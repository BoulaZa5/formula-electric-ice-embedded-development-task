/*
 *  timer0.c
 *
 *  Created on: Sep 23, 2018
 *  Author: Boula
 */

#include "timer2.h"

void Timer2_PWM_Init(unsigned char set_duty_cycle)
{
	TCNT2 = 0; // Timer initial value
	OCR2  = set_duty_cycle; //compare value
	DDRD  = DDRD | (1<<PD7); //set OC2 as output pin --> pin where the PWM signal is generated from MC
	/* Configure timer control register
	 * 1. Fast PWM mode FOC2=0
	 * 2. Fast PWM Mode WGM21=1 & WGM20=1
	 * 3. Clear OC2 when match occurs (non inverted mode) COM20=0 & COM21=1
	 * 4. clock = F_CPU/8 CS20=0 CS21=1 CS22=0
	 */
	TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) | (1<<CS21);
}

void Timer2_PWM_Stop(void)
{
	TCCR2 = 0x00;
}
