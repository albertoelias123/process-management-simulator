//
// Created by alber on 09/09/2021.
//

#ifndef FROMZERO_MANAGER_H
#define FROMZERO_MANAGER_H

#include "Estruturas/CPU.h"

//#define _DEBUG
#ifdef _DEBUG
#define Debug(f_, ...) printf((f_), ##__VA_ARGS__)
#else
#define Debug(f_, ...)
#endif

typedef struct{
    int *pipe;
    pid_t PID;


    int time;
    TabelaDeProcessos tabela;
    EstadoPronto estadoPronto;
    EstadoBloqueado estadoBloqueado;
    EstadoExecucao estadoExecucao;
    CPU cpu;

}manager;




void loopManager(manager *pManager);
void setupManager(manager* pManager, int* pipe);

#endif //FROMZERO_MANAGER_H
