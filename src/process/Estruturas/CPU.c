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
    carrega(&cpu->processoExecucao.memory,cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].operation.valores.refMem,cpu->reg);
    for(int i = 0;i < TAM_REGISTRADOR;i++){
        if(cpu->reg[i].state == usando) {
            if(cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].comando == 'V'){
                cpu->reg[i].valor = cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].operation.valores.valor;
            }
            else if(cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].comando == 'A'){
                sum(cpu->reg,cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].operation.valores.valor,i);
            }
            else if(cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].comando == 'S'){
                sub(cpu->reg,cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].operation.valores.valor,i);
            }
            printf("%d %d\n", cpu->reg[i].refMem, cpu->reg[i].valor);
            break;
        }
    }
}

void carrega(memProcess *refMem,int position,registrador *reg){
    for(int i = 0;i<TAM_REGISTRADOR;i++){
        if(reg[i].state == naoUsando){
            reg[i].state = usando;
            reg[i].refMem = position;
            reg[i].valor = refMem->memory[position]->valor;
            break;
        }
        if(i == TAM_REGISTRADOR - 1){
            printf("\n--------------------------------\n");
            printf("Nao ha registradores disponiveis");
            printf("\n--------------------------------\n");
        }
    }

}
void salva(int *refMem,int position,registrador *reg){

}

void sum(registrador *reg,int valor,int posicao){
    if(posicao < TAM_REGISTRADOR) {
        reg[posicao].valor += valor;
    }
    else{
        printf("--------------------------");
        printf("\nPosicao inexistente\n");
        printf("--------------------------");
    }
}
void sub(registrador *reg,int valor,int posicao){
    if(posicao < TAM_REGISTRADOR) {
        reg[posicao].valor -= valor;
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