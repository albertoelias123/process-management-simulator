//
// Created by alber on 09/09/2021.
//

#include "manager.h"
#include "schedulling.h"

void executa(manager *pManager){    
    schedulling(pManager);// realiza escalonamento com base na politica escolhida
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
            schedulling(pManager);// realiza escalonamento

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
            free(pManager->tabela->processos[pManager->processoEmExecucao]);
            pManager->tabela->processos[pManager->processoEmExecucao] = NULL;
            pManager->tabela->qtd--;
            pManager->processoEmExecucao = -1;
        }
    }
    pManager->cpu->timeUsed++;
    pManager->time++;
}

void commandF(manager *pManager){
    process newProcessSimulated;
    newProcessSimulated.qtdInstructions = pManager->cpu->processoExecucao.qtdInstructions;
    newProcessSimulated.memory = pManager->cpu->processoExecucao.memory;
    newProcessSimulated.estado = pronto;
    newProcessSimulated.priority = pManager->cpu->processoExecucao.priority;
    newProcessSimulated.timeStart = pManager->cpu->processoExecucao.timeStart;
    newProcessSimulated.timeCpuUsed = 0;
    newProcessSimulated.ppid = pManager->cpu->processoExecucao.pid;
    newProcessSimulated.pid = pManager->cpu->processoExecucao.pid +1;
    newProcessSimulated.PC = pManager->cpu->processoExecucao.PC + 1;
            
    insereOnFila(pManager->processosProntos, insereOnTabela(pManager->tabela, &newProcessSimulated));
    pManager->cpu->processoExecucao.PC += pManager->cpu->processoExecucao.vetorPrograma[pManager->cpu->processoExecucao.PC].F.valor + 1;  
    printf("Projeto filho criado \n");          

}

void comandL(manager *pManager){
    int indice = removeOfFila(pManager->processosBloqueados);
    insereOnFila(pManager->processosProntos, indice);
    alteraEstadoParaPronto(pManager->tabela, indice);
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
        if(*command == 'L'){
            comandL(pManager);
        }
        if(*command == 'I'){

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
            printf("Time Used = %d",pManager->cpu->timeUsed);
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

    }
    else if(opcao == 5){
        int indice;
        printf("\nEntre com um indice da tabela: ");
        scanf("%d",&indice);
        printf("\n ||||||||||||||||||||| Processo %d da tabela de processos ||||||||||||||||||||| \n",indice);
        printf("| Pid | Ppid | State | Time CPU | instructs | PC | Time start | Mem used | Prio |\n");
        imprimeProcesso(pManager->tabela->processos[indice]);
        imprimeInstrucoesProcesso(pManager->tabela->processos[indice]);
        imprimeMem(&pManager->tabela->processos[indice]->memory);
    }
}