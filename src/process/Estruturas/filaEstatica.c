//
// Created by pedro on 09/09/2021.
//

#include "filaEstatica.h"

Fila *criaFila(){
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->fim = 0;
    return f;
}
int filaEVazia(Fila *fila){
    if(fila->fim == 0){
        return TRUE;
    }
    return FALSE;
}
int filaECheia(Fila *fila){
    if(fila->fim == MAXTAM-1){
        return TRUE;
    }
    return FALSE;
}
void insereOnFila(Fila *fila,int chave){
    if(filaEVazia(fila)){
        fila->chave[fila->fim++] = chave;
    }
    else{
        if(!filaECheia(fila)) {
            fila->chave[fila->fim++] = chave;
        }
        else{
            printf("\nFila cheia\n");
        }
    }
}
int removeOfFila(Fila *fila){
    if(!filaEVazia(fila)){
        int inicio = fila->chave[0];
        for (int i = 0; i < fila->fim-1; ++i) {
            fila->chave[i] = fila->chave[i+1];
        }
        fila->fim--;
        return inicio;
    }
    else{
        printf("\nFila vazia\n");
        return -1;
    }
}
void imprimeFila(Fila *fila){
    for(int i = 0;i<fila->fim;i++){
        if(i + 1 < fila->fim)
            printf("%d | ",fila->chave[i]);
        else
            printf("%d",fila->chave[i]);
    }
}
