/*******************************************************************************************
 * [FILE NAME]:		adc.h
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	8 Jan 2020
 * [DESCRIPTION]:	This header file contains static configurations and function prototypes
 * 					for ADC Module in AVR ATMEGA-16 Micro-controller
 *******************************************************************************************/

#ifndef ADC_H_
#define ADC_H_

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
	AREF,AVCC,INTERNAL=3
}ADC_ReferenceVoltage;

typedef enum{
	POLLING,INTERRUPT
}ADC_Mode;

typedef enum{
	ADC_F_CPU_2,ADC_F_CPU_4=2,ADC_F_CPU_8,ADC_F_CPU_16,ADC_F_CPU_32,ADC_F_CPU_64,ADC_F_CPU_128
}ADC_Clk;

typedef struct{
	ADC_ReferenceVoltage referenceVolt;
	ADC_Mode mode;
	ADC_Clk clock;
}ADC_ConfigType;


/******************************************************************
 * 				  Public Functions Prototypes					  *
 ******************************************************************/
/*Description: This Function initialises the ADC Module:
 * 1. Determines desired reference voltage for ADC either AREF/AVCC/Internal voltage
 * 2. Determines desired mode for ADC either polling/interrupt
 * 3. Determines desired clock for ADC*/
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*Description: This Function reads input from a given channel number and starts conversion*/
void ADC_readChannel(uint8 ch_num);

/*Description: This Function gets ADC value from ADC register*/
uint16 ADC_getValue(void);

/*Description: This function sets call back function for ADC module*/
void ADC_setCallBack (void(*a_ptr)(void));

#endif /* ADC_H_ */
