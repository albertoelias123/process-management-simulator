//
// Created by pedro on 14/08/2021.
//

#include "ArvoreProcessos.h"

//Estrutura Arvore
void iniciaArvore(TipoApontador *noRaiz){
    *noRaiz = NULL;//inicia a cabeça da árvore
}
// a função de inserir na árvore binária requer a verificação de uma chave e,
// assim colocar a esquerda os valores menores que a raiz e a direita os valores maiores que a raiz
int insere_ArvBin(TipoApontador *noRaiz,Process *processo){
    if (noRaiz == NULL){
        return 0;
    }
    TipoNo *novo;// Aqui criamos um noovo nó e alocamos espaço na memória para ele
    novo = (TipoApontador)malloc(sizeof(TipoNo));// Assim então ele serve para armazenar o nó e então colocar na estrutura da árvoe na posição correta
    if (novo == NULL)
        return 0;
    novo->processo = *processo;
    novo->direita = NULL;
    novo->esquerda = NULL;
    if(*noRaiz == NULL){
        *noRaiz = novo;// Aqui significa que a arvore está vazia e então podemos apenas inserir o nó na raiz
    }
    else{// Aqui utilizamos uma variável auxiliar chamada de "ant" que armazena o nó anterior ao nó atual,
        // para que ao verificar a possição correta para alocar o novo nó, termos acesso ao nó correto e alocar na esquerda se menor ou na direita se maior
        TipoNo *atual = *noRaiz;
        TipoNo *ant = NULL;
        while (atual != NULL){
            ant = atual;
            if (processo->PID == atual->processo.PID){
                free(novo);
                return 0;// elemento ja existe
            }
            if (processo->priority > atual->processo.priority)
                atual = atual->direita;
            else
                atual = atual->esquerda;
        }
        if (processo->priority > ant->processo.priority){
            ant->direita = novo;
        }
        else{
            ant->esquerda = novo;
        }
    }
    return 1;
}
//Para obter a altura de uma arvore, levamos em consideração o maior caminho da raiz até a folha
//Para analizar as possibilidades , utilizamos uma função recursiva que caminha pela arvore tanto pela esquerda, quanto pela direita
//Após isso, verificamos qual caminho possui uma altura maior e então acrescentamos 1 em seu valor ate percorrer toda a árvore
//caso o caminho da esquerda for maior que o da direita ou seja igual, retornamos a altura da esquerda + 1 , visto que se quando encontramos um nó nullo,
//A função retorna -1.
int alturaArvore(TipoApontador noRaiz){
    if (noRaiz == NULL){
        return -1;
    }
    else{
        int alturaEsquerda = alturaArvore(noRaiz->esquerda);
        int alturaDireita = alturaArvore(noRaiz->direita);
        if (alturaEsquerda < alturaDireita){
            return alturaDireita + 1;
        }
        else
            return alturaEsquerda + 1;
    }
}

// mostra os processos em ordem de prioridade
void emOrdem(TipoApontador *noRaiz){
    TipoApontador auxiliar = *noRaiz;
    if (auxiliar->esquerda != NULL){
        emOrdem(&auxiliar->esquerda);
    }

    //aqui deve imprimir os processos em ordem de prioridade

    if (auxiliar->direita != NULL){
        emOrdem(&auxiliar->direita);
    }
}
void ordemDecrescente(TipoApontador *noRaiz){
    TipoApontador auxiliar = *noRaiz;
    if (auxiliar->direita != NULL){
        ordemDecrescente(&auxiliar->direita);
    }

    //aqui deve imprimir os valores em ordem decrescente

    if (auxiliar->esquerda != NULL){
        ordemDecrescente(&auxiliar->esquerda);
    }
}

void maiorElemento(TipoApontador *noRaiz){
    TipoApontador auxiliar = *noRaiz;
    if (auxiliar->direita != NULL){
        maiorElemento(&auxiliar->direita);
    }
    else {
        // aqui deve mostrar o processo com o valor de prioridade maior
    }
}
void retirada(TipoApontador *noRaiz,pid_t pid){
    TipoApontador aux_remove;
    if (*noRaiz == NULL){//significa que a arvore é nula ou a chave não existe dentro da árvore
        printf("\n|||||||||| Arvore  vazia ou no nao existente ||||||||||\n");
        return;
    }
    else{
        if (pid < (*noRaiz)->processo.PID){
            retirada(&(*noRaiz)->esquerda,pid);
        }
        else if (pid > (*noRaiz)->processo.PID){
            retirada(&(*noRaiz)->direita,pid);
        } // percorrenco a árvore com relação ao valor da chave para saber se ela se encontra a direita ou a esquerda do no
        else{// o nó foi encontrado e agora podemos analisar os casos de ocorrencia
            if ((*noRaiz)->direita == NULL && (*noRaiz)->esquerda != NULL){ // significa q tem um nó a esquerda e devemos fazer o nó atual apontar para ele
                aux_remove = *noRaiz;
                (*noRaiz) = (*noRaiz)->esquerda;
                free(aux_remove);
            }
            else if ((*noRaiz)->direita != NULL && (*noRaiz)->esquerda != NULL){// significa que o nó possui 2 filhos e devemos chamar a função antecessor
                antecessor((*noRaiz),&(*noRaiz)->esquerda);
            }
            else if ((*noRaiz)->esquerda == NULL && (*noRaiz)->direita != NULL){// significa que o nó possui um filho a direita e o no atual deve apontar para ele
                aux_remove = *noRaiz;
                (*noRaiz) = (*noRaiz)->direita;
                free(aux_remove);
            }
            else{//chegou a um nó folha e não há mais nós a esquerda ou direita
                *noRaiz = NULL;
            }
        }
    }
}
void antecessor(TipoApontador no,TipoApontador *filho_a_esquerda){
    // a técnica do antecessor favorece a idéia de olhar para o filho a esquerda e percorrer pelos seus filhos a direita
    // até econtrar um filho a direita nulo e assim substituir o nó pelo novo nó pai que é o filho mais a direita do filho a esquerda
    TipoApontador aux;
    if ((*filho_a_esquerda)->direita != NULL){
        antecessor(no,&(*filho_a_esquerda)->direita);
        return;
    }
    no->processo = (*filho_a_esquerda)->processo;
    aux = *filho_a_esquerda;
    (*filho_a_esquerda) = (*filho_a_esquerda)->esquerda;
    free(aux);
}