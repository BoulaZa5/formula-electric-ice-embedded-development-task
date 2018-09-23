/*
 *  main.c
 *
 *  Created on: Sep 23, 2018
 *  Author: Boula
 */ 

#include "lcd.h"
#include "keypad.h"
#include "overflow_timer.h"
#include "timer2.h"
#include "interrupt2.h"

#define NUMBER_OF_OVERFLOWS_PER_HALF_SECOND 4

unsigned char g_tick = 0;

ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if(g_tick == NUMBER_OF_OVERFLOWS_PER_HALF_SECOND)
	{
		PORTD = PORTD ^ (1<<PD5); //toggle led every 1 second
		g_tick = 0; //clear the tick counter again to count a new second
	}
}

int main(void)
{
	SREG  |= (1<<7); //enable global interrupts in MC by setting the I-Bit.
	INT2_Init();

	const uint16 password = 123;
	uint16 temp_password = 0;
	uint8 wrong_times = 0;
	bool finished = 0;
	unsigned char key;

	DDRD  |= (1<<PD5) | (1<<PD6) | (1<<PD7);
	PORTD &= ~(1<<PD5) & ~(1<<PD6) & ~(1<<PD7);

	LCD_init();
	LCD_displayStringRowColumn(0, 0, "Enter your passw");
	LCD_displayStringRowColumn(1, 0, "ord:");
	LCD_goToRowColumn(2, 0);

    while(1)
    {
		/* if any switch pressed for more than 500 ms it counts more than one press */
		if (!finished)
		{
			key = KeyPad_getPressedKey(); /* get the pressed key number */
			if((key <= 9) && (key >= 0))
			{
				temp_password = temp_password * 10 + key;
				LCD_displayCharacter('*');
			}
			else if (key == '=' && temp_password == password)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "Correct");
				finished = 1;
				PORTD = PORTD ^ (1<<PD6);
				Timer2_PWM_Init(128);
			}
			else
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "Wrong");
				if (wrong_times == 2)
				{
					finished = 1;
					timer0_init_normal_mode();
				}
				else
				{
					temp_password = 0;
					wrong_times++;
					LCD_displayString(", Re-enter ");
					LCD_displayStringRowColumn(1, 0, "the password:");
					LCD_goToRowColumn(2, 0);
				}
			}
		}
		_delay_ms(500); /* Press time */
    }
}
