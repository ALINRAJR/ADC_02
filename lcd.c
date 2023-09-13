


/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
/* Private includes ----------------------------------------------------------*/
#include "lcd.h"


#if configLCD
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define DDRAMADDRESSLINE0 0x80
#define DDRAMADDRESSLINE1 0xC0

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Need to fill the custom character values after calculating from the below link */
/* https://maxpromer.github.io/LCD-Character-Creator/            */
const uint8_t customchararray0[]={0x02,0x02,0x06,0x06,0x0E,0x0E,0x1E,0x1E};
const uint8_t customchararray1[]={0x04,0x04,0x04,0x0E,0x0E,0x1F,0x1F,0x1F};
const uint8_t customchararray2[]={0};
const uint8_t customchararray3[]={0};
const uint8_t customchararray4[]={0};
const uint8_t customchararray5[]={0};
const uint8_t customchararray6[]={0};
const uint8_t customchararray7[]={0};

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

 /**
  * @brief Setting direction for LCD pins connected on board
  * @return None
  **/
void vLCDInitialize(void)
{
#if LCD8BITMODE
	/* TODO DONE */
	/* Setting directions of the data pins of the LCD */
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D0, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D1, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D2, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D3, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D4, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D5, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D6, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D7, OUTPUT);

	/* Setting directions of the control pins of the LCD */
	vGpioSetDir(LCDCTRLPORT, LCDCTRLPIN_RS, OUTPUT);
	vGpioSetDir(LCDCTRLPORT, LCDCTRLPIN_RW, OUTPUT);
	vGpioSetDir(LCDCTRLPORT, LCDCTRLPIN_EN, OUTPUT);

	/* Clearing the control pin RW as we are going to do only write operation always*/
	vGpioClrPin(LCDCTRLPORT, LCDCTRLPIN_RW);

#elif LCD4BITMODE

	/* Setting directions of the data pins of the LCD */
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D4, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D5, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D6, OUTPUT);
	vGpioSetDir(LCDDATAPORT, LCDDATAPIN_D7, OUTPUT);

	/* Setting directions of the control pins of the LCD */
	vGpioSetDir(LCDCTRLPORT, LCDCTRLPIN_RS, OUTPUT);
	vGpioSetDir(LCDCTRLPORT, LCDCTRLPIN_RW, OUTPUT);
	vGpioSetDir(LCDCTRLPORT, LCDCTRLPIN_EN, OUTPUT);

#endif
}

/**
 * @brief     Crude delay implementation for generating a delay
 * @param[in] count No of times the loop should run
 * @return    No return value
 **/

/* Crude delay implementation for generating a delay */
void vLCDDelay(uint32_t count)
{
	int i,j;
	for(i=0;i<count;i++)
		for(j=0;j<0xA00;j++);
}

/**
 * @brief Sending initialization commands to LCD controller
 * @return None
 **/
void vLCDInitialCommands(void)
{
#if LCD8BITMODE
	/* TODO DONE
		 * Hint reuse vLCDWriteCommand  and implement the logic	 *
		 *
		 * */
	vLCDWriteCommand(0x38); // 8-BIT MODE
#elif LCD4BITMODE
	vLCDWriteCommand(0x28); // 4-BIT MODE
#endif
	vLCDWriteCommand(0x0F); // cursor blinking
	vLCDWriteCommand(0x06); // entry mode
	vLCDWriteCommand(0x01); // clear screen

/* Storing the custom characters in the CGRAM locations */
vLCDCustomCharStore(CGRAMLOC0,customchararray0);
vLCDCustomCharStore(CGRAMLOC3,customchararray1);


/*Making the LCD position into the first location of the display */
vLCDGotoxy(LINE0,COL0);

}

/**
 * @brief Clearing the LCD
 * @return None
 **/
void vLCDClear(void)
{
	vLCDWriteCommand(0x01); // clear screen
}


/**
 * @brief For writing data into the LCD
 * @param[in] data data for writing into LCD
 * @return None
 **/
