//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_CPU_H
#define ESTRUTURAS_CPU_H

#include "simulatedProcess.h"

#define TAM_REGISTRADOR 4

//1 2 3 4 5
// a 0 10
// a 0 20
// s 0 30
// a 1 10
// a 2 10

//primeiro salva a operação na mem processo a na posicao 0 o valor 0
//mudou de processo, pega tudo do registrador e carrega na memoria do processo A

//coloca os dados do processo B para a CPU
//comeca a executar os valores da mem do processo B no registrador


//quando for copiar da tabela de processos para a CPU

// now we want to copy a to b
//memcpy(&b, &a, sizeof b);

typedef struct{
    process processoExecucao;
    int timeSlice;//fatia de tempo do processo em execução na CPU
    int timeUsed; //tempo usado do timeSlice
}CPU;


CPU *criaCPU();
void executa(CPU *cpu);
void sum(process *processOnCpu);
void sub(process *processOnCpu);
void printCPU(CPU *cpu);



#endif //ESTRUTURAS_CPU_H
