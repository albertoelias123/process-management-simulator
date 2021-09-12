//
// Created by alber on 09/09/2021.
//

#include "manager.h"
void comandL(manager *pManager){

}

void setupManager(manager* pManager, int* pipe){
    //inicialização do processo gerenciador de processos
    pManager->pidAutoIncrement = 0;
    pManager->estadoBloqueado = criaFila();
    pManager->estadoExecucao = criaFila();
    pManager->estadoPronto = criaFila();
    pManager->tabela = criaTabela();
    pManager->cpu = criaCPU();
    pManager->time = 0;

    //criar o priemeiro processo simulado
    process *process1 = (process*) malloc(sizeof(process));
    processReader(process1,"instrucoes.txt",1,1);

    //inserindo o primeiro processo na tabela de processos e na fila bloqueada
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,process1));

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

}