/*
===============================================================================
 Name        : 17_Day42_19102021_ADC002.c
 Date		 : 19-10-2021

 Description : Program demonstrate ADC Interrupt method software controlled
 	 	 	   start of conversion burst mode disabled and displaying on LCD

 

 Layered Architecture used for this project
 ************************************
 Application layer-17_Day42_19102021_ADC002.c
 ************************************
 Board layer - lcd.c/.h, configboard.h
 ************************************
 Low level drivers or chip level - pinmux.c/.h,adc.c/.h, gpio.c/.h
 ************************************
 Hardware
 ************************************

===============================================================================
*/

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Private includes ----------------------------------------------------------*/
#include "pinmux.h"
#include "adc.h"
#include "lcd.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define DISPTIMEOUT 	0xFFFFF
#define CONVTIMEOUT	    0x2FFFF
#define CLEARTIMEOUT	0x1FFFF
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint32_t channelno=0,adcresult[8]={0};
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  ADC Interrupt Service Routine
  * @retval none
  */
void ADC_IRQHandler(void)
{
	volatile uint32_t readADCGDRdata=0,channelno=0;

	/* Reading the global data register into a variable and clearing current interrupt/re-enabling for next interrupt */
	readADCGDRdata = LPC_ADC->ADGDR;

	/* Extracting the channel no from the global data register which is in 26:24 bits */
	channelno = (readADCGDRdata >> 24) & 0x07;

	/* Extracting the adc result from the global data register which is in 15:4 bits */
	adcresult[channelno] = (readADCGDRdata >> 4) & 0xFFF;

}

/**
  * @brief  Initialize all the hardware connected
  * @retval none
  */
void vAppHardwareInit(void)
{
	vPinmuxInitialize();
	vLCDInitialize();
	vLCDInitialCommands();
	vADCInitialize();

}

/**
  * @brief  Crude Delay
  * @retval none
  */
void vAppDelay(uint32_t count)
{
	int i,j;
	for(i=0;i<count;i++)
		for(j=0;j<0xA00;j++);
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
	uint32_t delaycount=0,channelno=0;

  /* Initialize all configured peripherals */
   vAppHardwareInit();

   /* Disabling the burst mode as we are going to use software controlled starting mechanism */
   vADCBurstMode(BURSTDISABLE);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)  // for(;;)
  {

  delaycount++;
		switch (delaycount) {
		case CLEARTIMEOUT:
			vLCDClear();
			break;
		case CONVTIMEOUT:
			/* Select the channel no 0 for conversion */
			vADCChannelSel(ADCCHAN0);
			/* Start the conversion now */
			vADCStartConv(START_NOW);

			break;
		case DISPTIMEOUT:
			/* Displaying the result on the LCD */
			vLCDGotoxy(LINE0,COL0);
			vLCDPrintf("A[%d]=%d",0,adcresult[0]);
			delaycount=0;
			break;

		default:
			/* DO NOTHING */
			break;
		}

  }
  /* End of Application entry point */
}




