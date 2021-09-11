//
// Created by pedro on 09/09/2021.
//

#include "TabelaProcessos.h"

TabelaDeProcessos * criaTabela(){
    TabelaDeProcessos *tabela = (TabelaDeProcessos*) malloc(sizeof(TabelaDeProcessos));
    tabela->qtd = 0;
    return tabela;
}
int insereOnTabela(TabelaDeProcessos *tabela,process *entrada){
    if(tabela->qtd <= TAM_VETOR_TABELA_POCESSOS - 1){
        int posicaoNovoProcesso;

        for(int i = 0;i<tabela->qtd;i++){
            if(tabela->processos[i] == NULL){
                posicaoNovoProcesso = i;
                tabela->processos[i] = entrada;
                tabela->qtd++;
                break;
            }

        }
        return posicaoNovoProcesso;
    }
    else{
        printf("-----------------------");
        printf("\nTabela cheia\n");
        printf("-----------------------");
        return -1;
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