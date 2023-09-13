

#ifndef ADC_H_
#define ADC_H_

/* Private includes ----------------------------------------------------------*/
#include "configboard.h"
/* Private typedef -----------------------------------------------------------*/
enum {POWERDOWN=0,OPERATIONAL};
enum {GLOBALINTDISABLE=0, GLOBALINTENABLE};
enum {ADCINTDISABLE=0, ADCINTENABLE};
enum {ADCCHAN0=0,ADCCHAN1,ADCCHAN2,ADCCHAN3,ADCCHAN4,ADCCHAN5,ADCCHAN6,ADCCHAN7};
enum {BURSTDISABLE=0,BURSTENABLE};
enum {NO_START=0,START_NOW,START_EINTO,START_CAP0_1,START_MAT0_1,START_MAT0_3,START_MAT1_0,START_MAT1_1};

/* Private define ------------------------------------------------------------*/

/*Bits in A/D Control Register (AD0CR - address 0x4003 4000)*/
#define BIT_AD0CR_SEL		 0
#define BIT_AD0CR_CLKDIV	 8
#define BIT_AD0CR_BURST	    16
#define BIT_AD0CR_PDN		21
#define BIT_AD0CR_START		24
#define BIT_AD0CR_EDGE		27

/*Bits in A/D Global Data Register (AD0GDR - address 0x4003 4004)*/
#define BIT_AD0GDR_RESULT	 4
#define BIT_AD0GDR_CHN		24
#define BIT_AD0GDR_OVERRUN	30
#define BIT_AD0GDR_DONE		31

/*Bits in A/D Interrupt Enable register (AD0INTEN - address 0x4003 400C)*/
#define BIT_AD0INTEN_ADINTEN0	0
#define BIT_AD0INTEN_ADINTEN1	1
#define BIT_AD0INTEN_ADINTEN2	2
#define BIT_AD0INTEN_ADINTEN3	3
#define BIT_AD0INTEN_ADINTEN4	4
#define BIT_AD0INTEN_ADINTEN5	5
#define BIT_AD0INTEN_ADINTEN6	6
#define BIT_AD0INTEN_ADINTEN7	7
#define BIT_AD0INTEN_ADGINTEN	8


/*Bits in A/D Data Registers (AD0DR0 - 0x4003 4010)*/
#define BIT_AD0DR0_RESULT	 4
#define BIT_AD0DR0_OVERRUN	30
#define BIT_AD0DR0_DONE		31

/*Bits in A/D Data Registers (AD0DR1 - 0x4003 4014)*/
#define BIT_AD0DR1_RESULT	 4
#define BIT_AD0DR1_OVERRUN	30
#define BIT_AD0DR1_DONE		31

/*Bits in A/D Data Registers (AD0DR2 - 0x4003 4018)*/
#define BIT_AD0DR2_RESULT	 4
#define BIT_AD0DR2_OVERRUN	30
#define BIT_AD0DR2_DONE		31

/*Bits in A/D Data Registers (AD0DR3 - 0x4003 401C)*/
#define BIT_AD0DR3_RESULT	 4
#define BIT_AD0DR3_OVERRUN	30
#define BIT_AD0DR3_DONE		31

/*Bits in A/D Data Registers (AD0DR4 - 0x4003 4020)*/
#define BIT_AD0DR4_RESULT	 4
#define BIT_AD0DR4_OVERRUN	30
#define BIT_AD0DR4_DONE		31

/*Bits in A/D Data Registers (AD0DR5 - 0x4003 4024)*/
#define BIT_AD0DR5_RESULT	 4
#define BIT_AD0DR5_OVERRUN	30
#define BIT_AD0DR5_DONE		31

/*Bits in A/D Data Registers (AD0DR6 - 0x4003 4028)*/
#define BIT_AD0DR6_RESULT	 4
#define BIT_AD0DR6_OVERRUN	30
#define BIT_AD0DR6_DONE		31

/*Bits in A/D Data Registers (AD0DR7 - 0x4003 402C)*/
#define BIT_AD0DR7_RESULT	 4
#define BIT_AD0DR7_OVERRUN	30
#define BIT_AD0DR7_DONE		31

/*Bits in A/D Status register (AD0STAT - address 0x4003 4030)*/
#define BIT_AD0STAT_DONE0		 0
#define BIT_AD0STAT_DONE1		 1
#define BIT_AD0STAT_DONE2		 2
#define BIT_AD0STAT_DONE3		 3
#define BIT_AD0STAT_DONE4		 4
#define BIT_AD0STAT_DONE5		 5
#define BIT_AD0STAT_DONE6		 6
#define BIT_AD0STAT_DONE7		 7
#define BIT_AD0STAT_OVERRUN0	 8
#define BIT_AD0STAT_OVERRUN1	 9
#define BIT_AD0STAT_OVERRUN2	10
#define BIT_AD0STAT_OVERRUN3	11
#define BIT_AD0STAT_OVERRUN4	12
#define BIT_AD0STAT_OVERRUN5	13
#define BIT_AD0STAT_OVERRUN6	14
#define BIT_AD0STAT_OVERRUN7	15
#define BIT_AD0STAT_ADINT		16

/*Bits in A/D Trim register (ADTRM - address 0x4003 4034)*/
#define BIT_ADTRM_ADCOFFS	4
#define BIT_ADTRM_TRIM		8




/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief     ADC Initialization
 * @return    No return value
 **/
void vADCInitialize(void);

/**
 * @brief     Selecting the ADC Power down mode
 * @param[in] burstmode value can be POWERDOWN,OPERATIONAL
 * @return    No return value
 **/
void vADCPowerdown(uint8_t powerdownmode);

/**
 * @brief     Selecting the ADC Clock divider value
 * @param[in] clkdiv value divisor value for dividing the peripheral clock value less than or equal to 13MHz
 * @return    No return value
 **/
void vADCClockDiv(uint8_t clkdiv);

/**
 * @brief     Selecting the ADC Channel for conversion
 * @param[in] channelno value can be ADCCHAN0,ADCCHAN1,ADCCHAN2,ADCCHAN3,ADCCHAN4,ADCCHAN5,ADCCHAN6,ADCCHAN7
 * @return    No return value
 **/
void vADCChannelSel(uint8_t channelno);

/**
 * @brief     Selecting the ADC Burst Mode
 * @param[in] burstmode value can be BURSTDISABLE,BURSTENABLE
 * @return    No return value
 **/
void vADCBurstMode(uint8_t burstmode);

/**
 * @brief     Selecting the ADC Start mode
 * @param[in] value can be NO_START=0,START_NOW,START_EINTO,START_CAP0_1,
 * 			                         START_MAT0_1,START_MAT0_3,START_MAT1_0,START_MAT1_1
 * @return    No return value
 **/
void vADCStartConv(uint8_t startmode);

/**
 * @brief     Enabling and Disabling Global interrupt of ADC
 * @param[in] interruptmode value can be either GLOBALINTDISABLE, GLOBALINTENABLE
 * @return    No return value
 **/

void vADCGlobalInterrupt(uint8_t interruptmode);

/**
 * @brief     Enabling and Disabling individual channel interrupt of ADC
 * @param[in] channelno value can be ADCCHAN0,ADCCHAN1,ADCCHAN2,ADCCHAN3,ADCCHAN4,ADCCHAN5,ADCCHAN6,ADCCHAN7
 * @param[in] interruptmode value can be either ADCINTDISABLE, ADCINTENABLE
 * @return    No return value
 **/

void vADCChannelInterrupt(uint8_t channelno,uint8_t interruptmode);



#endif /* ADC_H_ */
