//
// Created by pedro on 14/08/2021.
//

#include "filaProcessos.h"

void iniciaListprocess(processList *list){
    list->inicio = NULL;
    list->fim = list->inicio;
    list->tamanho = 0;
}
void insereProcess(processList *list, Process *processo){
    if(list->fim == NULL){
        list->fim = (processPointer) malloc(sizeof(Celulafila));
        list->inicio = list->fim;
    }
    else{
        list->fim->prox = (processPointer) malloc(sizeof(Celulafila));
        list->fim = list->fim->prox;
    }
    list->fim->processo = *processo;
    list->fim->prox = NULL;
    list->tamanho++;
}
void removeDoinicio(processList *list){
    processPointer aponta_inicio = list->inicio;
    processPointer aponta = list->inicio->prox;
    if(aponta == NULL){
        free(aponta_inicio);
        iniciaListprocess(list);
    }
    else{
        list->inicio = aponta;
        free(aponta_inicio);
        list->tamanho--;
    }
}
void removeProcess(processList *list,pid_t  PID){
    Celulafila *auxilia;
    processPointer Aponta = list->inicio;
    if(Aponta == NULL){
        return;
    }
    else{
        if(list->inicio->processo.PID == PID){
            removeDoinicio(list);
        }
        else{
            while (Aponta->prox != NULL && Aponta->processo.PID != PID){
                if((Aponta->prox->processo.PID == PID) && (Aponta->prox->processo.PID != list->fim->processo.PID)){
                    auxilia = Aponta->prox;
                    Aponta->prox = Aponta->prox->prox;
                    free(auxilia);
                    list->tamanho--;
                    break;
                }
                if (Aponta->prox->processo.PID == PID && list->fim->processo.PID == PID){
                    auxilia = list->fim;
                    list->fim = Aponta;
                    free(auxilia);
                    list->tamanho--;
                    list->fim->prox = NULL;
                    break;
                }
                Aponta = Aponta->prox;
            }
        }
    }
}
void imprimeProcessos(processList *list){
    //a determinar durante o trabalho como será o modelo de impressão
}