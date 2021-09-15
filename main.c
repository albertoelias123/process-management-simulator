#include "src/process/control.h"

int main(int argc, char *argv[]){
    pid_t pidMain;
    control pControl;
    manager pManager;    
    strcpy(pManager.schedullingPolitics,argv[1]); //escolha da politica de escalonamento    

    Debug("Politica: %s \n", pManager.schedullingPolitics);

    /*/////////////////////////////// Cria o pipeControlToManager////////////////////////////*/
    //se o pipeControlToManager retornar -1 significa que não houve sucesso na sua criação
    int *pipeControlToManager = (int*) malloc(2 * sizeof(int));
    int *pipeManagerToControl = (int*) malloc(2 * sizeof(int));
    if (pipe(pipeControlToManager) < 0){
        perror("Pipe");
        exit(EXIT_FAILURE);
    } else {
        printf("PipeControlToManager criado c/ sucesso\n");
    }
    if (pipe(pipeManagerToControl) < 0){
        perror("Pipe");
        exit(EXIT_FAILURE);
    } else {
        printf("PipeManagerToControl criado c/ sucesso\n");
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