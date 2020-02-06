/*******************************************************************************************
 * [FILE NAME]:		dc_motor.c
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	10 Jan 2020
 * [DESCRIPTION]:	This C file contains implementation of functions for DC Motor
 *******************************************************************************************/

#include "dc_motor.h"

/******************************************************************
 * 				 	Private Global Variables					  *
 ******************************************************************/
/*static global variable to hold which motor is initialised according
 *to configID struct*/
static DCMotor_ID motorID;

/******************************************************************
 * 				 	 Public Global Variables					  *
 ******************************************************************/
/*Variable to hold current motor state (direction)*/
bool motorDirection;

/******************************************************************
 * 				  Public Functions Definitions					  *
 ******************************************************************/
/*Description: This function initialises the motor according to passed parameters:
 * 1. Set pins of MCU connected to motor to be output
 * 2. Stops motor initially*/
void DCMotor_init(const DCMotor_ID * ConfigID_Ptr)
{
	/*Setting motor ID*/
	motorID.enable=ConfigID_Ptr->enable;
	motorID.pinNum_1=ConfigID_Ptr->pinNum_1;
	motorID.pinNum_2=ConfigID_Ptr->pinNum_2;
	motorID.port=ConfigID_Ptr->port;
	switch(ConfigID_Ptr->port)
	{
		case A:
			/*Set direction of 2 pins of motor and its enable to be output pins*/
			SET_BIT(DDRA,ConfigID_Ptr->pinNum_1);
			SET_BIT(DDRA,ConfigID_Ptr->pinNum_2);
			SET_BIT(DDRA,ConfigID_Ptr->enable);
			/*Stop motor initially by clearing the 2 bits of it*/
			CLEAR_BIT(PORTA,ConfigID_Ptr->pinNum_1);
			CLEAR_BIT(PORTA,ConfigID_Ptr->pinNum_2);
			break;
		case B:
			/*Set direction of 2 pins of motor and its enable to be output pins*/
			SET_BIT(DDRB,ConfigID_Ptr->pinNum_1);
			SET_BIT(DDRB,ConfigID_Ptr->pinNum_2);
			SET_BIT(DDRB,ConfigID_Ptr->enable);
			/*Stop motor initially by clearing the 2 bits of it*/
			CLEAR_BIT(PORTB,ConfigID_Ptr->pinNum_1);
			CLEAR_BIT(PORTB,ConfigID_Ptr->pinNum_2);
			break;
		case C:
			/*Set direction of 2 pins of motor and its enable to be output pins*/
			SET_BIT(DDRC,ConfigID_Ptr->pinNum_1);
			SET_BIT(DDRC,ConfigID_Ptr->pinNum_2);
			SET_BIT(DDRC,ConfigID_Ptr->enable);
			/*Stop motor initially by clearing the 2 bits of it*/
			CLEAR_BIT(PORTC,ConfigID_Ptr->pinNum_1);
			CLEAR_BIT(PORTC,ConfigID_Ptr->pinNum_2);
			break;
		case D:
			/*Set direction of 2 pins of motor and its enable to be output pins*/
			SET_BIT(DDRD,ConfigID_Ptr->pinNum_1);
			SET_BIT(DDRD,ConfigID_Ptr->pinNum_2);
			SET_BIT(DDRD,ConfigID_Ptr->enable);
			/*Stop motor initially by clearing the 2 bits of it*/
			CLEAR_BIT(PORTD,ConfigID_Ptr->pinNum_1);
			CLEAR_BIT(PORTD,ConfigID_Ptr->pinNum_2);
			break;
	}
}

/*Description: This function makes motor rotate:
 * 1. In certain desired direction (Clockwise or anti-clockwise)
 * 2. With certain speed according to PWM signal generated from Timer0*/
