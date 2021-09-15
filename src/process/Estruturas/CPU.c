//
// Created by pedro on 09/09/2021.
//

#include "CPU.h"


CPU *criaCPU(){
    CPU *cpu = (CPU*) malloc(sizeof(CPU));
    return cpu;
}

void sum(process *processOnCpu){
    for(int i = 0;i<processOnCpu->memory.qtd;i++) {
        if (processOnCpu->memory.position[i]->posicao ==
            processOnCpu->vetorPrograma[processOnCpu->PC].operation.valores.refMem) {
            processOnCpu->memory.position[i]->valor +=
                    processOnCpu->vetorPrograma[processOnCpu->PC].operation.valores.valor;
        }
    }
}

void sub(process *processOnCpu){
    for(int i = 0;i<processOnCpu->memory.qtd;i++) {
        if (processOnCpu->memory.position[i]->posicao ==
            processOnCpu->vetorPrograma[processOnCpu->PC].operation.valores.refMem) {
            processOnCpu->memory.position[i]->valor -=
                    processOnCpu->vetorPrograma[processOnCpu->PC].operation.valores.valor;
        }
    }
}

void printCPU(CPU *cpu){
    // pid processo  time slice   time used   registradores
    printf("\n|||||||||||||||||||||||||||||||||| CPU |||||||||||||||||||||||||||||||||||||||\n");
    printf("Pid = %d | Time Slice %d | Time Used %d | ",cpu->processoExecucao.pid,cpu->timeSlice,cpu->timeUsed);
}
