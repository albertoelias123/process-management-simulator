//
// Created by pedro on 14/08/2021.
//

#ifndef PROCESS_MANAGEMENT_SIMULATOR_ARVOREPROCESSOS_H
#define PROCESS_MANAGEMENT_SIMULATOR_ARVOREPROCESSOS_H

#include "Processo.h"

typedef struct TipoNo *TipoApontador;

typedef struct TipoNo{
    TipoApontador esquerda, direita;
    Process processo;
}TipoNo;

//Funções Arvore
void iniciaArvore(TipoApontador *noRaiz);
void maiorElemento(TipoApontador *noRaiz);
int insere_ArvBin(TipoApontador *noRaiz,Process *processo);
int alturaArvore(TipoApontador noRaiz);
void emOrdem(TipoApontador *noRaiz);
void ordemDecrescente(TipoApontador *noRaiz);
void antecessor(TipoApontador no,TipoApontador *filho_a_esquerda);
void retirada(TipoApontador *noRaiz,pid_t pid);

#endif //PROCESS_MANAGEMENT_SIMULATOR_ARVOREPROCESSOS_H
