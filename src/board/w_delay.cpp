/*
  w_delay.cpp - Arduino-XC HAL API implementation of delay/timer core library functions
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

// #include ....


static uint32_t ticksPerSecond = 0;
static uint32_t ticksPerMs = 0;
static uint32_t ticksPerUs = 0;

uint32_t Board_Delay_Millis( void )
{
    /* call chip library/your code here to read count from hardware timer/counter */
    return read_timer_count_from_chip_timer_counter() / ticksPerMs;
}

uint32_t Board_Delay_MillisMax( void )
{
    // for 32-bit timer, max counter value is 2^32-1 = 0xFFFFFFFF
    return 0xFFFFFFFF / ticksPerMs;
}

uint32_t Board_Delay_Micros( void )
{
    /* call chip library/your code here to read count from hardware timer/counter */
    return read_timer_count_from_chip_timer_counter() / ticksPerUs;
}

uint32_t Board_Delay_MicrosMax( void )
{
    // for 32-bit timer, max counter value is 2^32-1 = 0xFFFFFFFF
    return 0xFFFFFFFF / ticksPerUs;
}

void Board_Delay_InitTimer( void )
{
    /* call chip library/your code here to initialize chip hardware timer/counter */

    /* Pre-compute tick rate. */
    ticksPerSecond = 1000000/* this number is chip/board specific */;
    ticksPerMs = ticksPerSecond / 1000;
    ticksPerUs = ticksPerSecond / 1000000;
}
