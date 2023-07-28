/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14/06/2023 08:04:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Arthur Roberto da Silva, arthurroberto458@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "uart.h"
#include "timer.h"

#define		PIN_BUTTON_GPIO2_1 	01
#define 	CM_PER_GPIO1		0xAC
#define 	TOGLLE				0x01
#define CM_PER_GPIO2                                                    0XB0


/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
void ledON(gpioMod  ,ucPinNumber );
void ledOFF(gpioMod ,ucPinNumber );
void ledInit_i();
void ledInit_e();



/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
	
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){

	watchdog();

	unsigned char count=9; 

	/*-----------------------------------------------------------------------------
	 *  initialize UART modules
	 *-----------------------------------------------------------------------------*/
	uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);


	//setando o pino referente ao botao como entrada - gpio1_28 (P9, 12)
	gpioSetDirection(GPIO2, 1, INPUT);

	ledInit_i();
	ledInit_e();
	
    	DMTimerSetUp();

	while(1){
		ledON(GPIO1, 21);
		Delay(1000);
		ledOFF(GPIO1, 21);
		Delay(1000);
	}

	//uartPutString(UART0,"GPIO INPUT Initialized",23);	
  	uartPutString(UART0,"Time: ",7);
  	while(count){
		uartPutC(UART0,0x30+count);
		Delay(1000);
		count--;
		uartPutC(UART0,' ');
	}
	uartPutString(UART0,"OK...",5);

	return(0);
} /* ----------  end of function main  ---------- */
void ledON(gpioMod mod, ucPinNumber pin){
				gpioSetPinValue(mod, pin, HIGH);	
}/* -----  end of function ledON  ----- */


void ledOFF(gpioMod mod,  ucPinNumber pin ){
				gpioSetPinValue(mod, pin, LOW);
}/* -----  end of function ledOFF  ----- */

void ledInit_i( ){
	
	unsigned int val_temp; 	
	HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE; // configuração de clock
	
	/*-----------------------------------------------------------------------------
	 * MULTIPLEXAR O PINO NO MODULO DE CONTROLE GPI01
	 *-----------------------------------------------------------------------------*/
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a5) |= 7; 
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a6) |= 7;
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a7) |= 7;
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a8) |= 7;
 
	/*-----------------------------------------------------------------------------
	 *  DEFINE OS PINOS COMO SAÍDA
	 *-----------------------------------------------------------------------------*/
	val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);
	val_temp &= ~(1<<21);                                                            //25.4.10 GPIO_OE Register
	val_temp &= ~(1<<22);
	val_temp &= ~(1<<23);
	val_temp &= ~(1<<24);
	HWREG(SOC_GPIO_1_REGS+GPIO_OE) = val_temp;
	
}


