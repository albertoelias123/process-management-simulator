//
// Created by alber on 09/09/2021.
//

#include "manager.h"
void timeIncrement(manager *pManager){
    pManager->tabela->processos[*pManager->estadoExecucao]->timeCpuUsed++;
    pManager->cpu->timeUsed++;
    pManager->time++;
}
void comandU(manager *pManager){
    //faz o escalonamento (pode envolver troca de contexto)
    //executa a proxima instrução do processo simulado em execucao
    executa(pManager->cpu);
    //incrementa o PC , execeto para instruções F ou R
    if(pManager->tabela->processos[*pManager->estadoExecucao]->vetorPrograma[pManager->tabela->processos[*pManager->estadoExecucao]->PC].comando != 'F' &&
    pManager->tabela->processos[*pManager->estadoExecucao]->vetorPrograma[pManager->tabela->processos[*pManager->estadoExecucao]->PC].comando != 'R'){
        pManager->tabela->processos[*pManager->estadoExecucao]->PC++;
    }
    timeIncrement(pManager);
}
void comandL(manager *pManager){
    int indice = removeOfFila(pManager->estadoBloqueado);
    insereOnFila(pManager->estadoPronto,indice);
    alteraEstado(pManager->tabela,indice);
}

void setupManager(manager* pManager, int *pipeControlToManager, int* pipeManagerToControl){
    //inicialização do processo gerenciador de processos
    pManager->pidAutoIncrement = 0;
    pManager->estadoBloqueado = criaFila();
    pManager->estadoExecucao = (int*) malloc(sizeof(int));
    pManager->estadoPronto = criaFila();
    pManager->tabela = criaTabela();
    pManager->cpu = criaCPU();
    pManager->time = 0;

    //criar o primeiro processo simulado
    process *processo0 = criaProcesso("processo0",0,0);
    processo0->estado = execucao;
    //inserindo o primeiro processo na tabela de processos e na fila bloqueada
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,processo0));
    *pManager->estadoExecucao = insereOnTabela(pManager->tabela,processo0);
    //depois imprimir o q esta acontecendo

    //começar a fazer a operação L

    //melhorar operação I
    //fazer o comando U
    //melhorar operação I

    pManager->pipeControlToManager = pipeControlToManager;
    pManager->pipeManagerToControl = pipeManagerToControl;
    close(pManager->pipeControlToManager[1]); // Close the unwanted pipe2 write side
    pManager->PID = getpid();
    Debug("PID Manager = %d\n", pManager->PID);
}

void loopManager(manager *pManager){
    Debug("\tComeço Manager\n");
    char *command = (char*) malloc(sizeof (char));
    do{
        Debug("\tLoop Manager\n");
        close(pManager->pipeControlToManager[1]); // Quer Ler
        close(pManager->pipeManagerToControl[0]); // Quer Escrever

        read(pManager->pipeControlToManager[0], command, sizeof(char));
        Debug("\t[Manager] Comando: %c\n", *command);

        if(*command == 'I'){

            printf("\t[Manager] Comando: %c | IMPRIMIR\n", *command);

            pid_t pidImpress;
            if((pidImpress = fork()) < 0){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if(pidImpress > 0){
                //Manager

                printf("\t[Manage] Aguarda processo impress\n");
                //Aguarda a finalização do Processo Impressão
                wait(NULL);
                printf("\t[Manage] FIM\n");

            }
            else{

                //Impress
                printf("\t\t[Impress] Inicio\n");
                imprimeManager(pManager);
                printf("\t\t[Impress] SLEEP(5)\n");
                sleep(5);
                printf("\t\t[Impress] FIM\n");
                exit(EXIT_SUCCESS);

            }


            printf("\n");
            sleep(1);
            write(pManager->pipeManagerToControl[1], "S", sizeof(char));

        }

    } while (*command != 'M');
    free(command);
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