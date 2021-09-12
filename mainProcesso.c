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
    process1.PC = 3;
    pManager->cpu->processoExecucao = process1;
    executa(pManager->cpu);
    process1.PC = 5;
    pManager->cpu->processoExecucao = process1;
    executa(pManager->cpu);
//    imprimeManager(pManager);
//    comandU(pManager);
//    imprimeManager(pManager);
//    imprimeFila(pManager->estadoBloqueado);
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    insereOnFila(pManager->estadoBloqueado,insereOnTabela(pManager->tabela,&process1));
//    printCPU(pManager->cpu);
//    imprimeTabela(pManager->tabela);
    return EXIT_SUCCESS;
}