#include "interface.h"

void BemVindo_Interface(){
    uartPutString(UART0, "\n\r\n\r\n\r",8);
    uartPutString(UART0, "***************************************************\n\r", 55);
    uartPutString(UART0, "*                                                 *\n\r", 55);
    uartPutString(UART0, "*               Bem-vindo ao Sistema              *\n\r", 55);
    uartPutString(UART0, "*                                                 *\n\r", 55);
    uartPutString(UART0, "***************************************************\n\r", 55);
    uartPutString(UART0, "\n\r\n\r\n\r",8);
}
void PessoaEntra_Interface(){
    uartPutString(UART0, "\n\r",4);
    uartPutString(UART0, "╔═════════════════════════════════════════════╗\n\r", 145);
    uartPutString(UART0, "║                                             ║\n\r", 55);
    uartPutString(UART0, "║         Uma pessoa entrou da sala           ║\n\r", 55);
    uartPutString(UART0, "║                                             ║\n\r", 55);
    uartPutString(UART0, "╚═════════════════════════════════════════════╝\n\r", 145);
    uartPutString(UART0, "\n\r",4);
}
void PessoaSai_Interface(){
    uartPutString(UART0, "\n\r",4);
    uartPutString(UART0, "╔═════════════════════════════════════════════╗\n\r", 145);
    uartPutString(UART0, "║                                             ║\n\r", 55);
    uartPutString(UART0, "║          Uma pessoa saiu da sala            ║\n\r", 55);
    uartPutString(UART0, "║                                             ║\n\r", 55);
    uartPutString(UART0, "╚═════════════════════════════════════════════╝\n\r", 145);
    uartPutString(UART0, "\n\r",4);
}
void SalaQCheia_Interface_saiu(){
    uartPutString(UART0, "\n\r",4);
    uartPutString(UART0, "┌──────────────────────────────────────────────┐\n\r", 148);
    uartPutString(UART0, "│                                              │\n\r", 56);
    uartPutString(UART0, "│       Atenção!! A sala está quase cheia      │\n\r", 59);
    uartPutString(UART0, "│             Pessoa saiu da sala              │\n\r", 56);
    uartPutString(UART0, "└──────────────────────────────────────────────┘\n\r", 148);
    uartPutString(UART0, "\n\r",4);
}
void SalaCheia_Interface(){
    uartPutString(UART0, "\n\r",4);
    uartPutString(UART0, "┌──────────────────────────────────────────────┐\n\r", 148);
    uartPutString(UART0, "│                                              │\n\r", 56);
    uartPutString(UART0, "│        Atenção!!!!! A sala está cheia        │\n\r", 59);
    uartPutString(UART0, "│                                              │\n\r", 56);
    uartPutString(UART0, "└──────────────────────────────────────────────┘\n\r", 148);
    uartPutString(UART0, "\n\r",4);
}
void SalaLimpa_Interface(){
    uartPutString(UART0, "\n\r",4);
    uartPutString(UART0, "┌──────────────────────────────────────────────┐\n\r", 148);
    uartPutString(UART0, "│                                              │\n\r", 56);
    uartPutString(UART0, "│             A sala foi esvaziada!            │\n\r", 56);
    uartPutString(UART0, "│                                              │\n\r", 56);
    uartPutString(UART0, "└──────────────────────────────────────────────┘\n\r", 148);
    uartPutString(UART0, "\n\r",4);
}

void SalaQCheia_Interface_entrou(){
    uartPutString(UART0, "\n\r",4);
    uartPutString(UART0, "┌──────────────────────────────────────────────┐\n\r", 148);
    uartPutString(UART0, "│                                              │\n\r", 56);
    uartPutString(UART0, "│       Atenção!! A sala está quase cheia      │\n\r", 59);
    uartPutString(UART0, "│             Pessoa entrou na sala            │\n\r", 56);
    uartPutString(UART0, "└──────────────────────────────────────────────┘\n\r", 148);
    uartPutString(UART0, "\n\r",4);
}