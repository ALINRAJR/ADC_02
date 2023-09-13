

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Private includes ----------------------------------------------------------*/
#include "configboard.h"
#include "clock.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

#if configClock

/**
  * @brief     Clock Initialization to the user desired frequency
  * @return    No return value
  **/
void vClockInitialization(void)
{

	/* Step1: Checking whether the main oscillator is enabled and ready before selecting it as PLL Clock Source */
			LPC_SC->SCS = 0 << BIT_SCS_OSCRANGE | 1 << BIT_SCS_OSCEN;

			if (LPC_SC->SCS & (1 << BIT_SCS_OSCEN)) { /* If Main Oscillator is enabled      */
				while ((LPC_SC->SCS & (1 << BIT_SCS_OSCSTAT)) == 0);/* Wait for Oscillator to be ready */
			}

	/* Step2: Selecting the clock source as the main oscillator */
			LPC_SC->CLKSRCSEL = CURRENT_OSCSEL << BIT_CLKSRCSEL_CLKSRC;

	/* Step3: PLL Configurations */
	/* Step3.1: PLL Configuration by providing M and N values for the FCCO calculated from excel sheet */
			LPC_SC->PLL0CFG = (CURRENT_MSEL - 1) << BIT_PLL0CFG_MSEL0 | (CURRENT_NSEL - 1) << BIT_PLL0CFG_NSEL0;

	/* Step3.2: Feed sequence to be applied for every change in PLL Control and Configuration register */
			LPC_SC->PLL0FEED = 0xAA; //1010 1010
			LPC_SC->PLL0FEED = 0x55; //0101 0101

	/* Step3.3: Enabling the PLL register */
			LPC_SC->PLL0CON = 1 << BIT_PLL0CON_PLLE0;

	/* Step3.4: Feed sequence to be applied for every change in PLL Control and Configuration register */
			LPC_SC->PLL0FEED = 0xAA; //1010 1010
			LPC_SC->PLL0FEED = 0x55; //0101 0101

	/* Step3.5: Waiting for the PLL to lock for the FCCO calculated from excel sheet */
			while ((LPC_SC->PLL0STAT & 1 << BIT_PLL0STAT_PLOCK0) == 0);

	/* Step3.6: Enabling and connecting  the PLL to the system */
			LPC_SC->PLL0CON = 1 << BIT_PLL0CON_PLLE0 | 1<<BIT_PLL0CON_PLLC0;

	/* Step3.7: Feed sequence to be applied for every change in PLL Control and Configuration register */
			LPC_SC->PLL0FEED = 0xAA; //1010 1010
			LPC_SC->PLL0FEED = 0x55; //0101 0101

	/* Step4: Dividing the PLL Clock for the desired CCLK */
			LPC_SC->CCLKCFG  = (CURRENT_CCLKSEL-1)<<BIT_CCLKCFG_CCLKSEL;

	/* Step5: Dividing the CCLK for providing the desired peripheral CLK */
			LPC_SC->PCLKSEL0 = CURRENT_PCLKSEL0;
			LPC_SC->PCLKSEL1 = CURRENT_PCLKSEL1;

	/* Step6: Configuring the Clock out frequency over the CLKOUT PIN (1.27) */
			LPC_SC->CLKOUTCFG = CURRENT_CLKOUTSEL<<BIT_CLKOUTCFG_CLKOUTSEL|(CURRENT_CLKOUTDIV-1)<<BIT_CLKOUTCFG_CLKOUTDIV;
}


#endif // end of configClock
