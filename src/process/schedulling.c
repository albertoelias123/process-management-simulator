#include "schedulling.h"


CPU *criaCPU(){
    CPU *cpu = (CPU*) malloc(sizeof(CPU));
    return cpu;
}

void executa(process *processo,manager *pManager){// falta as operacoes de D , N , F  R
    if(processo->estado == pronto){
        pManager->cpu->processoExecucao = *processo;
        pManager->cpu->processoExecucao.estado = execucao;
        pManager->estadoExecucao = removeOfFila(pManager->estadoPronto);
        pManager->cpu->processoExecucao.PC++;
    }
    char *command = (char*) malloc(sizeof(char));
    *command = pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].comando;

    if(*command == 'N'){
        pManager->cpu->processoExecucao.PC++;
    }
    if(*command == 'V'){
        for(int i = 0;i<pManager->cpu->processoExecucao.memory.qtd;i++){
            if(pManager->cpu->processoExecucao.memory.position[i]->posicao ==
              pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].operation.valores.refMem){
                pManager->cpu->processoExecucao.memory.position[i]->valor =
                        pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].operation.valores.valor;
            }
        }
        pManager->cpu->processoExecucao.PC++;
    }
    else if(*command == 'A'){
        sum(&pManager->cpu->processoExecucao);
        pManager->cpu->processoExecucao.PC++;
    }
    else if(*command == 'S'){
        sub(&pManager->cpu->processoExecucao);
        pManager->cpu->processoExecucao.PC++;
    }
    else if(*command == 'D'){
        insereOnMemory(&pManager->cpu->processoExecucao.memory, 0, pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].D.refMem);
        pManager->cpu->processoExecucao.PC++;
    }
    else if(*command == 'R'){
        pManager->cpu->processoExecucao = *criaProcesso(pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].R.file,pManager->cpu->processoExecucao.pid,pManager->cpu->processoExecucao.ppid);
    }
    else if(*command == 'B'){ // implementação da politica de escalonamento
        processSort(pManager);
        prioritySchedulling(pManager,command,pManager->estadoPronto->chave[0]);
//        ****************************************************************************
//        nonPreemptiveSchedulling(pManager,command,pManager->estadoPronto->chave[0]);
//        caso seja utilizada a politica do grupo
//        *********************************************************************************
        pManager->cpu->processoExecucao.PC++;
    }
    else if(*command == 'F'){
        process newProcessSimulated;
        newProcessSimulated = pManager->cpu->processoExecucao;
        newProcessSimulated.PC++;
        insereOnFila(pManager->estadoPronto, insereOnTabela(pManager->tabela,&newProcessSimulated));
        pManager->cpu->processoExecucao.PC += pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].F.valor + 1;
    }
    else if(*command == 'T'){
        free(pManager->tabela->processos[pManager->estadoExecucao]);//testar
        pManager->estadoExecucao = removeOfFila(pManager->estadoPronto);
        pManager->cpu->processoExecucao = *pManager->tabela->processos[pManager->estadoExecucao];
        processSort(pManager);
        dispatcher(pManager,pManager->estadoExecucao);
        pManager->tabela->processos[pManager->estadoExecucao]->estado = execucao;
    }
    pManager->cpu->timeSlice++;
    pManager->cpu->timeUsed++;
    *processo = pManager->cpu->processoExecucao ;
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







void dispatcher(manager *pManager, int indexPtoCPU){
    alteraEstado(pManager->tabela, pManager->estadoExecucao); //replace type of state to rdy
    *pManager->tabela->processos[pManager->estadoExecucao] = pManager->cpu->processoExecucao;
    pManager->cpu->processoExecucao = *pManager->tabela->processos[indexPtoCPU];//index processo q vai para a cpu
    printf("Troca de contexto\n");//teste
}


void prioritySchedulling(manager *pManager, char *command, int nextProcess){
    int exp;
    exp = pManager->cpu->processoExecucao.priority;   
    if (pManager->cpu->processoExecucao.timeCpuUsed == (pow(2,(exp)))){
        pManager->cpu->processoExecucao.estado = pronto;
        insereOnFila(pManager->estadoBloqueado, pManager->cpu->processoExecucao.pid);
        dispatcher(pManager, nextProcess); //troca de contexto
        
        if (pManager->cpu->processoExecucao.priority < 3){
            pManager->cpu->processoExecucao.priority++;
        }else{
            fprintf(stderr, "Lower priority achieved \n");
        }
    }
    //incremento na prioridade 
    if((pManager->cpu->processoExecucao.timeCpuUsed < (pow(2,(exp))) && (*command == 'B'))){
        if(pManager->cpu->processoExecucao.priority > 0){
            pManager->cpu->processoExecucao.priority--;
            dispatcher(pManager, nextProcess); //troca de contexto
        }else{
            fprintf(stderr, "Higher priority achieved \n");
        }
    }
}

//  Once resources(CPU Cycle) are allocated to a process, the process holds it till it completes its burst time or switches to a bloqued (bloqueado) state.

void nonPreemptiveSchedulling(manager *pManager, char *command, int nextProcess){ 
    
    if(*command == 'B'){
        dispatcher(pManager, nextProcess); //troca de contexto
//        processSort(pManager); não vai precisar pq ja vai receber a fila ordenada
    }else{
            fprintf(stderr, "Still running... \n");
    }    
}

void processSort(manager *pManager){
    for (int i = 1; i <= pManager->estadoPronto->fim; i++){
        int aux;
        if (pManager->tabela->processos[pManager->estadoPronto->chave[i-1]]->priority > pManager->tabela->processos[pManager->estadoPronto->chave[i]]->priority){
            aux = pManager->estadoPronto->chave[i-1];
            pManager->estadoPronto->chave[i] = pManager->estadoPronto->chave[i-1];
            pManager->estadoPronto->chave[i-1] = aux;            
        }
    }
}

