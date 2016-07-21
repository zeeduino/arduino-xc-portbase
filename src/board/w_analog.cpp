/*
  w_analog.cpp - Arduino-XC HAL API implementation of analog core library functions
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

#include "board_private.h"
#include "pins_arduino.h"
#include "board/pin_mapping.h"
#include "board/utilities.h"

// #include ....

uint32_t Board_Analog_Read(uint32_t adcChannel)
{
    uint16_t dataADC;
    uint32_t pinNumber;

    uint32_t port = 0;
    uint8_t pin = 7;
    uint32_t modefunc = WIRING_DIGITAL_NOTOK;

    if (!isAdcChannel(adcChannel))
    {
        return 0;
    }

    pinNumber = adcChannelToPin(adcChannel);
    port = APIN_PORT(pinNumber);
    pin = APIN_PIN(pinNumber);
    // by default, all AD pins are set to analog mode
    // so we can find mode value using APIN_MODE
    modefunc = APIN_MODE(pinNumber);

    /* call chip library/your code here to set pin to analog function */

    /* call chip library/your code here to start A/D conversion */

    /* Waiting for A/D conversion complete */
    while (/* A/D converter is busy */)
    {
    }

    /* call chip library/your code here to read ADC value */
    dataADC = read_adc_value_from_chip();

    return dataADC;
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
// dutyCycle is set to 10-bit resolution (1024 steps)
void Board_Analog_Write(uint32_t ulPin, uint32_t ulValue)
{
    uint32_t dutyMatchCount;
    uint32_t pwmPeriod;

    LPC_TIMER_T *pTMR;
    uint8_t channel;
    uint8_t port;
    uint8_t pin;
    uint8_t pwmChannel;
    uint32_t modefunc;

    // analogWrite() calls this function only if ulPin has PWM support.
    // optimize this so we don't have to do it on every analogWrite
    port = APIN_PORT(ulPin);
    pin = APIN_PIN(ulPin);
    pwmChannel = APIN_PWM(ulPin);

    pTMR = PWM_MAP_TIMER(pwmChannel);
    channel = PWM_MAP_CHANNEL(pwmChannel);
    modefunc = PWM_MAP_MODE(pwmChannel);

    /* call chip library/your code here to enable function on selected pin */
    /* call chip library/your code here to set up hardware PWM */
    /* call chip library/your code here to run/enable PWM peripheral */
}
