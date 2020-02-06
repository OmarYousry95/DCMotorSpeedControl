/*******************************************************************************************
 * [FILE NAME]:		dc_motor.h
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	10 Jan 2020
 * [DESCRIPTION]:	This header file contains static configurations and function prototypes
 * 					for DC Motor
 *******************************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/******************************************************************
 * 				Common Header Files Inclusion					  *
 ******************************************************************/
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "pwm0.h" /*For speed control*/

/******************************************************************
 * 				    User-defined Data Types					      *
 ******************************************************************/
typedef enum{
	CLOCKWISE,ANTI_CLOCKWISE
}DCMotor_Direction;

typedef enum{
	A,B,C,D
}DCMotor_Port;

typedef struct{
	DCMotor_Port port;
	uint8 pinNum_1;
	uint8 pinNum_2;
	uint8 enable;
}DCMotor_ID;

/******************************************************************
 * 				    Public Variables Externs				      *
 ******************************************************************/
/*Variable to hold current motor state (direction)*/
extern bool motorDirection;

/******************************************************************
 * 				  Public Functions Prototypes					  *
 ******************************************************************/
/*Description: This function initialises the motor according to passed parameters:
 * 1. Set pins of MCU connected to motor to be output
 * 2. Stops motor initially*/
void DCMotor_init(const DCMotor_ID * ConfigID_Ptr);

/*Description: This function makes motor rotate:
 * 1. In certain desired direction (Clockwise or anti-clockwise)
 * 2. With certain speed according to PWM signal generated from Timer0*/
void DCMotor_rotate(const DCMotor_Direction a_motorDirection,const uint8 speed);

void DCMotor_changeDirection(void);

/*Description: This function stops the motor*/
void DCMotor_stop(void);

#endif /* DC_MOTOR_H_ */

