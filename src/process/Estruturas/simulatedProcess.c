//
// Created by pedro on 09/09/2021.
//

#include "simulatedProcess.h"

process *criaProcesso(char *fileName,int pid,int ppid){

    process *process1 = (process*) malloc(sizeof(process));
    char *newStr = (char*) malloc((strlen(fileName)+10)*sizeof(char));
    strcpy(newStr,fileName);
    strcat(newStr,".txt");
    inicializaProcess(process1,pid,ppid);
    processReader(process1,newStr);
    return process1;

}

void inicializaProcess(process *processo, int pid, int ppid){
    processo->PC = 0;
    processo->qtdInstructions = 0;
    processo->memory = *createMemory();
    processo->estado = bloqueado;
    processo->priority = 0;
    processo->timeStart = -1;
    processo->timeCpuUsed = 0;
    processo->ppid = ppid;
    processo->pid = pid;
}
void processReader(process *processo, char *filename){
    int PC = 0, index, numVar, declaration, value;
    char fileN[20];
//    /*leitura de arquivo*/
    FILE *fl;
    processo->PC = 0;
    processo->qtdInstructions = 0;
    char *buf = (char*)malloc(sizeof(char));
    fl = fopen(filename,"r");
    if ( fl == NULL){
        printf("File not found!\n");
        return;
    }
    else {
        while (fscanf(fl, "%s", buf) != EOF) {
            if (strcmp(buf, "N") == 0) {
                processo->vetorPrograma[PC].comando = 'N';
                fscanf(fl, "%d", &numVar);
                processo->vetorPrograma[PC].N.valor = numVar;
                processo->qtdInstructions++;
                PC++;
            }
            else if (strcmp(buf, "D") == 0) {
                processo->vetorPrograma[PC].comando = 'D';
                fscanf(fl, "%d", &index);
                processo->vetorPrograma[PC].D.refMem = index;
                processo->qtdInstructions++;
                PC++;
            }
            else if (strcmp(buf, "V") == 0) {
                processo->vetorPrograma[PC].comando = 'V';
                fscanf(fl, "%d %d", &index, &value);
                processo->vetorPrograma[PC].operation.valores.refMem = index;
                processo->vetorPrograma[PC].operation.valores.valor = value;
                processo->qtdInstructions++;
                PC++;
            }
            else if (strcmp(buf, "A") == 0) {
                processo->vetorPrograma[PC].comando = 'A';
                fscanf(fl, "%d %d", &index, &value);
                processo->vetorPrograma[PC].operation.valores.refMem = index;
                processo->vetorPrograma[PC].operation.valores.valor = value;
                processo->qtdInstructions++;
                PC++;
            }
            else if (strcmp(buf, "S") == 0) {
                processo->vetorPrograma[PC].comando = 'S';
                fscanf(fl, "%d %d", &index, &value);
                processo->vetorPrograma[PC].operation.valores.refMem = index;
                processo->vetorPrograma[PC].operation.valores.valor = value;
                processo->qtdInstructions++;
                PC++;
            }
            else if (strcmp(buf, "B") == 0) {
                processo->vetorPrograma[PC].comando = 'B';
                processo->qtdInstructions++;
                PC++;
            }
            else if (strcmp(buf, "T") == 0) {
                processo->vetorPrograma[PC].comando = 'T';
                processo->qtdInstructions++;
                PC++;
            }
            else if (strcmp(buf, "F") == 0) {
                processo->vetorPrograma[PC].comando = 'F';
                fscanf(fl, "%d", &value);
                processo->vetorPrograma[PC].F.valor = value;
                processo->qtdInstructions++;
                PC++;
            }
            else if (strcmp(buf, "R") == 0) {
                processo->vetorPrograma[PC].comando = 'R';
                fscanf(fl, "%s", fileN);
                processo->vetorPrograma[PC].R.file = (char *) malloc(strlen(fileN) * sizeof(char));
                strcpy(processo->vetorPrograma[PC].R.file, fileN);
                processo->qtdInstructions++;
                PC++;
            }
            else{
                printf("\n-------------------------\n");
                printf("Instrucao nao reconhecida");
                printf("\n-------------------------\n");
            }
        }
        fclose(fl);
    }
}

