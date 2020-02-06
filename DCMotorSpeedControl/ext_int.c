/*******************************************************************************************
 * [FILE NAME]:		ext_int.c
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	10 Jan 2020
 * [DESCRIPTION]:	This c file contains implementation of functions for external interrupts
 * 					in AVR ATMEGA-16 Micro-controller
 *******************************************************************************************/

#include "ext_int.h"

/******************************************************************
 * 						Global Variables						  *
 ******************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/******************************************************************
 * 				  Interrupt Service Routines					  *
 ******************************************************************/
ISR(INT0_vect)
{
	/*Go to callback function*/
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR(INT1_vect)
{
	/*Go to callback function*/
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR(INT2_vect)
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
/*Description: This function initialises External Interrupt:
 * 1. Determines which interrupt to be used INT0 or INT1 or INT2
 * 2. Determines logic to work with either on low level/any change in logic/falling or rising edge*/
void EXT_INT_init(const EXT_INT_ConfigType * Config_Ptr)
{
	switch(Config_Ptr->intNum)
	{
		case 0:
			/*Insert logic type bits in ISC01:0 bits for INT0 in MCUCR register*/
			MCUCR = (MCUCR&0xFC) | (Config_Ptr->logic);
			/*Enable INT0 by setting INT0 bit in GICR register*/
			SET_BIT(GICR,INT0);
			break;
		case 1:
			/*Insert logic type bits in ISC10:1 bits for INT1 in MCUCR register*/
			MCUCR = (MCUCR&0xF3) | ((Config_Ptr->logic)<<2);
			/*Enable INT1 by setting INT1 bit in GICR register*/
			SET_BIT(GICR,INT1);
			break;
		case 2:
			/*Insert logic type bit in ISC2 bit for INT2 in MCUCSR register*/
			MCUCSR = (MCUCSR&0xBF) | (((Config_Ptr->logic)&0x01)<<6);
			/*Enable INT2 by setting INT2 bit in GICR register*/
			SET_BIT(GICR,INT2);
			break;
	}
}

/*Description: This function disable External Interrupt:*/
void EXT_INT_DeInit(const uint8 intNum)
{
	switch(intNum)
	{
		case 0:
			/*Disable INT0 by clearing INT0 bit in GICR register*/
			CLEAR_BIT(GICR,INT0);
			break;
		case 1:
			/*Disable INT0 by clearing INT0 bit in GICR register*/
			CLEAR_BIT(GICR,INT1);
			break;
		case 2:
			/*Disable INT0 by clearing INT0 bit in GICR register*/
			CLEAR_BIT(GICR,INT2);
			break;
	}
}

/*Description: This function sets call back function for ADC module*/
void EXT_INT_setCallBack (void(*a_ptr)(void))
{
	/*Save the address of passed function (to be called) in global pointer to function*/
	g_callBackPtr=a_ptr;
}
