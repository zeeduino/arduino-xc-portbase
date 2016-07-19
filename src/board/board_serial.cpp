/*
  board_serial.h - Arduino-XC HAL API implementation of serial comm
  Copyright (c) 2016 Ravendyne Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "lib/UARTSerial.h"
#include "board/board_serial.h"
#include "ringbuffer.h"
#include "board/variant.h"

// #include ....

// ----------------------------------------------------------------------------
//   CONSTANT DEFINITIONS
// ----------------------------------------------------------------------------
// These "constants" are declared as variables and their value is platform specific
// This way we can declare these in code that is not platform specific (i.e. core or lib)
// and then define their values here in platform specific part where we need to access
// platform specific values (like UART_LCR_WLEN8, UART_LCR_PARITY_F_0, etc.)
extern const uint32_t SERIAL_8N1 = (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);
extern const uint32_t SERIAL_8E1 = (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_EVEN | UART_LCR_PARITY_EN);
extern const uint32_t SERIAL_8O1 = (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_ODD | UART_LCR_PARITY_EN);
extern const uint32_t SERIAL_8M1 = (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_F_1 | UART_LCR_PARITY_EN);
extern const uint32_t SERIAL_8S1 = (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_F_0 | UART_LCR_PARITY_EN);

/******************************************************************
 * UART objects
 */
/*
 * We declare buffers here so we can have multiple instances of
 * Serial object on different ports and not have to handle that
 * in UARTClass
 */
/* Transmit and receive ring buffers */
STATIC RingBuffer txring, rxring;

/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 128   /* Send */
#define UART_RRB_SIZE 32    /* Receive */

/* Transmit and receive buffers */
static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

// This can be either declared like this...
//UARTClass Serial(LPC_USART, UART0_IRQn, 0, &rxring, &txring);
// ...or like this...
UARTSerial Serial;
// and then constructed in Serial_Init()

// ----------------------------------------------------------------------------
//   INIT/DEINIT FUNCTIONS
// ----------------------------------------------------------------------------
void Serial_Init(void)
{

    /* Before using the ring buffers, initialize them using the ring
       buffer init function */
    RingBuffer_init(&rxring, rxbuff, UART_RRB_SIZE, sizeof(uint8_t));
    RingBuffer_init(&txring, txbuff, UART_SRB_SIZE, sizeof(uint8_t));

    /* creation of Serial object is chip/board specific, this is example for LPC */
    // Serial = UARTSerial(LPC_USART, UART0_IRQn, 0, &rxring, &txring);
}

// ----------------------------------------------------------------------------
void Serial_UART_Init(void *pUart, uint32_t dwIrq, const uint32_t dwBaudRate, const uint32_t configData)
{
}

// ----------------------------------------------------------------------------
void Serial_UART_End(void *pUart, uint32_t dwIrq)
{
}

// ----------------------------------------------------------------------------
void Serial_UART_Flush(void *pUart)
{
    // Wait for transmission to complete
    while (!Serial_UART_TxRegisterEmpty(_pUart)) yield();
}

// ----------------------------------------------------------------------------
//   LOW-LEVEL RX/TX FUNCTIONS, ALSO USED IN IRQ HANDLER
// ----------------------------------------------------------------------------
/* UART transmit-only interrupt handler for ring buffers */
void Serial_UART_Transmit(void *pUART, RingBuffer *pRB)
{
	uint8_t ch;

    /* Fill FIFO until full or until TX ring buffer is empty */
    while (Serial_UART_TxRegisterEmpty(pUART) && RingBuffer_popOne(pRB, &ch))
    {
        // Use chip library/your own code to send ch via UART here
    }
}

// ----------------------------------------------------------------------------
/* UART receive-only interrupt handler for ring buffers */
void Serial_UART_Receive(void *pUART, RingBuffer *pRB)
{
    /* New data will be ignored if data not popped in time */
    while (Serial_UART_RxRegisterHasData(pUART))
    {
        // Use chip library/your own code to receive ch via UART here
        uint8_t ch = read_the_char_from_UART();
        RingBuffer_pushOne(pRB, &ch);
    }
}

// ----------------------------------------------------------------------------
/*
 * When this returns true, that means UART is ready for the next byte to be sent.
 * This usually means: the top byte of the hardware UART FIFO is available
 * to accept next byte to be sent.
 */
bool Serial_UART_TxRegisterEmpty(void *pUART)
{
	return true;
}

// ----------------------------------------------------------------------------
/*
 * When this returns true, that means UART has received a byte and it is waiting
 * for us to read it. This usually means: location at which UART register that
 * points to the oldest received byte in hardware UART FIFO, has not been read yet,
 * there's still data to read from receive FIFO.
 */
bool Serial_UART_RxRegisterHasData(void *pUART)
{
	return false;
}

// ----------------------------------------------------------------------------
//   INTERRUPTS
// ----------------------------------------------------------------------------
void Serial_UART_Set_Interrupt_Priority(uint32_t dwIrq, uint32_t priority)
{
}

// ----------------------------------------------------------------------------
uint32_t Serial_UART_Get_Interrupt_Priority(uint32_t dwIrq)
{
    return 0;
}

// ----------------------------------------------------------------------------
void Serial_UART_Disable_Interrupt(void *pUART, uint32_t dwIrq)
{
}

// ----------------------------------------------------------------------------
void Serial_UART_Enable_Interrupt(void *pUART, uint32_t dwIrq)
{
}

// ----------------------------------------------------------------------------
//   EVENTS
// ----------------------------------------------------------------------------
// This fires in main loop whenever UART receives any bytes
// and they are available to be read
void serialEvent() __attribute__((weak));
void serialEvent() { }
// This one is called by main.cpp after every loop() call
void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
}

// ----------------------------------------------------------------------------
//   IRQ HANDLERS
// ----------------------------------------------------------------------------

/*
    This part is very chip specific, IRQ handlers could be C, assembler etc. and
    declared in various ways. What follows is general outline of the interrupt service
    routine which should be usable in most cases.
*/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   UART interrupt handler using ring buffers
 * @return  Nothing
 */
void UART_IRQHandler(void)
{
    /* Want to handle any errors? Do it here. */

    /* Use default ring buffer handler. Override this with your own
       code if you need more capability. */
    /* Handle transmit interrupt if enabled */
    if (/* TX interrupt pending */)
    {
        // replace LPC_USART with your own *void pointer
    	Serial_UART_Transmit(LPC_USART, &txring);

        /* Disable transmit interrupt if the ring buffer is empty */
        if (RingBuffer_isEmpty(&txring))
        {
            // replace LPC_USART with your own *void pointer
        	Serial_UART_Disable_Interrupt(LPC_USART, 0);
        }
    }

    /* Handle receive interrupt */
    // replace LPC_USART with your own *void pointer
    Serial_UART_Receive(LPC_USART, &rxring);
}


#ifdef __cplusplus
}
#endif


