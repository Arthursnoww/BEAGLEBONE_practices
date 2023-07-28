#include "interrupt.h"
#include "timer.h"
#include "turnstile.h"

bool flag_timer;
extern unsigned int Tam_total;

/*Configura a máscara de interrupção
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
        
       
        set_timer_flag(false);

        return 1;
    }
    return -1;
     
}

void ISR_Handler(){
    unsigned int irq_number = HWREG(SOC_AINTC_REGS+INTC_SIR_IRQ) & 0x7f;
    switch (irq_number){
        case GPIO1A:
            PessoaEntra();
    break;
        case GPIO1B:
            start();
    break;
        case GPIO3A:
            gpioIsrHandler_3A();
    break;
        case GPIO3B:
            gpioIsrHandler_3B();
    break;
        case GPIO2A:
            PessoaSai();
    break;
        case GPIO2B:
            reset();
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