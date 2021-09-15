//
// Created by alber on 09/09/2021.
//

#include "manager.h"
#include "schedulling.h"

void executa(manager *pManager){
    //prioritySchedulling(pManager);
    nonPreemptiveSchedulling(pManager);// realiza escalonamento
    if(pManager->processoEmExecucao != -1) {

        char *command = (char *) malloc(sizeof(char));
        *command = pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].comando;

        if (*command == 'N') {
            pManager->cpu->processoExecucao.PC++;
            pManager->cpu->processoExecucao.timeCpuUsed++;
        }
        if (*command == 'V') {
            for (int i = 0; i < pManager->cpu->processoExecucao.memory.qtd; i++) {
                if (pManager->cpu->processoExecucao.memory.position[i]->posicao ==
                    pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].operation.valores.refMem) {
                    pManager->cpu->processoExecucao.memory.position[i]->valor =
                            pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].operation.valores.valor;
                }
            }
            pManager->cpu->processoExecucao.PC++;
            pManager->cpu->processoExecucao.timeCpuUsed++;
        } else if (*command == 'A') {
            sum(&pManager->cpu->processoExecucao);
            pManager->cpu->processoExecucao.PC++;
            pManager->cpu->processoExecucao.timeCpuUsed++;
        } else if (*command == 'S') {
            sub(&pManager->cpu->processoExecucao);
            pManager->cpu->processoExecucao.PC++;
            pManager->cpu->processoExecucao.timeCpuUsed++;
        } else if (*command == 'D') {
            insereOnMemory(&pManager->cpu->processoExecucao.memory, 0,
                           pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].D.refMem);
            pManager->cpu->processoExecucao.PC++;
            pManager->cpu->processoExecucao.timeCpuUsed++;
        } else if (*command == 'R') {
            processReader(&pManager->cpu->processoExecucao,pManager->cpu->processoExecucao.vetorPrograma[
                    pManager->cpu->processoExecucao.PC].R.file);
            pManager->cpu->processoExecucao.timeCpuUsed++;
        } else if (*command == 'B') { // implementação da politica de escalonamento
            //movendo o processo atualmente em execução para bloqueado
            pManager->cpu->processoExecucao.timeCpuUsed++;
            pManager->cpu->processoExecucao.estado = bloqueado;
            pManager->cpu->processoExecucao.PC++;
            nonPreemptiveSchedulling(pManager);// realiza escalonamento
        } else if (*command == 'F') {

            process *newProcessSimulated = (process*) malloc(sizeof (process));
            *newProcessSimulated = pManager->cpu->processoExecucao;
            newProcessSimulated->estado = pronto;
            newProcessSimulated->timeStart = -1;
            newProcessSimulated->ppid = pManager->cpu->processoExecucao.pid;
            newProcessSimulated->pid = pManager->pidAutoIncrement++;
            newProcessSimulated->timeCpuUsed = 0;
            newProcessSimulated->PC++;

            insereOnFila(pManager->processosProntos, insereOnTabela(pManager->tabela, newProcessSimulated));
            pManager->cpu->processoExecucao.PC +=
                    pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].F.valor + 1;
            pManager->cpu->processoExecucao.timeCpuUsed++;

        } else if (*command == 'T') {
            // SALVAR TEMPO DE EXECUCAO PARA CALCULAR TEMPO MEDIO
            // FAZER CODIGO AQUI

            pManager->timeProcessAbsolut += pManager->cpu->timeUsed;
            pManager->qtdProcessosExecuted++;// usado para calcular o tempo medio
            free(pManager->tabela->processos[pManager->processoEmExecucao]);
            pManager->tabela->processos[pManager->processoEmExecucao] = NULL;
            pManager->tabela->qtd--;
            pManager->processoEmExecucao = -1;
        }
    }
    pManager->cpu->timeUsed++;
    pManager->time++;
}



void comandL(manager *pManager){
    int indice = removeOfFila(pManager->processosBloqueados);
    insereOnFila(pManager->processosProntos, indice);
    alteraEstadoParaPronto(pManager->tabela, indice);
}

void averageTime(manager *pManager){
    printf("\n*******************************\n");
    if(pManager->qtdProcessosExecuted > 0) {
        printf("O tempo medio do ciclio = %d", pManager->timeProcessAbsolut / pManager->qtdProcessosExecuted);
    }
    else{
        printf("O tempo medio do ciclio = %d", 0);
    }
}