void vLCDWriteData(uint8_t data)
{
#if LCD8BITMODE
	/* TODO DONE*/
	/* For Data, RS should be 1 */
	vGpioSetPin(LCDCTRLPORT, LCDCTRLPIN_RS);
	/* Writing the 8 byte data into the data pins D0-D7 */
	vGpioSetByte(LCDDATAPORT,LCDDATAPIN_D0,data);
	/* Making EN pin HIGH and LOW to act as an interrupt for the LCD Controller
	 * For notifying the change in values in D0-D7*/
	vGpioSetPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);
	vGpioClrPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);
#elif LCD4BITMODE

	/* For Data, RS should be 1 */
	vGpioSetPin(LCDCTRLPORT, LCDCTRLPIN_RS);
	/* Writing the 8 byte data into the data pins D4-D7
	 * Example consider data is 0x56
	 * First we have to seperate 0x05 from 0x56
	 * For that we are shifting 0x56 towards right 4 times so that value becomes 0x56 ==> 0x05
	 * And afterwards anding with 0x0F for ensuring only 4 bits are there.*
	 * */

	vGpioSetNibble(LCDDATAPORT,LCDDATAPIN_D4,((data>>4)&0x0F));
	/* For notifying the change in values in D4-D7*/
	vGpioSetPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);
	vGpioClrPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);
	/* Writing the 8 byte data into the data pins D4-D7
	 * Example consider data is 0x56
	 * Now we have to seperate 0x06 from 0x56
	 * For that we are shifting 0x56 towards s 0x56 & 0x0F==> 0x06
	 * */

	vGpioSetNibble(LCDDATAPORT,LCDDATAPIN_D4,(data&0x0F));
	/* For notifying the change in values in D4-D7*/
	vGpioSetPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);
	vGpioClrPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);

#endif
}


/**
 * @brief For writing command into the LCD
 * @param[in] command command for writing into LCD
 * @return None
 **/
void vLCDWriteCommand(uint8_t command)
{
#if LCD8BITMODE
	/* TODO DONE */
	/* For Command, RS should be 0 */
	vGpioClrPin(LCDCTRLPORT, LCDCTRLPIN_RS);
	/* Writing the 8 byte command into the data pins D0-D7 */
	vGpioSetByte(LCDDATAPORT,LCDDATAPIN_D0,command);
	/* Making EN pin HIGH and LOW to act as an interrupt for the LCD Controller
	 * For notifying the change in values in D0-D7*/
	vGpioSetPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);
	vGpioClrPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);

#elif LCD4BITMODE
	/* For Command, RS should be 0 */
	vGpioClrPin(LCDCTRLPORT, LCDCTRLPIN_RS);
	/* Writing the 8 byte command into the data pins D4-D7
	 * Example consider data is 0x56
	 * First we have to seperate 0x05 from 0x56
	 * For that we are shifting 0x56 towards right 4 times so that value becomes 0x56 ==> 0x05
	 * And afterwards anding with 0x0F for ensuring only 4 bits are there.*
	 * */

	vGpioSetNibble(LCDDATAPORT, LCDDATAPIN_D4, ((command >> 4) & 0x0F));
	/* For notifying the change in values in D4-D7*/
	vGpioSetPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);
	vGpioClrPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);
	/* Writing the 8 byte command into the data pins D4-D7
	 * Example consider data is 0x56
	 * Now we have to seperate 0x06 from 0x56
	 * For that we are shifting 0x56 towards s 0x56 & 0x0F==> 0x06
	 * */

	vGpioSetNibble(LCDDATAPORT, LCDDATAPIN_D4, (command & 0x0F));
	/* For notifying the change in values in D4-D7*/
	vGpioSetPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);
	vGpioClrPin(LCDCTRLPORT, LCDCTRLPIN_EN);
	vLCDDelay(0x50);

#endif
}


/**
 * @brief For writing command into the LCD
 * @param[in] string string for writing into LCD
 * @return None
 **/
void vLCDWriteString(uint8_t* string)
{
	/* TODO DONE
	 * Hint reuse vLCDWriteData and implement the logic
	 * */
	while(*string !='\0')
	{
		vLCDWriteData(*string);
		string++;
	}
}


/**
 * @brief For writing command into the LCD
 * @param[in] num num for writing into LCD
 * @param[in] base base of the num for writing into LCD, it can be BINARY,OCTAL,DECIMAL,HEXADECIMAL
 * @return None
 **/
