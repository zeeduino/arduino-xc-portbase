/*
  board_private.h - platform specific internal initialization functions
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

#include "board/board_variant.h"
#include "board_private.h"
#include "board/variant.h"

//#include ...

/*
    Put any private initialization functions here.
    These are just some examples, highly chip/board specific.
*/

/*****************************************
 * ADC
 *****************************************/

void Board_ADC_Init(void)
{
}


/*****************************************
 * PWM
 *****************************************/

void Board_PWM_Init_CT32B0()
{
}

void Board_PWM_Init_CT16B0()
{
}

void Board_PWM_Init_CT16B1()
{
}
