//
// Created by pedro on 09/09/2021.
//

#include "simulatedProcess.h"

memProcess *createMemory(){
    memProcess *mem = (memProcess*) malloc(sizeof(memProcess));
    mem->memUsed = 0;
    return mem;
}
int memFull(memProcess *mem){
    if(mem->memUsed == TAM_VETOR_MEMORIA - 1){
        return TRUE;
    }
    return FALSE;
}
int memEmpty(memProcess *mem){
    if(mem->memUsed == 0){
        return TRUE;
    }
    return FALSE;
}

void insereOnMemory(memProcess *mem,int valor,int posicao){
    if(!memFull(mem) && posicao < TAM_VETOR_MEMORIA){
        mem->memory[posicao] = valor;
    }
    else{
        printf("--------------------------");
        printf("\nMemoria cheia\n");
        printf("--------------------------");
    }
}