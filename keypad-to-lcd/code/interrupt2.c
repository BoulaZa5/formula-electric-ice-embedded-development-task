/*
 *  interrupt2.c
 *
 *  Created on: Sep 23, 2018
 *  Author: Boula
 */

#include "interrupt2.h"

/* External INT2 Interrupt Service Routine */
ISR(INT2_vect)
{
	timer0_stop_normal_mode();
	Timer2_PWM_Stop();
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_mode();
}

/* External INT2 enable and configuration function */
void INT2_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRB  &= (~(1<<PB2));               // Configure INT2/PB2 as input pin
	GICR  |= (1<<INT2);                 // Enable external interrupt pin INT2
	MCUCSR |= (1<<ISC2);                // Trigger INT2 with the raising edge
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}
