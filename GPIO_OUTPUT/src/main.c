#include	"hw_types.h"
#include	"soc_AM335x.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME															1000000
#define TOGGLE          												(0x01u)
//registradores de configuração do clock
#define CM_PER_GPIO1										0xAC // 8.1.2.1 CM_PER Registers - registrador de controle de energia (CM_PER) 
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE   						(0x2u) //Table 8-58. CM_PER_GPIO1_CLKCTRL Register Field Descriptions(USAR BIT 18)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK  					(0x00040000u)//Table 8-58. CM_PER_GPIO1_CLKCTRL Register Field Descriptions(USAR BIT 0 ou 10

#define CM_PER_GPIO2                                                    0XB0 // 
#define CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE   						(0x2u) //Table 8-59. CM_PER_GPIO2_CLKCTRL Register Field Descriptions(USAR BIT 18)
#define CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK  					(0x00040000u)//Table 8-59. CM_PER_GPIO2_CLKCTRL Register Field Descriptions(USAR BIT 0 ou 10

// endereçõs de registradores para configurar os pinos do modo de controle
#define CM_conf_gpmc_ben1      	 								0x0878
#define CM_conf_gpmc_a5         								0x0854// Table 9-8. CONTROL_MODULE REGISTERS (((
#define CM_conf_gpmc_a6         								0x0818// Table 9-8. CONTROL_MODULE REGISTERS (( pode usar do pino 1 ao 15
#define CM_conf_gpmc_a7         								0x081C// Table 9-8. CONTROL_MODULE REGISTERS ((
#define CM_conf_gpmc_a8         								0x0820// Table 9-8. CONTROL_MODULE REGISTERS ((((
#define CM_conf_gpmc_ad11                                       0x0820
#define CM_conf_gpmc_ad12         								0x0830

// endereços de registradores para configurar o watchdog
#define WDT1 													0x44E35000
#define WDT_WSPR 												0x48 // temporizador watchdog / Registro de proteção de serviço de gravação do cronômetro de vigilância 
#define WDT_WWPS												0x34 // Escrever registro de status postado / Este registrador contém os bits de postagem de gravação para todos os registradores funcionais graváveis.
#define W_PEND_WSPR												(1<< 0x4u)






// manipular diretamente os registradores GPIO correspondentes( entrada, saida, setar, limpar)
#define GPIO_OE                 								0x134 //controla a capacidade de saída/entrada para cada pino - Table 25-5. GPIO Registers
#define GPIO_CLEARDATAOUT       								0x190 // limpar dados de saida - Table 25-5. GPIO Registers
#define GPIO_SETDATAOUT         								0x194 // setar dados de saida - - Table 25-5. GPIO Registers

