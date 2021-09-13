//
// Created by pedro on 09/09/2021.
//

#include "CPU.h"

CPU *criaCPU(){
    CPU *cpu = (CPU*) malloc(sizeof(CPU));
    return cpu;
}

void executa(CPU *cpu){// falta as operacoes de D , N , F  R

    if(cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].comando == 'V'){
        for(int i = 0;i<cpu->processoExecucao.memory.qtd;i++){
            if(cpu->processoExecucao.memory.position[i]->posicao ==
            cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].operation.valores.refMem){
                cpu->processoExecucao.memory.position[i]->valor =
                        cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].operation.valores.valor;
            }
        }
    }
    else if(cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].comando == 'A'){
        sum(&cpu->processoExecucao);
    }
    else if(cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].comando == 'S'){
        sub(&cpu->processoExecucao);
    }
    else if(cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].comando == 'D'){
        insereOnMemory(&cpu->processoExecucao.memory, 0, cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].D.refMem);
    }
    else if(cpu->processoExecucao.vetorPrograma[cpu->processoExecucao.PC].comando == 'R'){
        //fazer operação R
    }
<<<<<<<<< Temporary merge branch 1
    *processoPronto = cpu->processoExecucao;//salvamento

    cpu->timeSlice++;
    cpu->timeUsed++;
||||||||| merged common ancestors
    *processoPronto = cpu->processoExecucao;//salvamento
=========

    cpu->timeSlice++;
    cpu->timeUsed++;
>>>>>>>>> Temporary merge branch 2
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