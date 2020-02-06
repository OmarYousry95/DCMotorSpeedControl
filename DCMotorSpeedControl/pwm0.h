/*******************************************************************************************
 * [FILE NAME]:		pwm0.h
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	10 Jan 2020
 * [DESCRIPTION]:	This header file contains static configurations and function prototypes
 * 					for PWM Module in TIMER0 in AVR ATMEGA-16 Micro-controller
 *******************************************************************************************/
#ifndef PWM0_H_
#define PWM0_H_

/******************************************************************
 * 				Common Header Files Inclusion					  *
 ******************************************************************/
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/******************************************************************
 * 				    User-defined Data Types					      *
 ******************************************************************/
typedef enum{
	NON_INVERTED,INVERTED
}PWM0_Mode;

typedef enum{
	NO_CLK_SOURCE,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXT_FALLING,EXT_RISING
}PWM0_Clk;

typedef struct{
	PWM0_Mode mode;
	PWM0_Clk clock;
}PWM0_ConfigType;

/******************************************************************
 * 				  Public Functions Prototypes					  *
 ******************************************************************/
/*Description: This Function initialises the PWM Module in TIMER0:
 * 1. Determines desired mode for PWM (Inverting / Non-inverting)
 * 2. Determines desired clock for PMW0 (i.e. which prescalar to be used) according to your device*/
void PWM0_init(const PWM0_ConfigType * Config_Ptr);

/*Description: This Function determines duty cycle with which PWM work with according to inserted
 * compare value*/
void PWM0_start(const uint8 compareVal);

/*Description: This Function stops/de-initialises the PWM Module in TIMER0*/
void PWM0_DeInit(void);

#endif /* PWM0_H_ */
