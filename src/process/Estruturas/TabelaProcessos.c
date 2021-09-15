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
void alteraEstadoParaPronto(TabelaDeProcessos *tabela, int indice){
    if(0 <= indice && indice < TAM_VETOR_TABELA_POCESSOS) {
        tabela->processos[indice]->estado = pronto;
    }
    else {
        printf("\n----------------------------\n");
        printf("Indice nao existente na tabela");
        printf("\n----------------------------\n");
    }
}
void alteraEstadoParaExecucao(TabelaDeProcessos *tabela, int indice){
    if(0 <= indice && indice < TAM_VETOR_TABELA_POCESSOS) {
        tabela->processos[indice]->estado = execucao;
    }
    else {
        printf("\n----------------------------\n");
        printf("Indice nao existente na tabela");
        printf("\n----------------------------\n");
    }
}
void imprimeTabela(TabelaDeProcessos *tabela){
    printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||| Tabela de processos ||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|  ID  | State | Time CPU | instructs | PC | Time start | Mem used |\n");
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