void DCMotor_rotate(const DCMotor_Direction a_motorDirection,const uint8 speed)
{
	motorDirection=a_motorDirection;
	PWM0_start(speed);
	switch(motorID.port)
	{
		case A:
			if(a_motorDirection == ANTI_CLOCKWISE)
			{
				/*Motor rotates anti-clockwise*/
				CLEAR_BIT(PORTA,motorID.pinNum_1);
				SET_BIT(PORTA,motorID.pinNum_2);
			}
			else
			{
				/*Motor rotates clockwise*/
				SET_BIT(PORTA,motorID.pinNum_1);
				CLEAR_BIT(PORTA,motorID.pinNum_2);
			}
			break;
		case B:
			if(a_motorDirection == ANTI_CLOCKWISE)
			{
				/*Motor rotates anti-clockwise*/
				CLEAR_BIT(PORTB,motorID.pinNum_1);
				SET_BIT(PORTB,motorID.pinNum_2);
			}
			else
			{
				/*Motor rotates clockwise*/
				SET_BIT(PORTB,motorID.pinNum_1);
				CLEAR_BIT(PORTB,motorID.pinNum_2);
			}
			break;
		case C:
			if(a_motorDirection == ANTI_CLOCKWISE)
			{
				/*Motor rotates anti-clockwise*/
				CLEAR_BIT(PORTC,motorID.pinNum_1);
				SET_BIT(PORTC,motorID.pinNum_2);
			}
			else
			{
				/*Motor rotates clockwise*/
				SET_BIT(PORTC,motorID.pinNum_1);
				CLEAR_BIT(PORTC,motorID.pinNum_2);
			}
			break;
		case D:
			if(a_motorDirection == ANTI_CLOCKWISE)
			{
				/*Motor rotates anti-clockwise*/
				CLEAR_BIT(PORTD,motorID.pinNum_1);
				SET_BIT(PORTD,motorID.pinNum_2);
			}
			else
			{
				/*Motor rotates clockwise*/
				SET_BIT(PORTD,motorID.pinNum_1);
				CLEAR_BIT(PORTD,motorID.pinNum_2);
			}
			break;
	}
}

/*Description: This function changes motor direction*/
void DCMotor_changeDirection(void)
{
	switch(motorID.port)
	{
		case A:
			if(motorDirection == ANTI_CLOCKWISE)
			{
				/*Motor rotates clockwise*/
				SET_BIT(PORTA,motorID.pinNum_1);
				CLEAR_BIT(PORTA,motorID.pinNum_2);
				motorDirection = CLOCKWISE;
			}
			else
			{
				/*Motor rotates anti-clockwise*/
				CLEAR_BIT(PORTA,motorID.pinNum_1);
				SET_BIT(PORTA,motorID.pinNum_2);
				motorDirection = ANTI_CLOCKWISE;
			}
			break;
		case B:
			if(motorDirection == ANTI_CLOCKWISE)
			{
				/*Motor rotates clockwise*/
				SET_BIT(PORTB,motorID.pinNum_1);
				CLEAR_BIT(PORTB,motorID.pinNum_2);
				motorDirection = CLOCKWISE;
			}
			else
			{
				/*Motor rotates anti-clockwise*/
				CLEAR_BIT(PORTB,motorID.pinNum_1);
				SET_BIT(PORTB,motorID.pinNum_2);
				motorDirection = ANTI_CLOCKWISE;
			}
			break;
		case C:
			if(motorDirection == ANTI_CLOCKWISE)
			{
				/*Motor rotates clockwise*/
				SET_BIT(PORTC,motorID.pinNum_1);
				CLEAR_BIT(PORTC,motorID.pinNum_2);
				motorDirection = CLOCKWISE;
			}
			else
			{
				/*Motor rotates anti-clockwise*/
				CLEAR_BIT(PORTC,motorID.pinNum_1);
				SET_BIT(PORTC,motorID.pinNum_2);
				motorDirection = ANTI_CLOCKWISE;
			}
			break;
		case D:
			if(motorDirection == ANTI_CLOCKWISE)
			{
				/*Motor rotates clockwise*/
				SET_BIT(PORTD,motorID.pinNum_1);
				CLEAR_BIT(PORTD,motorID.pinNum_2);
				motorDirection = CLOCKWISE;
			}
			else
			{
				/*Motor rotates anti-clockwise*/
				CLEAR_BIT(PORTD,motorID.pinNum_1);
				SET_BIT(PORTD,motorID.pinNum_2);
				motorDirection = ANTI_CLOCKWISE;
			}
			break;
	}
}

/*Description: This function stops the motor*/
void DCMotor_stop(void)
{
	switch(motorID.port)
	{
		case A:
			CLEAR_BIT(PORTA,motorID.pinNum_1);
			CLEAR_BIT(PORTA,motorID.pinNum_2);
			break;
		case B:
			CLEAR_BIT(PORTB,motorID.pinNum_1);
			CLEAR_BIT(PORTB,motorID.pinNum_2);
			break;
		case C:
			CLEAR_BIT(PORTC,motorID.pinNum_1);
			CLEAR_BIT(PORTC,motorID.pinNum_2);
			break;
		case D:
			CLEAR_BIT(PORTD,motorID.pinNum_1);
			CLEAR_BIT(PORTD,motorID.pinNum_2);
			break;
	}
}
