//
// Created by pedro on 14/08/2021.
//

#ifndef PROCESS_MANAGEMENT_SIMULATOR_PROCESSO_H
#define PROCESS_MANAGEMENT_SIMULATOR_PROCESSO_H

#include "ProcessMemory.h"

typedef struct{
    pid_t  PID;
    memory memProcess;
    int priority;
}Process;


void processCreate(Process *processo,pid_t pid);//criar um novo processo simulado
void manipulateProcess(Process *processo,int posicao,int prioridade,int valor,char metodo[30]);

#endif //PROCESS_MANAGEMENT_SIMULATOR_PROCESSO_H
