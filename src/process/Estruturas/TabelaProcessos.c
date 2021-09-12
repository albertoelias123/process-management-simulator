//
// Created by pedro on 09/09/2021.
//

#include "TabelaProcessos.h"

TabelaDeProcessos * criaTabela(){
    TabelaDeProcessos *tabela = (TabelaDeProcessos*) malloc(sizeof(TabelaDeProcessos));
    tabela->qtd = 0;
    for(int i = 0;i<TAM_VETOR_TABELA_POCESSOS;i++){
        tabela->processos[i]= NULL;
    }
    return tabela;
}
void imprimeTabela(TabelaDeProcessos *tabela){
    printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||| Tabela de processos ||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\t ID\t\t\t  State\t\t\t Time CPU used\t\t\t Nº instructions\t\t\t Time start\t\t\t  memory used");
    for(int i = 0;i<tabela->qtd;i++){
        imprimeProcesso(tabela->processos[i]);
        printf("\n");
    }
}
int isTabelaEmpty(TabelaDeProcessos *tabela){
    if(tabela->processos[0] == NULL){
        return TRUE;
    }
    return FALSE;
}
int insereOnTabela(TabelaDeProcessos *tabela,process *entrada){
    if(tabela->qtd < TAM_VETOR_TABELA_POCESSOS){
        int posicaoNovoProcesso;
        for (int i = 0; i <= tabela->qtd; i++) {
            if (tabela->processos[i] == NULL) {
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