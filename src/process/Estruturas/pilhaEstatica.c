//
// Created by pedro on 09/09/2021.
//

#include "pilhaEstatica.h"

Pilha *criaPilha(){
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}

int pEVazia(Pilha *p){
    if(p->topo == -1){
        return TRUE;
    }
    return FALSE;
}

int pECheia(Pilha *p){
    if(p->topo == MAXTAM - 1){
        return TRUE;
    }
    return FALSE;
}

void insereOnPilha(Pilha *p, int chave){
    if(pECheia(p)){
        printf("\nPilha cheia\n");
    }
    else{
        p->topo++;
        p->item[p->topo] = chave;
    }
}

int removeOfPilha(Pilha *p){
    int auxiliar;
    if(!pEVazia(p)){
        auxiliar = p->item[p->topo];
        p->topo--;
        return auxiliar;
    }
}

void imprimePilha(Pilha p){
    if(!pEVazia(&p)){
        int i = p.topo;
        while (i>=0){
            printf("%d\n",p.item[i]);
            i--;
        }
    }
}