void imprimeMem(memProcess *mem){
    printf("\n|||||||||| Memoria do processo em execucao ||||||||||\n");
    for(int i = 0;i<mem->qtd; i++){
        if(i + 1 < mem->qtd)
            printf("[%d]=%d | ", mem->position[i]->posicao, mem->position[i]->valor);
        else
            printf("[%d]=%d\n", mem->position[i]->posicao, mem->position[i]->valor);
    }
}

void imprimeInstrucoesProcesso(process *processo){
    printf("\n");
    for(int i = 0;i<processo->qtdInstructions;i++){
        if(processo->vetorPrograma[i].comando == 'N'){
            printf("N:%d -> ",processo->vetorPrograma[i].N.valor);
        }
        else if(processo->vetorPrograma[i].comando == 'D'){
            printf("D:%d -> ",processo->vetorPrograma[i].D.refMem);
        }
        else if(processo->vetorPrograma[i].comando == 'V' || processo->vetorPrograma[i].comando == 'A' || processo->vetorPrograma[i].comando == 'S'){
            printf("%c:%d %d -> ",processo->vetorPrograma[i].comando,processo->vetorPrograma[i].operation.valores.refMem,processo->vetorPrograma[i].operation.valores.valor);
        }
        else if(processo->vetorPrograma[i].comando == 'F'){
            printf("F:%d -> ",processo->vetorPrograma[i].F.valor);
        }
        else if(processo->vetorPrograma[i].comando == 'R'){
            printf("R:%s -> ",processo->vetorPrograma[i].R.file);
        }
        else if(processo->vetorPrograma[i].comando == 'T'){
            printf("T -> ");
        }
        else if(processo->vetorPrograma[i].comando == 'B')
            printf("B -> ");
    }
    printf("\n");
}

void imprimeProcesso(process *processo){
    printf("| ");
    printf("%-3d",processo->pid);// ID
    printf(" | ");
    printf("%-4d",processo->ppid);// ID
    printf(" | ");
    if(processo->estado == bloqueado){
        printf("%-5s", "Bloq");
    }
    else if(processo->estado == execucao){
        printf("%-5s", "Exec");
    }
    else if(processo->estado == pronto){
        printf("%-5s", "Pron");
    }
    printf(" | ");
    printf("%-8d",processo->timeCpuUsed);// Time CPU
    printf(" | ");
    printf("%-9d",processo->qtdInstructions); // Instructions
    printf(" | ");
    printf("%-2d",processo->PC); // PC
    printf(" | ");
    printf("%-10d",processo->timeStart); // Time Start
    printf(" | ");
    printf("%-7.2f%%",(float)(processo->memory.qtd * 100) / TAM_VETOR_MEMORIA); // Mem Used
    printf(" | ");
    printf("%-4d",processo->priority);
    printf(" |");
}


memProcess *createMemory(){
    memProcess *mem = (memProcess*) malloc(sizeof(memProcess));
    mem->qtd = 0;
    for(int i = 0;i<TAM_VETOR_MEMORIA;i++){
        mem->position[i] = NULL;
    }
    return mem;
}
int memFull(memProcess *mem){
    if(mem->qtd == TAM_VETOR_MEMORIA - 1){
        return TRUE;
    }
    return FALSE;
}
int memEmpty(memProcess *mem){
    if(mem->qtd == 0){
        return TRUE;
    }
    return FALSE;
}

void insereOnMemory(memProcess *mem,int valor,int posicao){
    if(!memFull(mem) && posicao < TAM_VETOR_MEMORIA){
        estruturaMem *novaEstrutura = (estruturaMem*) malloc(sizeof(estruturaMem));
        novaEstrutura->posicao = posicao;
        novaEstrutura->valor = valor;
        mem->position[mem->qtd++] = novaEstrutura;
    }
    else{
        printf("\n--------------------------------------");
        printf("\nMemoria cheia ou posicao inexistente\n");
        printf("--------------------------------------\n");
    }
}

