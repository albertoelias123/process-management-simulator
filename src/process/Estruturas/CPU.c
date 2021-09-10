//
// Created by pedro on 09/09/2021.
//

#include "CPU.h"
void executa(CPU *cpu){//chama o sub o sum, carrega e salva

}

void carrega(int *refMem,int position,registrador *reg){

}
void salva(int *refMem,int position,registrador *reg){

}

void sum(memProcess *mem,int valor,int posicao){
    if(posicao < TAM_VETOR_MEMORIA) {
        mem->memory[posicao] += valor;
    }
    else{
        printf("--------------------------");
        printf("\nPosicao inexistente\n");
        printf("--------------------------");
    }
}
void sub(memProcess *mem,int valor,int posicao){
    if(posicao < TAM_VETOR_MEMORIA) {
        mem->memory[posicao] -= valor;
    }
    else{
        printf("--------------------------");
        printf("\nPosicao inexistente\n");
        printf("--------------------------");
    }
}
