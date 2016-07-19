/*
  board_spi_bb.cpp - Arduino-XC HAL API implementation of SPI peripheral - bit-bang/software version
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


#include "board/variant.h"
#include "lib/SPI.h"
#include "wiring_delay.h"
#include "pins_arduino.h"
#include "board/board_spi.h"

// #include ....

//#define BB_DELAY() delayMicroseconds(5)
#define BB_DELAY()

/*
    User your chip's support library/your own code to define bit-toggling
    one-liners for CS and SCK and read/write for MISO/MOSI pins
*/

#define CS_LOW() Chip_GPIO_WritePortBit(LPC_GPIO_PORT, CS_PORTv, CS_BITv, false)
#define CS_HIGH() Chip_GPIO_WritePortBit(LPC_GPIO_PORT, CS_PORTv, CS_BITv, true)
#define SCK_LOW() Chip_GPIO_WritePortBit(LPC_GPIO_PORT, SCK_PORTv, SCK_BITv, false)
#define SCK_HIGH() Chip_GPIO_WritePortBit(LPC_GPIO_PORT, SCK_PORTv, SCK_BITv, true)
#define MISO() Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, MISO_PORTv, MISO_BITv)
#define MOSI(x) Chip_GPIO_WritePortBit(LPC_GPIO_PORT, MOSI_PORTv, MOSI_BITv, x)

uint8_t CS_BITv;
uint8_t CS_PORTv;
uint8_t SCK_BITv;
uint8_t SCK_PORTv;
uint8_t MISO_BITv;
uint8_t MISO_PORTv;
uint8_t MOSI_BITv;
uint8_t MOSI_PORTv;

void Board_SPI_SetInternalPortStateDefault(BoardSPIPort *port)
{
	CS_BITv    =   APIN_PIN(SPI_BUILTIN_SSEL);
	CS_PORTv   =   APIN_PORT(SPI_BUILTIN_SSEL);

	SCK_BITv   =   APIN_PIN(SPI_BUILTIN_SCK);
	SCK_PORTv  =   APIN_PORT(SPI_BUILTIN_SCK);

	MISO_BITv  =   APIN_PIN(SPI_BUILTIN_MISO);
	MISO_PORTv =   APIN_PORT(SPI_BUILTIN_MISO);

	MOSI_BITv  =    APIN_PIN(SPI_BUILTIN_MOSI);
	MOSI_PORTv =    APIN_PORT(SPI_BUILTIN_MOSI);
}

void Board_SPI_SetInternalPortState(BoardSPIPort *port)
{
	CS_BITv    =   APIN_PIN(port->cs);
	CS_PORTv   =   APIN_PORT(port->cs);

	SCK_BITv   =   APIN_PIN(port->clk);
	SCK_PORTv  =   APIN_PORT(port->clk);

	MISO_BITv  =   APIN_PIN(port->miso);
	MISO_PORTv =   APIN_PORT(port->miso);

	MOSI_BITv  =    APIN_PIN(port->mosi);
	MOSI_PORTv =    APIN_PORT(port->mosi);
}

uint8_t Board_SPI_Transfer(BoardSPIPort *port, uint8_t data)
{
    uint8_t rx;
    int i;

    Board_SPI_SetInternalPortState(port);

//    CS_LOW();
    BB_DELAY();
    rx = 0x00;
    for (i = 7; i >= 0; i--)
    {
        rx <<= 1;

        SCK_LOW();
        BB_DELAY();

        MOSI(data & (1 << i));
        BB_DELAY();

        SCK_HIGH();
        BB_DELAY();
        if (MISO())
            rx |= 1;
        BB_DELAY();
    }
//    MOSI(true); // MOSI HIGH when idle

    return rx;
}

void Board_SPI_CS_High(BoardSPIPort *port)
{
    Board_SPI_SetInternalPortState(port);
    CS_HIGH();
}

void Board_SPI_CS_Low(BoardSPIPort *port)
{
    Board_SPI_SetInternalPortState(port);
    CS_LOW();
}

void Board_SPI_Init(BoardSPIPort *port)
{
    Board_SPI_SetInternalPortState(port);

    Board_Digital_Write(port->cs, HIGH);
    Board_Digital_Write(port->clk, HIGH);
    Board_Digital_Write(port->miso, HIGH);
    Board_Digital_Write(port->mosi, HIGH);

    Board_Digital_PinMode(port->cs, OUTPUT);
    Board_Digital_PinMode(port->clk, OUTPUT);
    Board_Digital_PinMode(port->miso, OUTPUT);
    Board_Digital_PinMode(port->mosi, OUTPUT);
}

void Board_SPI_End(BoardSPIPort *port)
{

}
