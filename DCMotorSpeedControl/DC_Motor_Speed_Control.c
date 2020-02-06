/*******************************************************************************************
 * [FILE NAME]:		DC_Motor_Speed_Control.c
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	10 Jan 2020
 * [DESCRIPTION]:	This C file contains implementation of functions for DC_Motor_Speed_Control
 * 					It should control Speed of DC Motor using potentiometer and ADC and displays ADC
 * 					value of 16x2 Character LCD
 *******************************************************************************************/

#include "lcd.h"
#include "adc.h"
#include "pwm0.h"
#include "ext_int.h"
#include "dc_motor.h"


/*Global Variable to hold ADC value*/
uint16 g_adcVal=0;
/*Global Variable to hold mapped value from ADC to compare value to determine duty cycle of PWM*/
uint8 g_PWM=0;
/*Global Variable to hold duty cycle value*/
uint8 g_dutyCycle=0;


/*Callback function to control speed of motor*/
void Motor_controlSpeed(void)
{
	g_adcVal=ADC_getValue();
	g_PWM=((255*(float)g_adcVal))/1023;
	g_dutyCycle=((float)g_PWM/255)*100;
	(motorDirection==CLOCKWISE)?DCMotor_rotate(CLOCKWISE,g_PWM):DCMotor_rotate(ANTI_CLOCKWISE,g_PWM);
}

/*Callback function to change direction of rotation of motor*/
void Motor_changeDirection(void)
{
	DCMotor_changeDirection();
}

int main()
{
	/*Enable I-bit in SREG register (global interrupt)*/
	SET_BIT(SREG,7);

	/*Configuration structures*/
	/*ADC_ConfigType structure*/
	ADC_ConfigType ADC_Config={AREF,POLLING,ADC_F_CPU_8};
	/*PWM0_ConfigType structure*/
	PWM0_ConfigType PWM0_Config={NON_INVERTED,F_CPU_8};
	/*EXT_INT_ConfigType structure*/
	EXT_INT_ConfigType INT1_Config={1,RISING_EDGE};
	/*DCMotor_ID structure*/
	DCMotor_ID DCMotor_Config={B,0,1,3};

	/*Initialise ADC module to operate with AREF voltage, polling and 125 kHz clock*/
	ADC_init(&ADC_Config);
	/*Set ADC callback to call Motor_controlSpeed function when conversion is done*/
	ADC_setCallBack(Motor_controlSpeed);


	/*Initialise PWM0 module to generate non-inverted PWM signal with prescalar 8*/
	PWM0_init(&PWM0_Config);
	/*Initialise motor*/
	DCMotor_init(&DCMotor_Config);
	/*Initialise INT1 to work on rising edge*/
	EXT_INT_init(&INT1_Config);
	/*Set INT1 callback to call Motor_changeDirection function when switch on INT1 is pressed*/
	EXT_INT_setCallBack(Motor_changeDirection);

	/*Initialise LCD*/
	LCD_init();
	LCD_clearScreen();
	/*Display "ADC Value = " string continuously on LCD*/
	LCD_displayString("ADC Value = ");
	/*Display "DC = " string continuously on LCD*/
	LCD_displayStringRowColumn(1,0,"DC = ");

	while(1)
	{
		/*Read Channel 0 of ADC with which the potentiometer is connected*/
		ADC_readChannel(0);
		/*Displays ADC value on LCD starting from column 12 on row 0 after "ADC Value = "*/
		LCD_goToRowColumn(0,12);
		LCD_intgerToString(g_adcVal);
		/*Display space to delete the last digit in case of decrement from 3-digit number to
		 *2-digit number or from 2-digit number to 1-digit number*/
		LCD_displayCharacter(' ');
		/*Displays DC on LCD starting from column 5 on row 1 after "DC = "*/
		LCD_goToRowColumn(1,5);
		LCD_intgerToString(g_dutyCycle);
		LCD_displayCharacter('%');
		/*Display space to delete the last digit in case of decrement from 3-digit number to
		 *2-digit number or from 2-digit number to 1-digit number*/
		LCD_displayCharacter(' ');
	}
}