//variaveis temporarias para controlar o comportamento do leds
unsigned int flagBlink0;
unsigned int flagBlink1;
unsigned int flagBlink2;
unsigned int flagBlink3;
unsigned int flagBlink0_e;
unsigned int flagBlink1_e;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay(int);
static void ledInit_i();
static void ledInit_e();
static void ledToggle0();
static void ledToggle1();
static void ledToggle2();
static void ledToggle3();
static void ledToggle0_e();
static void ledToggle1_e();
static void watchdog();

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int _main(void){
	watchdog();
	flagBlink0=0;	
  	flagBlink1=0;
  	flagBlink2=0;
  	flagBlink3=0;
  	
  	flagBlink0_e = 0;
  	flagBlink1_e = 0;
  	
  	ledInit_i();
  	ledInit_e();
  	
  	int i;
  	for(i = 0; i <= 16; i++){
    	if (i == 1){
    		ledToggle0();//liga
    		ledToggle0_e();
			delay(i);
	}if (i == 2){
    		ledToggle0(); //desliga
		ledToggle1(); //liga
		ledToggle0_e();
		ledToggle1_e();
			delay(i);
	}if (i == 3){
		ledToggle0();//liga
		ledToggle1_e();
		ledToggle0_e();
			delay(i);
	}if (i == 4){
    	ledToggle0();//desliga
		ledToggle1();//desliga
		ledToggle2();//liga
		ledToggle0_e();
		ledToggle1_e();
			delay(i);
	}if (i == 5){
    		ledToggle0(); //liga
    		ledToggle1_e();
    		ledToggle0_e();
			delay(i);
	}if (i == 6){
    		ledToggle0();//desliga
		ledToggle1();//liga
		ledToggle0_e();
		ledToggle1_e();
			delay(i);
	}if (i == 7){
    		ledToggle0();//liga
    		ledToggle1_e();
		ledToggle0_e();
			delay(i);
	}if (i == 8){
    		ledToggle0();//desliga
		ledToggle1();//desliga
		ledToggle2();//desliga
		ledToggle3();//liga
		ledToggle0_e();
		ledToggle1_e();
			delay(i);
	}if (i == 9){
    		ledToggle0();//liga
    		ledToggle1_e();
		ledToggle0_e();
			delay(i);
	}if (i == 10){
    		ledToggle0();//desliga
		ledToggle1();// liga
		ledToggle0_e();
		ledToggle1_e();
			delay(i);
	}if (i == 11){
		ledToggle0();//liga
		ledToggle1_e();
		ledToggle0_e();
			delay(i);
	}if (i == 12){
    		ledToggle0();//desliga
		ledToggle1();//desliga
		ledToggle2();//liga
		ledToggle0_e();
		ledToggle1_e();
			delay(i);
	}if (i == 13){
    		ledToggle0();//liga
    		ledToggle1_e();
		ledToggle0_e();
			delay(i);
	}if (i == 14){
    		ledToggle0();//desliga
		ledToggle1();//liga
		ledToggle0_e();
		ledToggle1_e();
			delay(i);
	}if (i == 15){
    		ledToggle0();//liga
    		ledToggle1_e();
		ledToggle0_e();
			delay(i);
	}if(i == 16){
		i= 0;
		ledToggle0();//desliga
		ledToggle1();//desliga
		ledToggle2();//desliga
		ledToggle3();//desliga
		ledToggle0_e();
			delay(i);
	}
	}
	return(0);
}
/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
void delay(int i){
	volatile unsigned int ra;
	if(i < 3){
		for(ra = 0; ra < TIME; ra ++);
	}else if(i >= 3 && i < 8){
		for(ra = 0; ra < (TIME * 2); ra ++);
	}else if(i >= 8 && i < 12){
		for(ra = 0; ra < (TIME * 4); ra ++);
	}else if(i >= 12 && i < 16){
		for(ra = 0; ra < (TIME * 6); ra ++);
	}
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledInit
 *  Description:  
 * =====================================================================================
 */

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
	
}/* -----  configura o clock e o modo de operação do módulo GPIO1, configura o pino GPIO1_21 ----- */


void ledInit_e( ){
	
	unsigned int val_temp; 	
	HWREG(SOC_CM_PER_REGS+CM_PER_GPIO2) |= CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK | CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE; // configuração de clock
	
	/*-----------------------------------------------------------------------------
	 * MULTIPLEXAR O PINO NO MODULO DE CONTROLE GPI02
	 *-----------------------------------------------------------------------------*/
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_ad11) |= 7; 
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_ad12) |= 7;
 
	/*-----------------------------------------------------------------------------
	 *  DEFINE OS PINOS COMO SAÍDA
	 *-----------------------------------------------------------------------------*/
	val_temp = HWREG(SOC_GPIO_2_REGS+GPIO_OE);
	val_temp &= ~(1<<6);                                                            //25.4.10 GPIO_OE Register
	val_temp &= ~(1<<7);
	HWREG(SOC_GPIO_2_REGS+GPIO_OE) = val_temp;
	
}/* -----  configura o clock e o modo de operação do módulo GPIO2, configura o pino GPIO2_6 ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledToggle's
 *  Description:  
 * =====================================================================================
 */
void ledToggle0(){
		flagBlink0 ^= TOGGLE;
		
		if(flagBlink0){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<21;
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<21;
		}
}
void ledToggle1(){
		flagBlink1 ^= TOGGLE;
		
		if(flagBlink1){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<22;
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<22;
		}
}
void ledToggle2(){
		flagBlink2 ^= TOGGLE;

		if(flagBlink2){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<23;
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<23;
		}
}
void ledToggle3(){
		flagBlink3 ^= TOGGLE;
		
		if(flagBlink3){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<24;
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<24;
		}
}void ledToggle0_e(){
		flagBlink0_e ^= TOGGLE;

		if(flagBlink0_e){
			HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<<6;
		}else{
			HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<<6;
		}
}
void ledToggle1_e(){
		flagBlink1_e ^= TOGGLE;
		
		if(flagBlink1_e){
			HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<<7;
		}else{
			HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<<7;
		}
}

void watchdog(){
	//Table 20-119. WDT_WWPS Register Field Descriptions
	HWREG(WDT1+WDT_WSPR) = 0xAAAA; //reconfigura o registrador 

	while((HWREG(WDT1+WDT_WWPS) & W_PEND_WSPR) != 0x0){}; // garante o loop 

	HWREG(WDT1+WDT_WSPR) = 0x5555;

	while((HWREG(WDT1+WDT_WWPS) & W_PEND_WSPR) != 0x0){};

}

