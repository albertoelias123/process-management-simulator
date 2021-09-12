//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_SIMULATEDPROCESS_H
#define ESTRUTURAS_SIMULATEDPROCESS_H

#define TAM_VETOR_PROGRAMA 1000
#define TAM_VETOR_MEMORIA 1000

#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

//memcpy() // copia de uma parte da memoria para outra


typedef enum{
    bloqueado,pronto,execucao
}type;

typedef struct{

    int valor;
    int posicao;

}estruturaMem;

typedef struct{
    char comando;

    union{
        int refMem;
    }D;
    union{
        int valor;
    }N;

    union{
        struct{
            int refMem;
            int valor;
        }valores;
    }operation;

    union{
        int valor;
    }F;
    union{
        char *file;
    }R;

}instrucao;

typedef struct{
    estruturaMem *memory[TAM_VETOR_MEMORIA]; // define a posicao 0 valendo 0 //  define a posicao 1 valendo 0 // coloca o valor 1000 na posicao 0
    int memUsed;//MAXTAM == 2
}memProcess;


typedef struct{
    int PC;//começa de 0 // pc passa para 1 // pc passa para 2 //pc passa para 3
    type estado;//em execucao
    instrucao vetorPrograma[TAM_VETOR_PROGRAMA];
    memProcess memory;//
    int pid;//simula o pid mesmo
    int ppid;//simula o pid do processo pai
    int timeStart;
    int timeCpuUsed;
    int priority;
    int qtdInstructions;
}process;

//troca de contexto envolve copiar o estado do processo recém escalonado da tabela de processos
//para a CPU

//enquanto vc esta na CPU vc n pode acessar a tabela e processos
//é uma copia em CPU

//ao final vc pega o processo da CPU e salva na tabela de processos


void inicializaProcess(process *processo, int pid, int ppid);
memProcess *createMemory();
int memFull(memProcess *mem);
int memEmpty(memProcess *mem);
void insereOnMemory(memProcess *mem,int valor,int posicao);
void imprimeMem(memProcess *mem);
void processReader(process *processo, char *filename, int pid, int ppid);
void imprimeTesteProcesso(process *processo);
void imprimeProcesso(process *processo);


#endif //ESTRUTURAS_SIMULATEDPROCESS_H
