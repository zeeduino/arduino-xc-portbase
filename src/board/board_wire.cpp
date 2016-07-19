/*
  board_wire.cpp - Arduino-XC HAL API implementation of Wire/I2C peripheral
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

#include "board/board_wire.h"
#include "ring_buffer.h"
#include "board/variant.h"
#include "lib/Wire.h"

// #include ....

WireClass Wire = WireClass((void*)LPC_I2C, NULL);

void WIRE_ISR_HANDLER(void)
{
    Wire.onService();
}

void Board_I2C_Master_Init(void *pI2C)
{
}

void Board_I2C_Slave_Init(void *pI2C, uint8_t address)
{
}

void Board_I2C_Set_Bus_Speed(void *pI2C, uint32_t frequency)
{
}

/* Returns:
    0:success
    1:data too long to fit in transmit buffer
    2:received NACK on transmit of address
    3:received NACK on transmit of data
    4:other error
 */
uint32_t Board_I2C_Master_Read_Blocking(void *pI2C, uint8_t address, uint8_t *rxBuffer, uint16_t size)
{
    return 0;
}

uint32_t Board_I2C_Master_Write_Blocking(void *pI2C, uint8_t address, uint8_t *txBuffer, uint16_t size)
{
    return 0;
}
