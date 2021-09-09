//
// Created by pedro on 09/09/2021.
//

#include "filaEstatica.h"

Fila *criaFila(){
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
    return f;
}
int filaEVazia(Fila *fila){
    if(fila->qtd == 0){
        return TRUE;
    }
    return FALSE;
}
int filaECheia(Fila *fila){
    if(fila->qtd == MAXTAM-1){
        return TRUE;
    }
    return FALSE;
}
void insereOnFila(Fila *fila,TipoChave chave){
    if(filaEVazia(fila)){
        fila->chave[fila->fim++] = chave;
        fila->qtd++;
    }
    else{
        if(!filaECheia(fila)) {
            fila->chave[fila->fim++] = chave;
            fila->qtd++;
        }
        else{
            printf("\nFila cheia\n");
        }
    }
}
void removeOfFila(Fila *fila){
    if(!filaEVazia(fila)){
        fila->qtd--;
        fila->inicio++;
    }
    else{
        printf("\nFila vazia\n");
    }
}
void imprimeFila(Fila *fila){
    for(int i = fila->inicio;i<fila->fim;i++){
        printf("%d\n",fila->chave[i].valor);
    }
}
