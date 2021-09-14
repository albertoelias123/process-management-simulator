//
// Created by alber on 09/09/2021.
//

#include "manager.h"
#include "/home/pedro/CLionProjects/process-management-simulato/src/process/schedulling.h"

void comandU(manager *pManager){
    //executa a proxima instrução do processo simulado em execucao

    executa(pManager->tabela->processos[pManager->estadoPronto->chave[0]],pManager);


    pManager->time++;
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
    pManager->estadoExecucao = 0;
    pManager->estadoPronto = criaFila();
    pManager->tabela = criaTabela();
    pManager->cpu = criaCPU();
    pManager->time = 0;

    //criar o primeiro processo simulado
    process *processo0 = criaProcesso("processo0",pManager->pidAutoIncrement++,0);

    insereOnFila(pManager->estadoBloqueado, insereOnTabela(pManager->tabela,processo0));

    pManager->pipeControlToManager = pipeControlToManager;
    pManager->pipeManagerToControl = pipeManagerToControl;
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
        if(*command == 'U'){
            comandU(pManager);
        }
        if(*command == 'L'){
            comandL(pManager);
        }
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
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    imprimeTabela(pManager->tabela);
}