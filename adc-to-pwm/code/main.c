/*
 *  main.c
 *
 *  Created on: Sep 23, 2018
 *  Author: Boula
 */

#include "adc.h"
#include "timer0.h"
#include <util/delay.h>

int main(void)
{
	ADC_init(); /* initialize ADC driver */
    while(1)
    {
		Timer0_PWM_Init(((uint32)ADC_readChannel(0)) * 255 / 1023);
		_delay_ms(50);
    }
}
