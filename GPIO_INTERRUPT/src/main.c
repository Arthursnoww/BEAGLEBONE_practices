/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "interrupt.h"


/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define WDT_WSPR			0x48
#define WDT_WWPS			0x34
#define W_MASK				(1<< 0x4u)

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
void ledON(gpioMod  ,ucPinNumber );
void ledOFF(gpioMod ,ucPinNumber );
void disablewatchdog();
void ledSequence01();
void ledSequence02();
void ledSequence03();
	
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	ucPinNumber port0=13;//saida
	ucPinNumber port1=12;//saida
	ucPinNumber port3=14;//saida
	ucPinNumber port5=15;//saida
	ucPinNumber port2=28;//entrada
	ucPinNumber port4=1;//entrada
	pinDirection dir=INPUT;
	pinDirection dir2=OUTPUT;

	/*-----------------------------------------------------------------------------
	 *  disable Watchdog-reset
	 *-----------------------------------------------------------------------------*/
	disablewatchdog();

	/*-----------------------------------------------------------------------------
	 *  initialize UART modules
	 *-----------------------------------------------------------------------------*/
	uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);

	/*-----------------------------------------------------------------------------
	 *  initialize TIMER modules
	 *-----------------------------------------------------------------------------*/
    DMTimerSetUp();
	
	/*-----------------------------------------------------------------------------
	 *  initialize GPIO modules
	 *-----------------------------------------------------------------------------*/
	gpioInitModule(GPIO1);
	gpioInitModule(GPIO2);
	
	/*-----------------------------------------------------------------------------
	 *  configure multplex in the pin of mudule
	 *-----------------------------------------------------------------------------*/
	gpioInitPin(GPIO1, port2);
	gpioInitPin(GPIO1, port0);
	gpioInitPin(GPIO1, port1);
	gpioInitPin(GPIO1, port3);
	gpioInitPin(GPIO2, port4);
	
	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	gpioSetDirection(GPIO1, port2, dir);
	gpioSetDirection(GPIO2, port4, dir);
	gpioSetDirection(GPIO1, port0, dir2);
	gpioSetDirection(GPIO1, port1, dir2);
	gpioSetDirection(GPIO1, port3, dir2);

	/*-----------------------------------------------------------------------------
	 *  configure gpio interrupt number
	 *-----------------------------------------------------------------------------*/
	Isrconfig(GPIO1A);
	Isrconfig(GPIO2A);
	Isrconfig(TINT7);

	/*-----------------------------------------------------------------------------
	 *  configure pin interrupt 
	 *-----------------------------------------------------------------------------*/
	pinGPIOinterrupt(GPIO1, port2, 'A');
	pinGPIOinterrupt(GPIO2, port4, 'A');

  	ledOFF(GPIO1, port0);
	ledOFF(GPIO1, port1);
	ledOFF(GPIO1, port3);
	
  	while(true){
		switch (getBlinkMode())
		{
		case 0:
			ledSequence01();
			break;
		
		case 1:
			ledSequence02();
			setBlinkMode(0);
			break;

		case 2:
			ledSequence03();
			setBlinkMode(0);
			break;
		}
	}
	return(0);
} /* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledON
 *  Description:  
 * =====================================================================================
 */
void ledON(gpioMod mod, ucPinNumber pin){
	gpioSetPinValue(mod, pin, HIGH);	
}/* -----  end of function ledON  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOFF
 *  Description:  
 * =====================================================================================
 */
void ledOFF(gpioMod mod,  ucPinNumber pin ){
	gpioSetPinValue(mod, pin, LOW);
}/* -----  end of function ledOFF  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Watchdog
 *  Description:  Disable Watchdog
 * =====================================================================================
 */
void disablewatchdog(){
	HWREG(SOC_WDT_1_REGS+WDT_WSPR) = 0xAAAA;
	while((HWREG(SOC_WDT_1_REGS+WDT_WWPS) & W_MASK) != 0x0){};
	HWREG(SOC_WDT_1_REGS+WDT_WSPR) = 0x5555;
	while ((HWREG(SOC_WDT_1_REGS+WDT_WWPS) & W_MASK) != 0x0){};
}

void ledSequence01(){
	ucPinNumber port0=12;
	ucPinNumber port1=13;
	ucPinNumber port2=14;
	ledON(GPIO1, port0);
	ledON(GPIO1, port1);
	ledON(GPIO1, port2);
	Delay(1000, SOC_DMTIMER_7_REGS);
	ledOFF(GPIO1, port0);
	ledOFF(GPIO1, port1);
	ledOFF(GPIO1, port2);
	Delay(1000, SOC_DMTIMER_7_REGS);
}

void ledSequence02(){
	ucPinNumber port0=12;
	ucPinNumber port1=13;
	ucPinNumber port2=14;
	ledON(GPIO1, port0);
	Delay(1000, SOC_DMTIMER_7_REGS);
	ledOFF(GPIO1, port0);
	Delay(1000, SOC_DMTIMER_7_REGS);
	ledON(GPIO1, port1);
	Delay(1000, SOC_DMTIMER_7_REGS);
	ledOFF(GPIO1, port1);
	Delay(1000, SOC_DMTIMER_7_REGS);
	ledON(GPIO1, port2);
	Delay(1000, SOC_DMTIMER_7_REGS);
	ledOFF(GPIO1, port2);
	Delay(1000, SOC_DMTIMER_7_REGS);
}

void ledSequence03(){
	ucPinNumber port0=12;
	ucPinNumber port1=13;
	ucPinNumber port2=14;
	ledON(GPIO1, port0);
	ledON(GPIO1, port1);
	Delay(1000, SOC_DMTIMER_7_REGS);
	ledOFF(GPIO1, port0);
	ledOFF(GPIO1, port1);
	Delay(1000, SOC_DMTIMER_7_REGS);
	ledON(GPIO1, port2);
	Delay(1000, SOC_DMTIMER_7_REGS);
	ledOFF(GPIO1, port2);
	Delay(1000, SOC_DMTIMER_7_REGS);
}



