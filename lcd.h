

#ifndef LCD_H_
#define LCD_H_

/* Private includes ----------------------------------------------------------*/
#include "gpio.h"
#include "configboard.h"
/* Private typedef -----------------------------------------------------------*/

enum {BINARY=2,OCTAL=8,DECIMAL=10,HEXADECIMAL=16};
enum {LINE0=0,LINE1};
enum {COL0=0,COL1,COL2,COL3,COL4,COL5,COL6,COL7,COL8,COL9,COL10,COL11,COL12,COL13,COL14,COL15};

enum {CGRAMLOC0=0x40,CGRAMLOC1=0x48,CGRAMLOC2=0x50,CGRAMLOC3=0x58,CGRAMLOC4=0x60,CGRAMLOC5=0x68,CGRAMLOC6=0x70,
	  CGRAMLOC7=0x78};

/* Private define ------------------------------------------------------------*/
#define LCD8BITMODE 0
#define LCD4BITMODE 1

/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/**
 * @brief Setting direction for LCD pins connected on board
 * @return None
 **/
void vLCDInitialize(void);

/**
* @brief Sending initialization commands to LCD controller
* @return None
**/
void vLCDInitialCommands(void);

/**
* @brief For writing data into the LCD
* @param[in] data data for writing into LCD
* @return None
**/
void vLCDWriteData(uint8_t data);

/**
* @brief For writing command into the LCD
* @param[in] command command for writing into LCD
* @return None
**/
void vLCDWriteCommand(uint8_t command);

/**
* @brief For writing command into the LCD
* @param[in] string string for writing into LCD
* @return None
**/
void vLCDWriteString(uint8_t* string);

/**
* @brief For writing command into the LCD
* @param[in] num num for writing into LCD
* @param[in] base base of the num for writing into LCD, it can be BINARY,OCTAL,DECIMAL,HEXADECIMAL
* @return None
**/
void vLCDWriteNum(uint32_t num, uint8_t base);

/**
* @brief For writing command into the LCD
* @param[in] lineno selecting the lineno as either LINE0, LINE1
* @param[in] columnno column position in the selected line COL0=0,COL1,COL2,COL3,COL4,COL5,
* 			  COL6,COL7,COL8,COL9,COL10,COL11,COL12,COL13,COL14,COL15
* @return None
**/
void vLCDGotoxy(uint8_t lineno, uint8_t columnno);

/**
 * @brief For writing floating point number into the LCD
 * @param[in] num floating point number for writing into LCD
 * @param[in] base base of the num for writing into LCD, it can be BINARY,OCTAL,DECIMAL,HEXADECIMAL
 * @return None
 **/
void vLCDWriteFloatNum(float num);

/**
 * @brief For storing custom character into CGRAM location of LCD
 * @param[in] cgramlocation CGRAM location address
 * @param[in] ptrtochararray pointer to custom character array
 * @return None
 **/
void vLCDCustomCharStore(uint8_t cgramlocation, const uint8_t* ptrtochararray);

/**
 * @brief Clearing the LCD
 * @return None
 **/
void vLCDClear(void);

/**
 * @brief For implementing the printf function
 * @param[in] formatstring formatted string to display
 * @return None
 **/
void vLCDPrintf(char* formatstring,...);


#endif /* LCD_H_ */
