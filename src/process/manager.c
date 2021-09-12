//
// Created by alber on 09/09/2021.
//

#include "manager.h"
void comandU(manager *pManager){
    //executa a proxima instrução do processo simulado em execucao
    executa(pManager->cpu);
    //incrementa o PC , execeto para instruções F ou R
    if(pManager->tabela->processos[*pManager->estadoExecucao]->vetorPrograma[pManager->tabela->processos[*pManager->estadoExecucao]->PC].comando != 'F' &&
    pManager->tabela->processos[*pManager->estadoExecucao]->vetorPrograma[pManager->tabela->processos[*pManager->estadoExecucao]->PC].comando != 'R'){
        pManager->tabela->processos[*pManager->estadoExecucao]->PC++;
    }
    pManager->time++;
    //faz o escalonamento (pode envolver troca de contexto)
}
void comandL(manager *pManager){
    int indice = removeOfFila(pManager->estadoBloqueado);
    insereOnFila(pManager->estadoPronto,indice);
    alteraEstado(pManager->tabela,indice);
}

process *criaProcesso(manager *pManager,char *fileName,int pid,int ppid){
    process *process1 = (process*) malloc(sizeof(process));
    char *newStr = (char*) malloc((strlen(fileName)+10)*sizeof(char));
    strcpy(newStr,fileName);
    strcat(newStr,".txt");
    processReader(process1,newStr,pid,ppid);
    return process1;
}
void setupManager(manager* pManager, int* pipe){
    //inicialização do processo gerenciador de processos
    pManager->pidAutoIncrement = 0;
    pManager->estadoBloqueado = criaFila();
    pManager->estadoExecucao = (int*) malloc(sizeof(int));
    pManager->estadoPronto = criaFila();
    pManager->tabela = criaTabela();
    pManager->cpu = criaCPU();
    pManager->time = 0;

    //criar o primeiro processo simulado
    process *processo0 = criaProcesso(pManager,"processo0",0,0);
    processo0->estado = execucao;
    //inserindo o primeiro processo na tabela de processos e na fila bloqueada
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,processo0));
    *pManager->estadoExecucao = insereOnTabela(pManager->tabela,processo0);
    //depois imprimir o q esta acontecendo
//    imprimeTesteProcesso(&process1);

    //começar a fazer a operação L

    //melhorar operação I
    //fazer o comando U
    //melhorar operação I

    pManager->pipe = pipe;
    pManager->PID = getpid();
    Debug("PID Manager = %d\n", pManager->PID);
}

void loopManager(manager *pManager){
    Debug("\tComeço Manager\n");
    char *comando = (char*) malloc(sizeof (char));
    do{
        Debug("\tLoop Manager\n");
        close(pManager->pipe[1]);
        read(pManager->pipe[0], comando, sizeof(char));
        Debug("\tComando no processo filho:%c\n", *comando);
        printf("\tComando:%c\n", *comando);
    } while (*comando != 'M');
    free(comando);
    Debug("\tFIM Manager\n");
    exit(EXIT_SUCCESS);
}
void imprimeManager(manager *pManager){
    printf("\n[Sistema]\n");
    printf("Total time used: %d\n",pManager->time);
    printCPU(pManager->cpu);
    printf("\n\n||||||||||||||||||||| indices processos bloqueados ||||||||||||||||||||| \n");
    printf("\t");
    imprimeFila(pManager->estadoBloqueado);
    printf("\n||||||||||||||||||||| indices processos prontos ||||||||||||||||||||| \n");
    printf("\t");
    imprimeFila(pManager->estadoPronto);
    printf("\n||||||||||||||||||||| Indice processo em execucao ");
    printf("[%d] |||||||||||||||||||||\n\n",*pManager->estadoExecucao);
    imprimeTabela(pManager->tabela);
}