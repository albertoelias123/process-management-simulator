//
// Created by pedro on 14/08/2021.
//

#include "Controle.h"


void processControl(TipoApontador *noRaiz){
    int pipefd[2];//variável para crição do pipe (processo pai e processo filho)
    int value = pipe(pipefd);
    if (value < 0){//se o pipe retornar -1 significa que não houve sucesso na sua criação
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    processManager(pipefd,noRaiz);
}
void processManager(int pipefd[2],TipoApontador *noRaiz){
    Process processoInicial;
    processCreate(&processoInicial,0);
    manipulateProcess(&processoInicial,0,0,0,"prioridade");
    //os outros elementos virão de um arquivo

    //ao final a gente inclui o elemento na árvore
    insere_ArvBin(noRaiz,&processoInicial);
}
