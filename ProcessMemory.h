//
// Created by pedro on 14/08/2021.
//

#ifndef PROCESS_MANAGEMENT_SIMULATOR_PROCESSMEMORY_H
#define PROCESS_MANAGEMENT_SIMULATOR_PROCESSMEMORY_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct Ponteiro *Apontador;

typedef struct Ponteiro{
    struct Ponteiro *prox;
    int index;
    int valor;
}celulaMem;

typedef struct{
    Apontador first,end;
    int tamanho;
}memory;

void startMemoryProcess(memory * mem);
void insereOnMemory(memory *mem,int posicao);
void valorOnMemory(memory *mem,int posicao,int valor);
void sum(memory *mem,int posicao,int valor);
void sub(memory *mem,int posicao,int valor);
void imprimeMemory(memory *mem);

#endif //PROCESS_MANAGEMENT_SIMULATOR_PROCESSMEMORY_H
