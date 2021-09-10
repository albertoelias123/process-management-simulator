//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_FILAESTATICA_H
#define ESTRUTURAS_FILAESTATICA_H
#include "pilhaEstatica.h"


typedef struct{
    int inicio,fim,qtd;
    TipoChave chave[MAXTAM];
}Fila;

Fila *criaFila();
int filaEVazia(Fila *fila);
int filaECheia(Fila *fila);
void insereOnFila(Fila *fila,TipoChave chave);
void removeOfFila(Fila *fila);
void imprimeFila(Fila *fila);

#endif //ESTRUTURAS_FILAESTATICA_H
