//
// Created by pedro on 09/09/2021.
//

#include "TabelaProcessos.h"

TabelaDeProcessos *criaTabela(){
    TabelaDeProcessos *tabela = (TabelaDeProcessos*) malloc(sizeof(TabelaDeProcessos));
    tabela->qtd = 0;
    return tabela;
}
void insereOnTabela(TabelaDeProcessos *tabela,process *entrada){
    if(tabela->qtd <= MAXTAM - 1){
        for(int i = 0;i<tabela->qtd;i++){
            if(tabela->processos[i] == NULL){
                tabela->processos[i] = entrada;
                tabela->qtd++;
                break;
            }
        }
    }
    else{
        printf("-----------------------");
        printf("\nTabela cheia\n");
        printf("-----------------------");
    }
}
void removeOfTabela(TabelaDeProcessos *tabela,int pidProcess){//conferir depois a ideia
    if(tabela->qtd > 0){
        for(int i = 0;i<tabela->qtd;i++){
            if(tabela->processos[i]->pid == pidProcess){
                free(tabela->processos[i]);
                tabela->processos[i] = NULL;
                tabela->qtd--;
            }

        }
    }
}