void setupManager(manager* pManager, int *pipeControlToManager, int* pipeManagerToControl){
    //inicialização do processo gerenciador de processos
    pManager->pidAutoIncrement = 0;
    pManager->processosBloqueados = criaFila();
    pManager->processoEmExecucao = -1;
    pManager->processosProntos = criaFila();
    pManager->tabela = criaTabela();
    pManager->cpu = criaCPU();
    pManager->time = 0;
    pManager->timeProcessAbsolut = 0;
    pManager->qtdProcessosExecuted = 0;

    //criar o primeiro processo simulado
    process *processo0 = criaProcesso("processo0",pManager->pidAutoIncrement++,-1);

    insereOnFila(pManager->processosBloqueados, insereOnTabela(pManager->tabela, processo0));

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
            executa(pManager);
        }
        else if(*command == 'L'){
            comandL(pManager);
        }
        else if(*command == 'I'){

            Debug("\t[Manager] Comando: %c | IMPRIMIR\n", *command);

            pid_t pidImpress;
            if((pidImpress = fork()) < 0){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if(pidImpress > 0){
                //Manager

                Debug("\t[Manage] Aguarda processo impress\n");
                //Aguarda a finalização do Processo Impressão
                wait(NULL);
                Debug("\t[Manage] FIM\n");

            }
            else{

                //Impress
                Debug("\t\t[Impress] Inicio\n");
                imprimeManager(pManager);
                Debug("\t\t[Impress] SLEEP(5)\n");
                Debug("\t\t[Impress] FIM\n");
                exit(EXIT_SUCCESS);

            }


            write(pManager->pipeManagerToControl[1], "S", sizeof(char));

        }

    } while (*command != 'M');

    if(*command == 'M'){

    }

    free(command);
    Debug("\tFIM Manager\n");
    exit(EXIT_SUCCESS);
}

void imprimeManager(manager *pManager){
    int opcao;
    printf("\n|||||||||||||||||||||||||||||||||||| Deseja imprimir quais informacoes do sistema ||||||||||||||||||||||||||||||||||||\n");
    printf("1- Imprimrir processo em execucao\n");
    printf("2- Imprimrir tabela de processos\n");
    printf("3- Imprimir tudo\n");
    printf("4- Imprimir resumo do sistema\n");
    printf("5- Imprimir processo da tabela de processos\n");
    printf("opcao: ");
    scanf("%d",&opcao);
    printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    if(opcao == 1 ){
        if(pManager->processoEmExecucao == -1) {
            printf("\n***************************************\n");
            printf("Nao ha processos atualmente em execucao");
            printf("\n***************************************\n");
        }
        else{
            printf("| Pid | Ppid | State | Time CPU | instructs | PC | Time start | Mem used | Prio |\n");
            imprimeProcesso(&pManager->cpu->processoExecucao);
            imprimeInstrucoesProcesso(&pManager->cpu->processoExecucao);
            imprimeMem(&pManager->tabela->processos[pManager->processoEmExecucao]->memory);
        }
    }
    else if(opcao == 2){
        imprimeTabela(pManager->tabela);
    }
    else if(opcao == 3) {
        printf("\n[Sistema]\n");
        printf("Total time used: %d | pidAutoincrement %d\n", pManager->time,pManager->pidAutoIncrement);
        if(pManager->processoEmExecucao == -1) {
            printf("\n|||||||||||||||||||||||||||||||||| CPU |||||||||||||||||||||||||||||||||||||||\n");
            printf("Time Lapse = %d",pManager->cpu->timeUsed);
            printf("\n***************************************\n");
            printf("Nao ha processos atualmente em execucao");
            printf("\n***************************************\n");
        }
        else{
            printCPU(pManager->cpu);
            printf("\n ||||||||||||||||||||| Processo em execucao ||||||||||||||||||||| \n");
            printf("| Pid | Ppid | State | Time CPU | instructs | PC | Time start | Mem used | Prio |\n");
            imprimeProcesso(&pManager->cpu->processoExecucao);
            imprimeInstrucoesProcesso(&pManager->cpu->processoExecucao);
            imprimeMem(&pManager->cpu->processoExecucao.memory);
        }
        imprimeTabela(pManager->tabela);
        printf("\n\n||||||||||||||||||||| indices processos bloqueados ||||||||||||||||||||| \n");
        printf("\t");
        imprimeFila(pManager->processosBloqueados);
        printf("\n||||||||||||||||||||| indices processos prontos ||||||||||||||||||||| \n");
        printf("\t");
        imprimeFila(pManager->processosProntos);

    }
    else if(opcao == 4){
        printf("\n************************************ Resumo do sistema *************************************\n");
        printf("Total time used = %d | Total de processos prontos = %d | Total de processos bloqueados = %d\n",
               pManager->time,pManager->processosProntos->fim,pManager->processosBloqueados->fim);
        if(pManager->processoEmExecucao == -1) {
            printf("\n***************************************\n");
            printf("Nao ha processos atualmente em execucao");
            printf("\n***************************************\n");
        }
        else {
            printf("\n ||||||||||||||||||||| Processo em execucao ||||||||||||||||||||| \n");
            printf("| Pid | Ppid | State | Time CPU | instructs | PC | Time start | Mem used | Prio |\n");
            imprimeProcesso(&pManager->cpu->processoExecucao);
            imprimeInstrucoesProcesso(&pManager->cpu->processoExecucao);
            imprimeMem(&pManager->cpu->processoExecucao.memory);
        }
    }
    else if(opcao == 5){
        int indice;
        printf("\nEntre com um indice da tabela: ");
        scanf("%d",&indice);
        printf("\n ||||||||||||||||||||| Processo %d da tabela de processos ||||||||||||||||||||| \n",indice);
        printf("| Pid | Ppid | State | Time CPU | instructs | PC | Time start | Mem used | Prio |\n");
        imprimeProcesso(pManager->tabela->processos[indice]);
        imprimeInstrucoesProcesso(&pManager->cpu->processoExecucao);
        imprimeMem(&pManager->tabela->processos[indice]->memory);
    }
}