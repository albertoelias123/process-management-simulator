//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_FILAESTATICA_H
#define ESTRUTURAS_FILAESTATICA_H

#define MAXTAM 1000

typedef struct{
    int fim;
    int chave[MAXTAM];
}Fila;

Fila *criaFila();
int filaEVazia(Fila *fila);
int filaECheia(Fila *fila);
void insereOnFila(Fila *fila,int chave);
int removeOfFila(Fila *fila);
void imprimeFila(Fila *fila);

#endif //ESTRUTURAS_FILAESTATICA_H
