#include "schedulling.h"


void schedulling(manager *pManager, int indexPtoCPU){
    alteraEstado(pManager->tabela, pManager->estadoExecucao); //replace type of state to rdy       
    *pManager->tabela->processos[pManager->estadoExecucao] = pManager->cpu->processoExecucao;
    pManager->cpu->processoExecucao = *pManager->tabela->processos[indexPtoCPU];
    printf("Troca de contexto\n");//teste
}


void prioritySchedulling(manager *pManager, char *command, int nextProcess){
    int exp;
    exp = pManager->cpu->processoExecucao.priority;   
    if (pManager->cpu->processoExecucao.timeCpuUsed == (pow(2,(exp)))){
        pManager->cpu->processoExecucao.estado = pronto;
        insereOnFila(pManager->estadoBloqueado, pManager->cpu->processoExecucao.pid);
        schedulling(pManager,nextProcess); //troca de contexto
        
        if (pManager->cpu->processoExecucao.priority < 3){
            pManager->cpu->processoExecucao.priority++;
        }else{
            fprintf(stderr, "Lower priority achieved \n");
        }
    }
    //incremento na prioridade 
    if((pManager->cpu->processoExecucao.timeCpuUsed < (pow(2,(exp))) && (command == "B"))){
        if(pManager->cpu->processoExecucao.priority > 0){
            pManager->cpu->processoExecucao.priority--;
            schedulling(pManager,nextProcess); //troca de contexto
        }else{
            fprintf(stderr, "Higher priority achieved \n");
        }
    }
}

//  Once resources(CPU Cycle) are allocated to a process, the process holds it till it completes its burst time or switches to a bloqued (bloqueado) state.

void nonPreemptiveSchedulling(manager *pManager, char *command, int nextProcess){ 
    
    if(command == "B"){       
        schedulling(pManager,nextProcess); //troca de contexto
        processSort(pManager);
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

