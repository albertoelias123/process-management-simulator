//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_PILHAESTATICA_H
#define ESTRUTURAS_PILHAESTATICA_H

#define MAXTAM 1000

#define TRUE 1
#define FALSE 0

#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct{
    int item[MAXTAM];
    int topo;
}Pilha;

Pilha *criaPilha();
int pEVazia(Pilha *p);
int pECheia(Pilha *p);
void insereOnPilha(Pilha *p, int chave);
void imprimePilha(Pilha p);
int removeOfPilha(Pilha *p);
#endif //ESTRUTURAS_PILHAESTATICA_H
