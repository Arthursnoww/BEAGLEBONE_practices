#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "gpio.h"


typedef enum _gpioIntNum{
    TINT7 = 95,
    GPIO0A = 96,
    GPIO0B = 97,
    GPIO1A = 98,
    GPIO1B = 99,
    GPIO2A = 32,
    GPIO2B = 33,
    GPIO3A = 62,
    GPIO3B = 63

}gpioIntNum;

#define INTC_REVISION	                    (0x0)
#define INTC_SYSCONFIG	                    (0x10)
#define INTC_SYSSTATUS	                    (0x14)
#define INTC_SIR_IRQ	                    (0x40)
#define INTC_SIR_FIQ	                    (0x44)
#define INTC_CONTROL	                    (0x48)
#define INTC_PROTECTION	                    (0x4C)
#define INTC_IDLE	                        (0x50)
#define INTC_IRQ_PRIORITY	                (0x60)
#define INTC_FIQ_PRIORITY	                (0x64)
#define INTC_THRESHOLD	                    (0x68)
#define INTC_ITR0	                        (0x80)
#define INTC_MIR0	                        (0x84)
#define INTC_MIR_CLEAR0	                    (0x88)
#define INTC_MIR_SET0	                    (0x8C)
#define INTC_ISR_SET0	                    (0x90)
#define INTC_ISR_CLEAR0	                    (0x94)
#define INTC_PENDING_IRQ0	                (0x98)
#define INTC_PENDING_FIQ0	                (0x9C)
#define INTC_ITR1	                        (0xA0)
#define INTC_MIR1	                        (0xA4)
#define INTC_MIR_CLEAR1	                    (0xA8)
#define INTC_MIR_SET1	                    (0xAC)
#define INTC_ISR_SET1	                    (0xB0)
#define INTC_ISR_CLEAR1	                    (0xB4)
#define INTC_PENDING_IRQ1	                (0xB8)
#define INTC_PENDING_FIQ1	                (0xBC)
#define INTC_ITR2	                        (0xC0)
#define INTC_MIR2	                        (0xC4)
#define INTC_MIR_CLEAR2	                    (0xC8)
#define INTC_MIR_SET2	                    (0xCC)
#define INTC_ISR_SET2	                    (0xD0)
#define INTC_ISR_CLEAR2	                    (0xD4)
#define INTC_PENDING_IRQ2	                (0xD8)
#define INTC_PENDING_FIQ2	                (0xDC)
#define INTC_ITR3	                        (0xE0)
#define INTC_MIR3	                        (0xE4)
#define INTC_MIR_CLEAR3	                    (0xE8)
#define INTC_MIR_SET3	                    (0xEC)
#define INTC_ISR_SET3	                    (0xF0)
#define INTC_ISR_CLEAR3	                    (0xF4)
#define INTC_PENDING_IRQ3	                (0xF8)
#define INTC_PENDING_FIQ3	                (0xFC)

void ISR_Handler(void);
int Isrconfig(gpioIntNum);
void pinGPIOinterrupt(gpioMod, ucPinNumber, char);
int getBlinkMode();
void setBlinkMode(int);
void gpioIsrHandler_1A();
void gpioIsrHandler_1B();
void gpioIsrHandler_3A();
void gpioIsrHandler_3B();
void gpioIsrHandler_2A();
void gpioIsrHandler_2B();
void gpioIsrHandler_0A();
void gpioIsrHandler_0B();
void timerIrqHandler();
void set_timer_flag(bool);
bool getTimer_flag();


#endif