#include "turnstile.h"

unsigned int populacao;
unsigned int Tam_total = 10;
unsigned int start_flag = 0;
//Funções para chamar na interrupção

//Pessoa saiu do ambiente
void PessoaSai(){
    HWREG(SOC_GPIO_2_REGS+GPIO_IRQSTATUS_0) |= (1<<28);
    if(populacao > 0 && populacao < Tam_total/2){
        populacao--;
        PessoaSai_Interface();
    }else if(populacao >= Tam_total/2 && populacao > 0){
        populacao--;
        SalaQCheia_Interface_saiu();
    }else{
        SalaLimpa_Interface();
    }
}

//Pessoa entrou no ambiente
void PessoaEntra(){
    HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_0) |= (1<<28);
    if(populacao > Tam_total/2 && populacao < Tam_total){
        populacao++;
        PessoaEntra_Interface();
    }else if(populacao > Tam_total/2 && populacao < Tam_total){
        populacao++;
        SalaQCheia_Interface_entrou();
    }else{
        SalaCheia_Interface();
    }
}

//Retorna a quantidade de pessoas no ambiente
unsigned int ocupacao(){
    return populacao;
}

//Retorna o tamanho ocupado do ambiente
int tam_ocupado(){
    if(ocupacao()==Tam_total){
        return 2;
    }else if(ocupacao()>=(Tam_total/2)){
        return 0;
    }else{
        return 1;
    }
}

//Reseta o ambiente
void reset(){
    HWREG(SOC_GPIO_2_REGS+GPIO_IRQSTATUS_1) |= (1<<28);
    populacao = 0;
    start_flag = 0;
    SalaLimpa_Interface();
}

//Starta o programa
void start(){
    HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_1) |= (1<<28);
    populacao = 0;
    start_flag = 1;
    BemVindo_Interface();
}

//Retorna se o programa
unsigned int get_start(){
    return start_flag; 
}