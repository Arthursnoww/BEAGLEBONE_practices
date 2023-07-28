#ifndef TURNSTILE_H_
#define TURNSTILE_H_

#include "interrupt.h"
#include "interface.h"

void PessoaSai();
void PessoaEntra();
unsigned int ocupacao();
int tam_ocupado();
void reset();
void start();
unsigned int get_start();

#endif