void vLCDWriteNum(uint32_t num, uint8_t base)
{
	/* TODO
	 * Hint reuse vLCDWriteData or vLCDWriteString  and implement the logic the atoi
	 */
	uint8_t representation[]="0123456789ABCDEF";
	uint8_t string[20];
	uint8_t *ptrtostring=&string[19];

	*ptrtostring = '\0';

	if (num == 0) {
		*--ptrtostring = '0';
	} else {
		while (num > 0) {
			*--ptrtostring = representation[num % base];
			num = num / base;
		}
	}
    vLCDWriteString(ptrtostring);
}

/**
 * @brief For writing floating point number into the LCD
 * @param[in] num floating point number for writing into LCD
 * @param[in] base base of the num for writing into LCD, it can be BINARY,OCTAL,DECIMAL,HEXADECIMAL
 * @return None
 **/
void vLCDWriteFloatNum(float num)
{
	/* TODO
	 * Hint : Try to reuse vLCDWriteNum with base as DECIMAL
	 *
	 */

}




/**
 * @brief For writing command into the LCD
 * @param[in] lineno selecting the lineno as either LINE0, LINE1
 * @param[in] columnno column position in the selected line COL0=0,COL1,COL2,COL3,COL4,COL5,
 * 			  COL6,COL7,COL8,COL9,COL10,COL11,COL12,COL13,COL14,COL15
 * @return None
 **/
void vLCDGotoxy(uint8_t lineno, uint8_t columnno)
{
	/* TODO
	 * Hint reuse vLCDWriteCommand  and implement the logic *
	 *
	 * */
	if(lineno==LINE0)
		vLCDWriteCommand(DDRAMADDRESSLINE0+columnno);
	else if(lineno==LINE1)
		vLCDWriteCommand(DDRAMADDRESSLINE1+columnno);
}


/**
 * @brief For storing custom character into CGRAM location of LCD
 * @param[in] cgramlocation CGRAM location address CGRAMLOC0,CGRAMLOC1,CGRAMLOC2,CGRAMLOC3,CGRAMLOC4,CGRAMLOC5,CGRAMLOC6,CGRAMLOC7
 * @param[in] ptrtochararray pointer to custom character array
 * @return None
 **/
void vLCDCustomCharStore(uint8_t cgramlocation, const uint8_t* ptrtochararray)
{
	/*TODO */
	int i=0;
	/* Storing the custom characters in the CGRAM locations */
	vLCDWriteCommand(cgramlocation); /*Starting address of the location you need to write the custom character */
	while(i<8)
	{
		vLCDWriteData(*ptrtochararray++);
		i++;
	}
}

/**
 * @brief For implementing the printf function
 * @param[in] formatstring formatted string to display
 * @return None
 **/
void vLCDPrintf(char* formatstring,...)
{
	/*TODO */

	int num=0;
	char *str;
	/* Declaring an object for va_list called as arglist */
	va_list arglist;
	/* Initialize the argument list. */
	va_start(arglist, *formatstring);

	while (*formatstring != '\0') {

		if (*formatstring != '%')
			vLCDWriteData(*formatstring);

		else {
			formatstring++;

			switch (*formatstring) {

			case 'c':
				/* Get the next argument value, here we have only 1byte as we will only pass a character */
				num=va_arg(arglist, int);
				vLCDWriteData(num);
				break;
			case 'd':
				/* Get the next argument value, here we have 4byte as we pass an integer */
				num=va_arg(arglist, int);
				if(num<0)
				{
					vLCDWriteData('-');
					num= num*-1;
				}
				vLCDWriteNum(num,DECIMAL);
				break;
			case 'f':

				/* TODO */
				break;
			case 'o':
				/* Get the next argument value, here we have 4byte as we pass an integer */
				num=va_arg(arglist, int);
				vLCDWriteNum(num,OCTAL);

				break;
			case 's':
				str=va_arg(arglist,char *);
				vLCDWriteString(str);
				break;
			case 'x':
				/* Get the next argument value, here we have 4byte as we pass an integer */
				num=va_arg(arglist, int);
				vLCDWriteNum(num,HEXADECIMAL);
				break;
			default:
				/* DO NOTHING*/
				break;

			}

		}
		formatstring++;


	}
		/* Clean up. */
		va_end(arglist);


}


#endif //end of configLCD




