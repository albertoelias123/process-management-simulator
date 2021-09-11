#include "src/process/control.h"

int main(){
    pid_t pidMain;
    control pControl;
    manager pManager;
    /*/////////////////////////////// Cria o pipe////////////////////////////*/
    //se o pipeMain retornar -1 significa que não houve sucesso na sua criação
    int *pipeMain = (int*) malloc(2 * sizeof(int));
    if (pipe(pipeMain) < 0){
        perror("pipeMain");
        exit(EXIT_FAILURE);
    } else {
        printf("pipeMain Criado c/ sucesso\n");
    }
    /* ///////////////////////////////////////////////////////////////// */

    if((pidMain = fork()) < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pidMain > 0){
//         Processo Control
        setupControl(&pControl, pipeMain);

        loopControl(&pControl);
    }
    else{
//         Processo Manager
        setupManager(&pManager, pipeMain);

        loopManager(&pManager);

    }

    return EXIT_SUCCESS;
}