#include "src/process/control.h"

int main(){
    process process1;
    manager *pManager = (manager*) malloc(sizeof(manager));
    processReader(&process1,"instrucoes.txt");
//    imprimeProcesso(&process1);
    pManager->estadoBloqueado = criaFila();
    pManager->estadoExecucao = criaFila();
    pManager->estadoPronto = criaFila();

    pManager->tabela = criaTabela();

    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));

//    imprimeFila(pManager->estadoBloqueado);
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));

    imprimeTabela(pManager->tabela);
    return EXIT_SUCCESS;
}