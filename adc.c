

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
#include "adc.h"
#include "clock.h"
#include "powercontrol.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

 /**
  * @brief     Setting power ON/OFF for ADC Peripheral
  * @param[in] mode value can be either POWERON/ POWEROFF
  * @return    No return value
  **/
void vADCPowerControl(uint8_t mode)
{
	if(mode==POWERON)
		LPC_SC->PCONP |= 1<<BIT_PCONP_PCADC;
	else if(mode ==POWEROFF)
		LPC_SC->PCONP &= ~(1<<BIT_PCONP_PCADC);
}

/**
 * @brief     Setting clock for ADC Peripheral
 * @param[in] clockmode value can be ONEFOURTH,SAME,HALF,ONEEIGTH
 * @return    No return value
 **/
void vADCClockControl(uint8_t clockmode)
{
	LPC_SC->PCLKSEL0 &= ~(3<<BIT_PCLKSEL0_PCLK_ADC);
	switch(clockmode)
	{
		case ONEFOURTH:
			/*DO NOTHING */
			break;
		case SAME:
			LPC_SC->PCLKSEL0 |= 1<<BIT_PCLKSEL0_PCLK_ADC;
			break;
		case HALF:
			LPC_SC->PCLKSEL0 |= 2<<BIT_PCLKSEL0_PCLK_ADC;
			break;
		case ONEEIGTH:
			LPC_SC->PCLKSEL0 |= 3<<BIT_PCLKSEL0_PCLK_ADC;
			break;
	}
}

/**
 * @brief     Selecting the ADC Power down mode
 * @param[in] burstmode value can be POWERDOWN,OPERATIONAL
 * @return    No return value
 **/
void vADCPowerdown(uint8_t powerdownmode)
{
	if(powerdownmode==OPERATIONAL)
		 LPC_ADC->ADCR = 1<<BIT_AD0CR_PDN;
	else if(powerdownmode ==POWERDOWN)
		 LPC_ADC->ADCR &= ~(1<<BIT_AD0CR_PDN);
}

/**
 * @brief     Selecting the ADC Clock divider value
 * @param[in] clkdiv value divisor value for dividing the peripheral clock value less than or equal to 13MHz
 * @return    No return value
 **/
void vADCClockDiv(uint8_t clkdiv)
{
	    LPC_ADC->ADCR |= (clkdiv-1)<<BIT_AD0CR_CLKDIV;
}

/**
 * @brief     Selecting the ADC Channel for conversion
 * @param[in] channelno value can be ADCCHAN0,ADCCHAN1,ADCCHAN2,ADCCHAN3,ADCCHAN4,ADCCHAN5,ADCCHAN6,ADCCHAN7
 * @return    No return value
 **/
void vADCChannelSel(uint8_t channelno)
{
	 LPC_ADC->ADCR &= ~(0xFF<<BIT_AD0CR_SEL);
	 LPC_ADC->ADCR |= 1<<channelno;
}


/**
 * @brief     Selecting the ADC Burst Mode
 * @param[in] burstmode value can be BURSTDISABLE,BURSTENABLE
 * @return    No return value
 **/
void vADCBurstMode(uint8_t burstmode)
{
	if(burstmode==BURSTENABLE)
		 LPC_ADC->ADCR |= 1<<BIT_AD0CR_BURST;
	else if(burstmode ==BURSTDISABLE)
		 LPC_ADC->ADCR &= ~(1<<BIT_AD0CR_BURST);
}

/**
 * @brief     Selecting the ADC Start mode
 * @param[in] value can be NO_START=0,START_NOW,START_EINTO,START_CAP0_1,
 * 			                         START_MAT0_1,START_MAT0_3,START_MAT1_0,START_MAT1_1
 * @return    No return value
 **/
void vADCStartConv(uint8_t startmode)
{
	     LPC_ADC->ADCR &= ~(7<<BIT_AD0CR_START);
		 LPC_ADC->ADCR |= startmode<<BIT_AD0CR_START;
}

/**
 * @brief     Enabling and Disabling Global interrupt of ADC
 * @param[in] interruptmode value can be either GLOBALINTDISABLE, GLOBALINTENABLE
 * @return    No return value
 **/

void vADCGlobalInterrupt(uint8_t interruptmode)
{
	if(interruptmode==GLOBALINTDISABLE)
		LPC_ADC->ADINTEN &= ~(1<<BIT_AD0INTEN_ADGINTEN);
	else if(interruptmode==GLOBALINTENABLE)
		LPC_ADC->ADINTEN |= 1<<BIT_AD0INTEN_ADGINTEN;

}

/**
 * @brief     Enabling and Disabling individual channel interrupt of ADC
 * @param[in] channelno value can be ADCCHAN0,ADCCHAN1,ADCCHAN2,ADCCHAN3,ADCCHAN4,ADCCHAN5,ADCCHAN6,ADCCHAN7
 * @param[in] interruptmode value can be either ADCINTDISABLE, ADCINTENABLE
 * @return    No return value
 **/

void vADCChannelInterrupt(uint8_t channelno,uint8_t interruptmode)
{
	if(interruptmode==ADCINTDISABLE)
		LPC_ADC->ADINTEN &= ~(1<<channelno);
	else if(interruptmode==ADCINTENABLE)
		LPC_ADC->ADINTEN |= 1<<channelno;

}



/**
 * @brief     ADC Initialization
 * @return    No return value
 **/
void vADCInitialize(void)
{
	/*********************************BASIC CONFIGURATION***************************************/
		/* Step 1: Powering the ADC first set the PCADC bit and then enable PDN in AD0CR */
		vADCPowerControl(POWERON);
		vADCPowerdown(OPERATIONAL);

		/* Step 2: Selecting the clock frequency for the ADC Peripheral */
		vADCClockControl(ONEFOURTH);

		/* Here 25MHz/4 = 6.25Mhz */
		vADCClockDiv(4);

		/* Step 3: Selected the pins for ADC Channels */
			/* Already done inside vPinmuxInitialize */

		/* Step 4: Enabling Interrupt for ADC Peripheral */
		vADCGlobalInterrupt(GLOBALINTENABLE);
		/* Enabling the ADC interrupt in NVIC */
		NVIC_EnableIRQ(ADC_IRQn);


		/* Step 5: Configuring GPDMA  */
			/* Not used in this program */
	 /****************************************************************************************************/
}


