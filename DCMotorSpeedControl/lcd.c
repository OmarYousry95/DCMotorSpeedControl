/***********************************************************************************************
 * [FILE NAME]:		lcd.c
 * [AUTHOR]:		Omar Yousry
 * [DATE CREATED]:	29 Dec 2019
 * [DESCRIPTION]:	This c file contains the functions of LCD driver either it is 2-line or 4-line
 * 					for 4-bit mode or 8-bit mode
 ***********************************************************************************************/

#include "lcd.h"

/**********STATIC (PRIVATE) FUNCTIONS DECLARATION********/
static void reverseString (char * str, uint8 length);
static char * intToString (int data, char * buff, int base);


/**********FUNCTIONS Definitions**************/
static void reverseString (char * str, uint8 length)
{
    uint8 start,end,temp=0;
    start=0;
    end=length-1;
    while(start<end)
    {
        temp=str[start];
        str[start]=str[end];
        str[end]=temp;
        start++;
        end--;
    }
}

static char * intToString (int data, char * buff, int base)
{
    uint8 i=0;
    int sign=0;
    if(data==0)
    {
        buff[0]='0';
        buff[1]='\0';
        return buff;
    }
    if(data<0)
    {
        sign=data;
        data=-data;
    }
    while (data != 0)
    {
        buff[i]=data%base + '0';
        data=data/base;
        i++;
    }
    if(sign<0)
    {
        buff[i++]='-';
    }
    buff[i]='\0';
    reverseString(buff,i);
    return buff;
}


void LCD_init(void)
{
	SET_BIT(LCD_CTRL_DIR,RS);		/*Set RS to be output pin*/
	SET_BIT(LCD_CTRL_DIR,RW);		/*Set RW to be output pin*/
	SET_BIT(LCD_CTRL_DIR,E);		/*Set E  to be output pin*/
	#if(DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_DIR |= 0xF0;
		#else
			LCD_DATA_DIR |= 0x0F;
		#endif
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
	#elif(DATA_BITS_MODE == 8)
		LCD_DATA_DIR=0xFF;			/*Set Data Port to be output port*/
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /*2-line LCD with 8-bit mode*/
	#endif
	LCD_sendCommand(CURSOR_OFF);	/*Cursor OFF*/
	LCD_clearScreen();				/*Clear Screen at the beginning*/
}

void LCD_sendCommand (uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); 	 /*RS=0 to send command*/
	CLEAR_BIT(LCD_CTRL_PORT,RW);	 /*RW=0 to write*/
	_delay_ms(1);					 /*delay for tas*/
	SET_BIT(LCD_CTRL_PORT,E); 		 /*E=1 to enable*/
	_delay_ms(1); 					 /*delay for tpw-tdsw*/
	#if(DATA_BITS_MODE == 4)
		/*Upper 4 bits*/
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT&0x0F) | (command&0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT&0xF0) | ((command&0xF0)>>4);
		#endif
			_delay_ms(1); 					 /*delay for tdsw*/
			CLEAR_BIT(LCD_CTRL_PORT,E); 	 /*E=0 to disable*/
			_delay_ms(1); 					 /*delay for th*/
			SET_BIT(LCD_CTRL_PORT,E); 		 /*E=0 to enable*/
			_delay_ms(1); 					 /*delay for tpw-tdsw*/
		/*Lower 4 bits*/
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT&0x0F) | ((command&0x0F)<<4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT&0xF0) | (command&0x0F);
		#endif
			_delay_ms(1); 					 /*delay for tdsw*/
			CLEAR_BIT(LCD_CTRL_PORT,E); 	 /*E=0 to disable*/
			_delay_ms(1); 					 /*delay for th*/
	#elif(DATA_BITS_MODE == 8)
		LCD_DATA_PORT = command;		 /*send command to data port of LCD*/
		_delay_ms(1); 					 /*delay for tdsw*/
		CLEAR_BIT(LCD_CTRL_PORT,E); 	 /*E=0 to disable*/
		_delay_ms(1); 					 /*delay for th*/
	#endif
}

void LCD_displayCharacter (uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,RS); 		 /*RS=1 to send data*/
	CLEAR_BIT(LCD_CTRL_PORT,RW);	 /*RW=0 to write*/
	_delay_ms(1);					 /*delay for tas*/
	SET_BIT(LCD_CTRL_PORT,E); 		 /*E=1 to enable*/
	_delay_ms(1); 					 /*delay for tpw-tdsw*/
	#if(DATA_BITS_MODE == 4)
		/*Upper 4 bits*/
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT&0x0F) | (data&0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT&0xF0) | ((data&0xF0)>>4);
		#endif
			_delay_ms(1); 					 /*delay for tdsw*/
			CLEAR_BIT(LCD_CTRL_PORT,E); 	 /*E=0 to disable*/
			_delay_ms(1); 					 /*delay for th*/
			SET_BIT(LCD_CTRL_PORT,E); 		 /*E=0 to enable*/
			_delay_ms(1); 					 /*delay for tpw-tdsw*/
			/*Lower 4 bits*/
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT&0x0F) | ((data&0x0F)<<4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT&0xF0) | (data&0x0F);
		#endif
			_delay_ms(1); 					 /*delay for tdsw*/
			CLEAR_BIT(LCD_CTRL_PORT,E); 	 /*E=0 to disable*/
			_delay_ms(1); 					 /*delay for th*/
	#elif(DATA_BITS_MODE == 8)
		LCD_DATA_PORT = data;			 /*send data to data port of LCD*/
		_delay_ms(1); 					 /*delay for tdsw*/
		CLEAR_BIT(LCD_CTRL_PORT,E); 	 /*E=0 to disable*/
		_delay_ms(1); 					 /*delay for th*/
	#endif
}

void LCD_displayString (const char * data)
{
	uint8 i=0;
	while(data[i] != '\0')
	{
		LCD_displayCharacter(data[i]);
		i++;
	}
}

void LCD_clearScreen (void)
{
	LCD_sendCommand(0x01); /*Clear Screen*/
}

void LCD_displayStringRowColumn (uint8 row, uint8 col, const char * data)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(data);
}

void LCD_goToRowColumn (uint8 row,uint8 col)
{
	uint8 address;
	switch (row)
	{
		case 0:
			address=col;
			break;
		case 1:
			address=0x40+col;
			break;
		case 2:
			address=0x10+col;
			break;
		case 3:
			address=0x50+col;
			break;
	}
	LCD_sendCommand(address | SET_CURSOR_LOCATION);
}

void LCD_intgerToString (int data)
{
	char buff[16];
	intToString(data,buff,10);
	//itoa(data,buff,10);
	LCD_displayString(buff);
}
