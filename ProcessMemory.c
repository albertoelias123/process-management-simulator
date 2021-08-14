//
// Created by pedro on 14/08/2021.
//

#include "ProcessMemory.h"

void startMemoryProcess(memory * mem){
    mem->first = NULL;
    mem->end = NULL;
    mem->tamanho = 0;
}

void insereOnMemory(memory *mem,int posicao){
    if(mem->end == NULL){
        mem->end = (Apontador) malloc(sizeof(celulaMem));
        mem->first = mem->end;
    }
    else{
        mem->end->prox = (Apontador) malloc(sizeof(celulaMem));
        mem->end = mem->end->prox;
    }
    mem->end->index = posicao;
    mem->end->prox = NULL;
    mem->tamanho++;
}
void valorOnMemory(memory *mem,int posicao,int valor){
    Apontador aux = mem->first;
    while (aux!= NULL){
        if (aux->index == posicao){
            aux->valor = valor;
            break;
        }
        aux = aux->prox;
    }
}
void sum(memory *mem,int posicao,int valor){
    Apontador aux = mem->first;
    while (aux!= NULL){
        if (aux->index == posicao){
            aux->valor += valor;
            break;
        }
        aux = aux->prox;
    }
}
void sub(memory *mem,int posicao,int valor){
    Apontador aux = mem->first;
    while (aux!= NULL){
        if (aux->index == posicao){
            aux->valor -= valor;
            break;
        }
        aux = aux->prox;
    }
}
void imprimeMemory(memory *mem){
    Apontador aux = mem->first;
    while (aux!=NULL){
        printf("Valor = %d Index = %d\n",aux->valor,aux->index);
        aux = aux->prox;
    }
}