//
// Created by pedro on 14/08/2021.
//

#ifndef PROCESS_MANAGEMENT_SIMULATOR_FILAPROCESSOS_H
#define PROCESS_MANAGEMENT_SIMULATOR_FILAPROCESSOS_H

#include "Processo.h"

typedef struct Celulafila *processPointer;

typedef struct Celulafila{
    struct Celulafila *prox;
    Process processo;
}Celulafila;

typedef struct{
    processPointer inicio,fim;
    int tamanho;
}processList;

//Funções Arvore
void iniciaListprocess(processList *list);
void insereProcess(processList *list, Process *processo);
void removeDoinicio(processList *list);
void removeProcess(processList *list,pid_t  PID);
void imprimeProcessos(processList *list);

#endif //PROCESS_MANAGEMENT_SIMULATOR_FILAPROCESSOS_H
