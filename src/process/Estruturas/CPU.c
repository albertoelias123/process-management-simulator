//
// Created by pedro on 09/09/2021.
//

#include "CPU.h"

CPU *criaCPU(){
    CPU *cpu = (CPU*) malloc(sizeof(CPU));
    for(int i = 0;i<TAM_REGISTRADOR;i++){
        cpu->reg[i].state = naoUsando;
    }
    return cpu;
}

void executa(CPU *cpu){//chama o sub o sum, carrega e salva

}

void carrega(int *refMem,int position,registrador *reg){

}
void salva(int *refMem,int position,registrador *reg){

}

void sum(registrador *reg,int valor,int posicao){
    if(posicao < TAM_REGISTRADOR) {
        //tratar a questão do registrador
    }
    else{
        printf("--------------------------");
        printf("\nPosicao inexistente\n");
        printf("--------------------------");
    }
}
void sub(registrador *reg,int valor,int posicao){
    if(posicao < TAM_REGISTRADOR) {
        //tratar a questao do registrador
    }
    else{
        printf("--------------------------");
        printf("\nPosicao inexistente\n");
        printf("--------------------------");
    }
}

void printCPU(CPU *cpu){
    // pid processo  time slice   time used   registradores
    printf("\n|||||||||||||||||||||||||||||||||| CPU |||||||||||||||||||||||||||||||||||||||\n");
    printf("Pid = %d | Time Slice %d | Time Used %d | ",cpu->processoExecucao.pid,cpu->timeSlice,cpu->timeUsed);
    for(int i = 0;i<TAM_REGISTRADOR;i++){
        printf("Reg %d->", i+1);
        printReg(&cpu->reg[i]);
        if(i+1 < TAM_REGISTRADOR)
            printf(" | ");
    }
}

void printReg(registrador *reg){
    //Estado (X) não usando
    //Estado usando   valor  refmem
    if(reg->state == naoUsando)
        printf("X");
    else
        printf("[%d]=%d",reg->refMem,reg->valor);
}