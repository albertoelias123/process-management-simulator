//
// Created by pedro on 14/08/2021.
//

#include "Processo.h"

void processCreate(Process *processo,pid_t pid){
    startMemoryProcess(&processo->memProcess);
    processo->PID = pid;
}

void manipulateProcess(Process *processo,int posicao,int prioridade,int valor,char metodo[30]){
    if (strcmp("iniciar posicao",metodo) == 0){
        insereOnMemory(&processo->memProcess,posicao);
    }
    else if (strcmp("inserir valor",metodo) == 0){
        valorOnMemory(&processo->memProcess,posicao,valor);
    }
    else if(strcmp("somar ao valor",metodo) == 0){
        sum(&processo->memProcess,posicao,valor);
    }
    else if(strcmp("prioridade",metodo) == 0){
        processo->priority = prioridade;
    }
    else{
        sub(&processo->memProcess,posicao,valor);
    }
}