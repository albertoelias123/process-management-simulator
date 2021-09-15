//
// Created by alber on 09/09/2021.
//

#ifndef FROMZERO_MANAGER_H
#define FROMZERO_MANAGER_H

#include "Estruturas/TabelaProcessos.h"
#include "Estruturas/filaEstatica.h"
#include "Estruturas/CPU.h"

//#define _DEBUG
#ifdef _DEBUG
#define Debug(f_, ...) printf((f_), ##__VA_ARGS__)
#else
#define Debug(f_, ...)
#endif


typedef struct{
    int *pipeControlToManager;
    int *pipeManagerToControl;
    pid_t PID;

    int time;
    TabelaDeProcessos *tabela;
    Fila *processosProntos;
    Fila *processosBloqueados;
    int processoEmExecucao;
    CPU *cpu;

    int timeProcessAbsolut;
    int pidAutoIncrement;
}manager;

void loopManager(manager *pManager);
void setupManager(manager* pManager, int *pipeControlToManager, int* pipeManagerToControl);
void comandL(manager *pManager);
void executa(manager *pManager);
void averageTime(manager *pManager);
void timeIncrement(manager *pManager);
void imprimeManager(manager *pManager); // fazer os imprime tudo

#endif //FROMZERO_MANAGER_H
