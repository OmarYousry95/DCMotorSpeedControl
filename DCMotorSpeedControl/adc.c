/*******************************************************************************************
 * [FILE NAME]:		adc.h
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	8 Jan 2020
 * [DESCRIPTION]:	This c file contains implementation of functions for ADC Module
 * 					in AVR ATMEGA-16 Micro-controller
 *******************************************************************************************/

#include "adc.h"

/******************************************************************
 * 						Global Variables						  *
 ******************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/******************************************************************
 * 				  Interrupt Service Routines					  *
 ******************************************************************/
ISR(ADC_vect)
{
	/*Go to callback function*/
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/******************************************************************
 * 				  Public Functions Definitions					  *
 ******************************************************************/
/*Description: This Function initialises the ADC Module:
 * 1. Determines desired reference voltage for ADC either AREF/AVCC/Internal voltage
 * 2. Determines desired mode for ADC either polling/interrupt
 * 3. Determines desired clock for ADC*/
void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/*Initially clear ADMUX register:
	 * 1. Clear ADLAR bit to save the converted data in the LSbits of ADC register
	 * 2. Clear MUX4:0 bits to select channel 0 initially*/
	ADMUX=0;
	/*Inserts in ADMUX register the REFS1:0 bits for determining reference voltage*/
	ADMUX = (ADMUX&0x3F) | ((Config_Ptr->referenceVolt)<<6);
	/*Initially clear ADCSRA register*/
	ADCSRA=0;
	/*Enable ADC module by setting ADEN bit*/
	SET_BIT(ADCSRA,ADEN);
	/*Inserts in ADCSRA register the ADPS2:0 bits for determining CLK for ADC*/
	ADCSRA = (ADCSRA&0xF8) | (Config_Ptr->clock);
	/*Inserts in ADCSRA register the ADIE bit for determining either ADC will operate with
	 *polling or interrupt*/
	ADCSRA = (ADCSRA&0xF7) | ((Config_Ptr->mode)<<3);
}

/*Description: This Function reads input from a given channel number and starts conversion*/
void ADC_readChannel(uint8 ch_num)
{
	/*Inserts channel number in MUX4:0 bits in ADMUX register*/
	ADMUX = (ADMUX&0xE0) | (ch_num&0x07);
	/*Start conversion in ADC module by setting ADSC bit*/
	SET_BIT(ADCSRA,ADSC);
	/*Check for polling mode (i.e. ADC Interrupt enable bit is clear)*/
	if(IS_BIT_CLEAR(ADCSRA,ADIE))
	{
		/*Busy-wait loop till ADC finishes conversion*/
		while(IS_BIT_CLEAR(ADCSRA,ADIF)){};
		/*Clear flag of ADC for next conversions*/
		SET_BIT(ADCSRA,ADIF);
		/*Go to callback function*/
		if(g_callBackPtr != NULL_PTR)
		{
			(*g_callBackPtr)();
		}
	}
}

/*Description: This Function gets ADC value from ADC register*/
uint16 ADC_getValue(void)
{
	return ADC;
}

/*Description: This function sets call back function for ADC module*/
void ADC_setCallBack (void(*a_ptr)(void))
{
	g_callBackPtr=a_ptr;
}
