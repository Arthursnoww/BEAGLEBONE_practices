#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "uart.h"
#include "hw_types.h"
#include "soc_AM335x.h"

void BemVindo_Interface();
void PessoaEntra_Interface();
void PessoaSai_Interface();
void SalaQCheia_Interface_saiu();
void SalaCheia_Interface();
void SalaLimpa_Interface();
void SalaQCheia_Interface_entrou();

#endif