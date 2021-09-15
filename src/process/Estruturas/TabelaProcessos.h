//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_TABELAPROCESSOS_H
#define ESTRUTURAS_TABELAPROCESSOS_H
#include "simulatedProcess.h"

#define TAM_VETOR_TABELA_POCESSOS 1000

typedef struct{
    process *processos[TAM_VETOR_TABELA_POCESSOS];
    int qtd;
}TabelaDeProcessos;

TabelaDeProcessos* criaTabela();
int insereOnTabela(TabelaDeProcessos *tabela,process *entrada);
void alteraEstadoParaPronto(TabelaDeProcessos *tabela, int indice);
void alteraEstadoParaExecucao(TabelaDeProcessos *tabela, int indice);
void removeOfTabela(TabelaDeProcessos *tabela,int pidProcess);
void imprimeTabela(TabelaDeProcessos *tabela);

#endif //ESTRUTURAS_TABELAPROCESSOS_H
