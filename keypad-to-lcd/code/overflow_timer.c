/*
 *  overflow_timer.c
 *
 *  Created on: Sep 23, 2018
 *  Author: Boula
 */

#include "overflow_timer.h"

/* Description :
 * For clock=1Mhz and prescale F_CPU/1024 every count will take 1ms
 * so put initial timer counter=0  0 --> 255 (256ms per overflow)
 * so we need timer to overflow 4 times to get a 1 second
 */
void timer0_init_normal_mode(void)
{
	TCNT0 = 0; //timer initial value
	TIMSK |= (1<<TOIE0); //enable overflow interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
}

void timer0_stop_normal_mode(void)
{
	TCCR0 = 0x00;
}
