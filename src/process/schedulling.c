#include "schedulling.h"


void dispatcher(manager *pManager, int indexPtoCPU){//troca de contexo
    alteraEstadoParaExecucao(pManager->tabela, indexPtoCPU);
    if(pManager->processoEmExecucao != -1){ //se tiver algum processo em execucao
        //salva o processo em execução na tabela de processos
        *pManager->tabela->processos[pManager->processoEmExecucao] = pManager->cpu->processoExecucao;
    }
    pManager->processoEmExecucao = indexPtoCPU;
    pManager->cpu->processoExecucao = *pManager->tabela->processos[indexPtoCPU];//index processo q vai para a cpu
    int exp = pManager->cpu->processoExecucao.priority;
    pManager->cpu->timeSlice = pow(2,(exp));
    pManager->cpu->timeUsed = 0;
    if(pManager->cpu->processoExecucao.timeStart == -1){
        pManager->cpu->processoExecucao.timeStart = pManager->time;
    }
}

void schedulling(manager *pManager){    
    if(strcmp(pManager->schedullingPolitics, "P") == 0){
        prioritySchedulling(pManager);
    }else if(strcmp(pManager->schedullingPolitics, "F") == 0){
        fifoSchedulling(pManager);
    }else{
        fprintf(stderr, "Erro na escolha da politica!\n");
    }

}


void prioritySchedulling(manager *pManager){
    if(pManager->processoEmExecucao != -1)
        if(pManager->cpu->processoExecucao.estado == bloqueado){ // o processo está bloquedo
            insereOnFila(pManager->processosBloqueados, pManager->processoEmExecucao);
            if((pManager->cpu->timeUsed < pManager->cpu->timeSlice)) // o processo não usou sua fatia de tempo
                if(pManager->cpu->processoExecucao.priority > 0)
                    pManager->cpu->processoExecucao.priority--;
            *pManager->tabela->processos[pManager->processoEmExecucao] = pManager->cpu->processoExecucao;
            pManager->processoEmExecucao = -1;
        }

    if(!filaEVazia(pManager->processosProntos)){

        if(pManager->processoEmExecucao == -1 ) { // nenhum processo em execução
            int nextProcess = removeOfFila(pManager->processosProntos);
            dispatcher(pManager, nextProcess);
        }
        else{ // temos um processo em execução
            if (pManager->cpu->timeUsed >= pManager->cpu->timeSlice){ //processo chegou no limite de uso
                pManager->cpu->processoExecucao.estado = pronto;
                insereOnFila(pManager->processosProntos, pManager->processoEmExecucao);

                if (pManager->cpu->processoExecucao.priority < 3)//diminui a prioridade
                    pManager->cpu->processoExecucao.priority++;

                int nextProcess = removeOfFila(pManager->processosProntos);
                dispatcher(pManager, nextProcess); //troca de contexto
            }
        }

    }

}

//  Once resources(CPU Cycle) are allocated to a process, the process holds it till it completes its burst time or switches to a bloqued (bloqueado) state.

void fifoSchedulling(manager *pManager){
    if(pManager->processoEmExecucao != -1)
        if(pManager->cpu->processoExecucao.estado == bloqueado){ // o processo está bloquedo
            insereOnFila(pManager->processosBloqueados, pManager->processoEmExecucao);            
            *pManager->tabela->processos[pManager->processoEmExecucao] = pManager->cpu->processoExecucao;
            pManager->processoEmExecucao = -1;
        }

    if(!filaEVazia(pManager->processosProntos)){

        int nextProcess = removeOfFila(pManager->processosProntos);
        if(pManager->processoEmExecucao == -1 ) { // nenhum processo em execução
            dispatcher(pManager, nextProcess);
        }
        else{ // temos um processo em execução
            pManager->cpu->processoExecucao.estado = pronto;
            insereOnFila(pManager->processosProntos, pManager->processoEmExecucao);
            dispatcher(pManager, nextProcess); //troca de contexto
        }
    }
}

void processSort(manager *pManager){
    for (int i = 1; i <= pManager->processosProntos->fim; i++){
        int aux;
        if (pManager->tabela->processos[pManager->processosProntos->chave[i - 1]]->priority > pManager->tabela->processos[pManager->processosProntos->chave[i]]->priority){
            aux = pManager->processosProntos->chave[i - 1];
            pManager->processosProntos->chave[i] = pManager->processosProntos->chave[i - 1];
            pManager->processosProntos->chave[i - 1] = aux;
        }
    }
}

