#include "schedulling.h"
#include <math.h>

void schedulling(manager *pManager, int indexPtoCPU){
    alteraEstado(pManager->tabela, *pManager->estadoExecucao); //replace type of state to rdy       
    *pManager->tabela->processos[*pManager->estadoExecucao] = pManager->cpu->processoExecucao;
    pManager->cpu->processoExecucao = *pManager->tabela->processos[indexPtoCPU];
    printf("Troca de contexto\n");//teste
}


void prioritySchedulling(manager *pManager, char *command, int nextProcess){
    int exp;
    exp = pManager->cpu->processoExecucao.priority;   
    if (pManager->cpu->processoExecucao.timeCpuUsed == (pow(2,(exp)))){
        pManager->cpu->processoExecucao.estado = bloqueado;
        insereOnFila(pManager->estadoBloqueado, pManager->cpu->processoExecucao.pid);
        schedulling(pManager,nextProcess); //troca de contexto
        
        if (pManager->cpu->processoExecucao.priority < 3){
            pManager->cpu->processoExecucao.priority++;
        }else{
            fprintf(stderr, "Lower priority achieved \n");
        }

    }

}