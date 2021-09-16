#include "src/process/control.h"

int main(int argc, char *argv[]){
    pid_t pidMain;
    control pControl;
    manager pManager;
    strcpy(pManager.schedullingPolitics,argv[1]); //escolha da politica de escalonamento

    if(strcmp(pManager.schedullingPolitics, "P") == 0)
        printf("Politica de Prioridade\n");
    else if(strcmp(pManager.schedullingPolitics, "F") == 0)
        printf("Politica FIFO\n");
    else{
        printf("Politica Não Definida\n");
        exit(EXIT_FAILURE);
    }

    /*/////////////////////////////// Cria o pipeControlToManager////////////////////////////*/
    //se o pipeControlToManager retornar -1 significa que não houve sucesso na sua criação
    int *pipeControlToManager = (int*) malloc(2 * sizeof(int));
    int *pipeManagerToControl = (int*) malloc(2 * sizeof(int));
    if (pipe(pipeControlToManager) < 0){
        perror("Pipe Control");
        exit(EXIT_FAILURE);
    } else {
        Debug("PipeControlToManager criado c/ sucesso\n");
    }
    if (pipe(pipeManagerToControl) < 0){
        perror("Pipe Manager");
        exit(EXIT_FAILURE);
    } else {
        Debug("PipeManagerToControl criado c/ sucesso\n");
    }
    /* ///////////////////////////////////////////////////////////////// */

    if((pidMain = fork()) < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pidMain > 0){

        //Processo Control
        setupControl(&pControl, pipeControlToManager, pipeManagerToControl);
        loopControl(&pControl);

    }
    else{

        //Processo Manager
        setupManager(&pManager, pipeControlToManager, pipeManagerToControl);
        loopManager(&pManager);

    }

    return EXIT_SUCCESS;
}