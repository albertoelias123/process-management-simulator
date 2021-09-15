//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_CPU_H
#define ESTRUTURAS_CPU_H

#include "simulatedProcess.h"
//#include "../manager.h"


typedef struct{
    process processoExecucao;
    int timeSlice;//fatia de tempo do processo em execução na CPU
    int timeUsed; //tempo usado do timeSlice
}CPU;

CPU *criaCPU();
void sum(process *processOnCpu);
void sub(process *processOnCpu);
void printCPU(CPU *cpu);



#endif //ESTRUTURAS_CPU_H
