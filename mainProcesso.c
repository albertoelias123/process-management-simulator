#include "src/process/control.h"

int main(){
    process process1;
    manager *pManager = (manager*) malloc(sizeof(manager));
    processReader(&process1,"instrucoes.txt",1,1);
//    imprimeProcesso(&process1);
    pManager->estadoBloqueado = criaFila();
    pManager->estadoExecucao = (int*) malloc(sizeof (int));
    *pManager->estadoExecucao = 0;
    pManager->estadoPronto = criaFila();
    pManager->cpu = criaCPU();
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
    pManager->cpu->reg[0].state = usando;
    pManager->cpu->reg[1].state = usando;
    pManager->cpu->reg[0].refMem = 0;
    pManager->cpu->reg[0].valor = 100;
    pManager->cpu->reg[1].refMem = 1;
    pManager->cpu->reg[1].valor = 10;
    imprimeManager(pManager);
//    imprimeFila(pManager->estadoBloqueado);
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    printCPU(pManager->cpu);
//    imprimeTabela(pManager->tabela);
    return EXIT_SUCCESS;
}