//
// Created by alber on 09/09/2021.
//

#include "control.h"

void sendCommandByPipeToProcessManager(const control *pcontrol) {
    close(pcontrol->pipe[0]);
    write(pcontrol->pipe[1], pcontrol->command, sizeof(char));
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
    printf("\n--------------------------------------------------------\n");
    printf("|||||| Existem 4 tipos de comandos |||||||\n"
           "U: Fim de uma unidade de tempo\n"
           "L: Desbloqueia o primeiro processo simulado na fila bloqueada\n"
           "I: Imprime o estado atual do sistema\n"
           "M: Imprime o temo médio do ciclo e finaliza o sistema\n");
    printf("\n--------------------------------------------------------\n");
    printf("\nEntre com o comando: ");
    char *comando = (char*) malloc(sizeof(char));
    scanf("%s",comando);
    return comando;
}

char* commandsFromFile(){
    FILE *file;
    char *nameArq = (char*) malloc(50*sizeof(char ));
    printf("\nDigite o nome do arquivo de entrada:");
    scanf("%s",nameArq);
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

void setupControl(control* pcontrol,int *pipe){
    pcontrol->pipe = pipe;
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
        }while( *(pcontrol->command) != 'M');

    } else {

        char* comandos = commandsFromFile();
        pcontrol->command = comandos;
        while (*(pcontrol->command-1) != 'M') {

            Debug("Loop Control\n");
            Debug("Comando no processo Control:%c\n",*(pcontrol->command));
            sendCommandByPipeToProcessManager(pcontrol);
            pcontrol->command++;

        }
        free(comandos);

    }

    /*
     * Se for tratar a instrução M no Processo Controle aqui é o local correto
     */

    // Aguarda a finalização do processo filho (Manager) para finalizar o processo pai (Control)
    wait(NULL);
    Debug("FIM Control\n");
}