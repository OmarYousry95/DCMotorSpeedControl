/*******************************************************************************************
 * [FILE NAME]:		pwm0.c
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	10 Jan 2020
 * [DESCRIPTION]:	This c file contains implementation of functions for PWM module in TIMER0
 * 					in AVR ATMEGA-16 Micro-controller
 *******************************************************************************************/


#include "pwm0.h"

/******************************************************************
 * 				  Public Functions Definitions					  *
 ******************************************************************/
/*Description: This Function initialises the PWM Module in TIMER0:
 * 1. Determines desired mode for PWM (Inverting / Non-inverting)
 * 2. Determines desired clock for PMW0 (i.e. which prescalar to be used) according to your device
 * 43 Determines desired compare value for PWM0 to change duty cycle accordingly*/
void PWM0_init(const PWM0_ConfigType * Config_Ptr)
{
	/*Initially clears TCCR0 register*/
	TCCR0=0;
	/*Set FOC0 bit for PWM mode*/
	CLEAR_BIT(TCCR0,FOC0);
	/*Set WGM00 and WGM01 bits to operate in Fast PWM mode*/
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);
	/*Set COM01 bit to operate in either inverting/non-inverting mode*/
	SET_BIT(TCCR0,COM01);
	/*Insert in COM00 bit the mode to select inverting or non-inverting mode*/
	TCCR0 = (TCCR0&0xEF) | ((Config_Ptr->mode)<<4);
	/*Insert clock in CS02:0 bits to select prescalar*/
	TCCR0 = (TCCR0&0xF8) | (Config_Ptr->clock);
	/*Clear TCNT0 register to start counting from zero*/
	TCNT0=0;
	/*Set PD3 bit in DDRD register to set the direction of pin 3 to be output*/
	SET_BIT(DDRB,PB3);
}

/*Description: This Function determines duty cycle with which PWM work with according to inserted
 * compare value*/
void PWM0_start(const uint8 compareVal)
{
	/*Insert compare value in OCR0 register to change duty cycle as desired*/
	OCR0=compareVal;
}

/*Description: This Function stops/de-initialises the PWM Module in TIMER0*/
void PWM0_DeInit(void)
{
	/*Clear all timer0 registers to stop PWM module*/
	TCCR0=0;
	TCNT0=0;
	OCR0=0;
}
