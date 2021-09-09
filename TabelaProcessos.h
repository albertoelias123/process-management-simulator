//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_TABELAPROCESSOS_H
#define ESTRUTURAS_TABELAPROCESSOS_H
#include "Estados.h"
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef enum{
    bloqueado,pronto,execucao
}type;

typedef struct{
    pid_t pidPai;
    pid_t pidProcesso;
    int *PC;
    int *prioridade;
    int *estado;
    int *tempoinicio;
    int *tempoCpu;
}EntradaTabela;

typedef struct{
    EntradaTabela vetor[MAXTAM];
    int qtd;
}TabelaDeProcessos;

TabelaDeProcessos *criaTabela();
void insereOnTabela(TabelaDeProcessos *tabela,EntradaTabela *entrada);
TabelaDeProcessos *removeOfTabela(TabelaDeProcessos *tabela,pid_t pidProcess);

#endif //ESTRUTURAS_TABELAPROCESSOS_H
