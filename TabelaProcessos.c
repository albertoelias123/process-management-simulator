//
// Created by pedro on 09/09/2021.
//

#include "TabelaProcessos.h"

TabelaDeProcessos *criaTabela(){
    TabelaDeProcessos *tabela = (TabelaDeProcessos*) malloc(sizeof(TabelaDeProcessos));
    tabela->qtd = 0;
    return tabela;
}
void insereOnTabela(TabelaDeProcessos *tabela,EntradaTabela *entrada){
    if(tabela->qtd <= MAXTAM - 1){
        tabela->vetor[tabela->qtd] = *entrada;
        tabela->qtd++;
    }
    else{
        printf("\nTabela cheia\n");
    }
}
TabelaDeProcessos *removeOfTabela(TabelaDeProcessos *tabela,pid_t pidProcess){//conferir depois a ideia
    TabelaDeProcessos *tabaleAux = criaTabela();
    if(tabela->qtd > 0){
        for(int i = 0;i<tabela->qtd;i++){
            if(tabela->vetor[i].pidProcesso == pidProcess){
                insereOnTabela(tabaleAux,&tabela->vetor[i]);
            }
        }
    }
    return tabaleAux;
}