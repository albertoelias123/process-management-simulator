//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_PILHAESTATICA_H
#define ESTRUTURAS_PILHAESTATICA_H

#define MAXTAM 1000

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valor;
    //outras variaveis
}TipoChave;

typedef struct{
    TipoChave item[MAXTAM];
    int topo;
}Pilha;

Pilha *criaPilha();
int pEVazia(Pilha *p);
int pECheia(Pilha *p);
void insereOnPilha(Pilha *p, TipoChave chave);
void imprimePilha(Pilha p);
TipoChave removeOfPilha(Pilha *p);
#endif //ESTRUTURAS_PILHAESTATICA_H
