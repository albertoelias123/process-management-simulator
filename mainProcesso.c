#include "src/process/control.h"

int main(){
    process process1,process2,process3;
    manager *pManager = (manager*) malloc(sizeof(manager));
    process1 = *criaProcesso("processo0",1,0);
    process2 = *criaProcesso("processo0",1,0);
    process3 = *criaProcesso("processo0",2,0);
    pManager->estadoBloqueado = criaFila();
    pManager->estadoExecucao = (int*) malloc(sizeof (int));
    process1.estado = execucao;
    pManager->estadoPronto = criaFila();
    pManager->cpu = criaCPU();
    pManager->tabela = criaTabela();

    pManager->estadoExecucao = insereOnTabela(pManager->tabela,&process1);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    comandU(pManager);
    imprimeMem(&pManager->tabela->processos[pManager->estadoExecucao]->memory);
    return EXIT_SUCCESS;
}