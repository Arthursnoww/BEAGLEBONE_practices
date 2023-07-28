#include "interrupt.h"
#include "timer.h"

static int blink_mode;
bool flag_timer;

/*Configura a máscara de interrupção*/
/*
    0--31 INTC_MIR_CLEAR0
    32--63 INTC_MIR_CLEAR1
    64--95 INTC_MIR_CLEAR2
    96--127 INTC_MIR_CLEAR3
    */
int Isrconfig(gpioIntNum num){
    if((num >= 0) && (num <= 127)){
        int val_temp = num / 32;
        int val_temp2;
        if(val_temp==0){
            HWREG(SOC_AINTC_REGS+INTC_MIR_CLEAR0) |= (1<<num);
        }else if(val_temp==1){
            val_temp2 = 32-num;
            if(val_temp2<0){
                val_temp2 = (-1*val_temp2);
            }
            HWREG(SOC_AINTC_REGS+INTC_MIR_CLEAR1) |= (1<<val_temp2);
        }else if(val_temp==2){
            val_temp2 = 64-num;
            if(val_temp2<0){
                val_temp2 = (-1*val_temp2);
            }
            HWREG(SOC_AINTC_REGS+INTC_MIR_CLEAR2) |= (1<<val_temp2);

        }else if(val_temp==3){
            val_temp2 = 96-num;
            if(val_temp2<0){
                val_temp2 = (-1*val_temp2);
            }
            HWREG(SOC_AINTC_REGS+INTC_MIR_CLEAR3) |= (1<<val_temp2);
        }
        
       
        setBlinkMode(0);
        set_timer_flag(false);

        return 1;
    }
    return -1;
     
}

void ISR_Handler(){
    unsigned int irq_number = HWREG(SOC_AINTC_REGS+INTC_SIR_IRQ) & 0x7f;
    switch (irq_number){
        case GPIO1A:
            gpioIsrHandler_1A();
    break;
        case GPIO1B:
            gpioIsrHandler_1B();
    break;
        case GPIO3A:
            gpioIsrHandler_3A();
    break;
        case GPIO3B:
            gpioIsrHandler_3B();
    break;
        case GPIO2A:
            gpioIsrHandler_2A();
    break;
        case GPIO2B:
            gpioIsrHandler_2B();
    break;
        case GPIO0A:
            gpioIsrHandler_0A();
    break;
        case GPIO0B:
            gpioIsrHandler_0B();
    break;
        case TINT7:
            timerIrqHandler();
    }
    
	HWREG(SOC_AINTC_REGS+INTC_CONTROL) = 0x1;
}

/*Configura interrupção num certo pino*/
void pinGPIOinterrupt(gpioMod mod, ucPinNumber pin, char c){
    switch (mod){
        case GPIO0:
            if(c=='a' || c=='A'){
                HWREG(SOC_GPIO_0_REGS+GPIO_IRQSTATUS_SET_0) |= (1<<pin);
            }else{
                HWREG(SOC_GPIO_0_REGS+GPIO_IRQSTATUS_SET_1) |= (1<<pin);
            }
        
            HWREG(SOC_GPIO_0_REGS+GPIO_RISINGDETECT) |= (1<<pin);
        break;
        
        case GPIO1:
            if(c=='a' || c=='A'){
                HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_SET_0) |= (1<<pin);
            }else{
                HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_SET_1) |= (1<<pin);
            }
            HWREG(SOC_GPIO_1_REGS+GPIO_RISINGDETECT) |= (1<<pin);
        break;
        
        case GPIO2:
            if(c=='a' || c=='A'){
                HWREG(SOC_GPIO_2_REGS+GPIO_IRQSTATUS_SET_0) |= (1<<pin);
            }else{
                HWREG(SOC_GPIO_2_REGS+GPIO_IRQSTATUS_SET_1) |= (1<<pin);
            }
            HWREG(SOC_GPIO_2_REGS+GPIO_RISINGDETECT) |= (1<<pin);
        break;

        case GPIO3:
            if(c=='a' || c=='A'){
                HWREG(SOC_GPIO_3_REGS+GPIO_IRQSTATUS_SET_0) |= (1<<pin);
            }else{
                HWREG(SOC_GPIO_3_REGS+GPIO_IRQSTATUS_SET_1) |= (1<<pin);
            }
            HWREG(SOC_GPIO_3_REGS+GPIO_RISINGDETECT) |= (1<<pin);
        break;
    }
}

void gpioIsrHandler_1A(void){
    /* Clear the status of the interrupt flags */
    HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_0) |= (1<<28);

    setBlinkMode(1);
    
}
void gpioIsrHandler_0A(void){

}
void gpioIsrHandler_0B(void){

}
void gpioIsrHandler_1B(void){

}
void gpioIsrHandler_2A(void){
    /* Clear the status of the interrupt flags */
    HWREG(SOC_GPIO_2_REGS+GPIO_IRQSTATUS_0) |= (1<<28);

    setBlinkMode(2);
}
void gpioIsrHandler_2B(void){

}
void gpioIsrHandler_3A(void){

}
void gpioIsrHandler_3B(void){

}

void timerIrqHandler(void){

    /* Clear the status of the interrupt flags */
	HWREG(SOC_DMTIMER_7_REGS+DMTIMER_IRQSTATUS) = 0x2; 

	set_timer_flag(true);

    /* Stop the DMTimer */
	DMTimerDisable(SOC_DMTIMER_7_REGS);

}

int getBlinkMode(){
    return blink_mode;
}

void setBlinkMode(int mode) {
    blink_mode = mode;
}

void set_timer_flag(bool mod){
    flag_timer = mod;
}

bool getTimer_flag(){
    return flag_timer;
}


