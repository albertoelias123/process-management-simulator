#include "src/process/control.h"

int main(){
    process process1;
    manager *pManager = (manager*) malloc(sizeof(manager));
    processReader(&process1,"instrucoes.txt",1,1);
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
    pManager->cpu->processoExecucao = process1;
    pManager->cpu->timeUsed = 0;
    pManager->cpu->timeSlice = 0;
//    imprimeFila(pManager->estadoBloqueado);
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
    printCPU(pManager->cpu);
//    imprimeTabela(pManager->tabela);
    return EXIT_SUCCESS;
}