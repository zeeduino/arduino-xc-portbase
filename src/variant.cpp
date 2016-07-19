/*
  variant.cpp - implementation of initVariant() and other platform-specific Arduino functions
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
#include "board/board_serial.h"

// #include ....

#ifdef __cplusplus
extern "C" {
#endif

/**
 * All LPC IRQ handlers and such have to be implemented here
 * within extern "C" declaration, otherwise their names will get mangled
 * by C++ compiler and they WON'T get linked where you would expect them
 * to be because they are declared with __attribute__((weak)).
 */

/*
    Add any chip/board specific IRQ handlers, routines etc. here
    Example for LPC system tick IRQ handler
 */
// void SysTick_Handler(void)
// {
// }

void yield(void)
{
    __WFI();
}

void initVariant( void )
{
	Board_Init();
    Board_Delay_InitTimer();
    Serial_Init();

    /*
        Call any chip/board specific initializations for IRQs and similar critical stuff here
        or implement them in board_private.c as private functions and call those from here.
        Example for LPC system tick IRQ handler
    */
    // SysTick_Config(SystemCoreClock / 1000);

    /*
        Call any chip/board specific private initialization functions from board_private.c here.
        Example for LPC
    */
    Board_ADC_Init();
    Board_PWM_Init_CT32B0();
    Board_PWM_Init_CT16B0();
    Board_PWM_Init_CT16B1();
}


#ifdef __cplusplus
}
#endif
