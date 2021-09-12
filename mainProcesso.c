#include "src/process/control.h"

int main(){
    process process1,process2,process3;
    manager *pManager = (manager*) malloc(sizeof(manager));
    process1 = *criaProcesso(pManager,"processo0",0,0);
    process2 = *criaProcesso(pManager,"processo0",1,0);
    process3 = *criaProcesso(pManager,"processo0",2,0);
    pManager->estadoBloqueado = criaFila();
    pManager->estadoExecucao = (int*) malloc(sizeof (int));
    process1.estado = execucao;
    pManager->estadoPronto = criaFila();
    pManager->cpu = criaCPU();
    pManager->tabela = criaTabela();

    *pManager->estadoExecucao = insereOnTabela(pManager->tabela,&process1);
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process2));
    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process3));
//    comandL(pManager);
//    comandL(pManager);
//    comandL(pManager);
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
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
//    comandU(pManager);
//    imprimeManager(pManager);
//    imprimeFila(pManager->estadoBloqueado);
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    printCPU(pManager->cpu);
//    imprimeTabela(pManager->tabela);
    return EXIT_SUCCESS;
}