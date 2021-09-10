//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_TABELAPROCESSOS_H
#define ESTRUTURAS_TABELAPROCESSOS_H
#include "Estados.h"
#include "simulatedProcess.h"

#define TAM_VETOR_TABELA_POCESSOS 1000

typedef enum{
    bloqueado,pronto,execucao
}type;

typedef struct{
    process *processos[TAM_VETOR_TABELA_POCESSOS];
    int qtd;
}TabelaDeProcessos;

TabelaDeProcessos *criaTabela();
void insereOnTabela(TabelaDeProcessos *tabela,process *entrada);
void removeOfTabela(TabelaDeProcessos *tabela,int pidProcess);

#endif //ESTRUTURAS_TABELAPROCESSOS_H
