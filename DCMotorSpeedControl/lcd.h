/*******************************************************************************************
 * [FILE NAME]:		lcd.h
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	29 Dec 2019
 * [DESCRIPTION]:	This header file contains the protoypes of functions of LCD driver
 * 					either it is 2-line or 4-line for 4-bit mode or 8-bit mode
 *******************************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/***********HEADER FILES INCLUSION***********/
#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"


/**********STATIC CONFIGURATIONS*************/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 8

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

/*LCD Hardware Pins*/
#define LCD_DATA_DIR	DDRC
#define	LCD_DATA_PORT	PORTC
#define LCD_CTRL_DIR	DDRD
#define LCD_CTRL_PORT	PORTD
#define RS				PD4
#define RW				PD5
#define E				PD6

/*LCD commands*/
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define CLEAR_COMMAND 0x01
#define SET_CURSOR_LOCATION 0x80

/**********FUNCTIONS PROTOTYPES**************/
void LCD_init(void);
void LCD_sendCommand (uint8 command);
void LCD_displayCharacter (uint8 data);
void LCD_displayString (const char * data);
void LCD_clearScreen (void);
void LCD_displayStringRowColumn (uint8 row, uint8 col, const char * data);
void LCD_goToRowColumn (uint8 row,uint8 col);
void LCD_intgerToString (int data);

#endif /* LCD_H_ */
