//
// Created by alber on 09/09/2021.
//

#include "control.h"

void sendCommandByPipeToProcessManager(const control *pcontrol) {
    close(pcontrol->pipeControlToManager[0]); // Quer Escrever
    close(pcontrol->pipeManagerToControl[1]); // Quer Ler

    write(pcontrol->pipeControlToManager[1], pcontrol->command, sizeof(char));
    Debug("[Control] COMANDO ENVIADO %c", *(pcontrol->command))

    if(*(pcontrol->command) == 'I'){

        Debug("[Control] Aguardando Imprimir no Manager...\n");
        char *command = (char*) malloc(sizeof (char));
        read(pcontrol->pipeManagerToControl[0], command, sizeof(char));
        if(*command == 'S') //Sucesso
            Debug("Print Executado com Sucesso");
        else
            printf("Imprimir c/ erro, comando recebido %c", *(pcontrol->command));
        free(command);

    }
}

int choiceMode(){
    printf("\n--------------------------------------------------------\n");
    printf("| Deseja inserir comandos interativamente ou por arquivo ?\n");
    printf("1 - Interativamente\n2 - Arquivo\n->");
    int resposta;
    scanf("%d",&resposta);
    printf("\n--------------------------------------------------------\n");

    if(resposta != 1 && resposta != 2){
        printf("Opção Incorreta");
        return choiceMode();
    }
    return resposta;
}

char* commandInteractive(){
    printf("--------------------------------------------------------\n");
    printf("|||||| Existem 4 tipos de comandos |||||||\n"
           "U: Fim de uma unidade de tempo\n"
           "L: Desbloqueia o primeiro processo simulado na fila bloqueada\n"
           "I: Imprime o estado atual do sistema\n"
           "M: Imprime o temo médio do ciclo e finaliza o sistema\n");
    printf("\n--------------------------------------------------------\n");
    printf("\nEntre com o comando: ");

    char *comando = (char*) malloc(sizeof(char));
    fflush(stdin);
    scanf(" %c",comando);

    if ((*comando == 'U') || (*comando == 'L') || (*comando == 'I') || (*comando == 'M')){
        return comando;
    }else{
        fprintf(stderr, "Comando incorreto!\n");
        commandInteractive();
        }


    
}

char* commandsFromFile(){
    FILE *file;
    char *nameArq = (char*) malloc(50*sizeof(char ));
    printf("\nDigite o nome do arquivo de entrada:");
    scanf("%s",nameArq);
    strcat(nameArq,".txt");
    file = fopen(nameArq,"r");
    if(file == NULL){
        printf("\n----Arquivo inexistente----\n");
        free(nameArq);
        commandsFromFile();
    }
    else{
        free(nameArq);
        char *comandos = (char*) malloc(100 * sizeof(char));
        char *comando = (char*) malloc(sizeof (char));
        int i = 0;
        while (!feof(file)){
            fscanf(file,"%s",comando);
            comandos[i] = *comando;
            i++;
        }
        free(comando);
        //printf("%s",comandos);
        return comandos;
    }
}

void setupControl(control* pcontrol, int *pipeControlToManager, int* pipeManagerToControl){
    pcontrol->pipeControlToManager = pipeControlToManager;
    pcontrol->pipeManagerToControl = pipeManagerToControl;
    //Salva o PID do Processo Control
    pcontrol->pid = getpid();
    printf("PID Control = %d\n", pcontrol->pid);
}

void loopControl(control* pcontrol){

    Debug("Começo Control\n");
    int resposta = choiceMode(); // 1 = Interativo | 2 = Arquivo

    if(resposta == 1){

        do{
            Debug("Loop Control\n");
            pcontrol->command = commandInteractive();
            Debug("Comando no processo Control:%s\n",pcontrol->command);
            sendCommandByPipeToProcessManager(pcontrol);

            if(*(pcontrol->command) == 'U' || *(pcontrol->command) == 'L')
                system("clear");

        }while( *(pcontrol->command) != 'M');

    } else {

        char* commands = commandsFromFile();
        pcontrol->command = commands;
        while (*(pcontrol->command-1) != 'M' && *(pcontrol->command) != 'Y') {

            Debug("Loop Control\n");
            Debug("Comando no processo Control:%c\n",*(pcontrol->command));
            sendCommandByPipeToProcessManager(pcontrol);
            pcontrol->command++;

        }
        free(commands);
        if(*(pcontrol->command) == 'Y')
            loopControl(pcontrol);
    }

    /*
     * Se for tratar a instrução M no Processo Controle aqui é o local correto
     */

    // Aguarda a finalização do processo filho (Manager) para finalizar o processo pai (Control)
    wait(NULL);
    Debug("FIM Control\n");
}