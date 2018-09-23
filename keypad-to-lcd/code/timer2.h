/*
 *  timer0.h
 *
 *  Created on: Sep 23, 2018
 *  Author: Boula
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>

void Timer2_PWM_Init(unsigned char set_duty_cycle);

void Timer2_PWM_Stop(void);

#endif /* TIMER0_H_ */
