//
// Created by pedro on 09/09/2021.
//

#include "simulatedProcess.h"
void inicializaProcess(process *processo, int pid, int ppid){
    processo->PC = 0;
    processo->qtdInstructions = 0;
    processo->memory = *createMemory();
    processo->estado = bloqueado;
    processo->priority = 0;
    processo->timeStart = 0;
    processo->timeCpuUsed = 0;
    processo->ppid = ppid;
    processo->pid = pid;
}
void processReader(process *processo, char *filename, int pid, int ppid){
    int PC = 0, index, numVar, declaration, value;
    char fileN[20];
//    /*leitura de arquivo*/

    inicializaProcess(processo, pid, ppid);

    FILE *fl;

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
                insereOnMemory(&processo->memory, 0, index);
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
    printf("\n||||||||||Memoria processo||||||||||\n");
    for(int i = 0;i<mem->memUsed;i++){
        if(i + 1 < mem->memUsed)
            printf("[%d]=%d | ",mem->memory[i]->posicao,mem->memory[i]->valor);
        else
            printf("[%d]=%d\n",mem->memory[i]->posicao,mem->memory[i]->valor);
    }
}

void imprimeTesteProcesso(process *processo){
    for(int i = 0;i<processo->qtdInstructions;i++){
        if(processo->vetorPrograma[i].comando == 'N'){
            printf("N: %d\n",processo->vetorPrograma[i].N.valor);
        }
        if(processo->vetorPrograma[i].comando == 'D'){
            printf("D: %d\n",processo->vetorPrograma[i].D.refMem);
        }
        if(processo->vetorPrograma[i].comando == 'V' || processo->vetorPrograma[i].comando == 'A' || processo->vetorPrograma[i].comando == 'S'){
            printf("%c: %d %d\n",processo->vetorPrograma[i].comando,processo->vetorPrograma[i].operation.valores.refMem,processo->vetorPrograma[i].operation.valores.valor);
        }
        if(processo->vetorPrograma[i].comando == 'F'){
            printf("F: %d\n",processo->vetorPrograma[i].F.valor);
        }
        if(processo->vetorPrograma[i].comando == 'R'){
            printf("R: %s\n",processo->vetorPrograma[i].R.file);
        }
        if(processo->vetorPrograma[i].comando == 'T'){
            printf("Comando de terminar o processo");
        }
    }
    imprimeMem(&processo->memory);
}

void imprimeProcesso(process *processo){
    printf("\n\t[%d]\t",processo->pid);
    if(processo->estado == bloqueado){
        printf("\t\tBloqueado\t");
    }
    else if(processo->estado == execucao){
        printf("\t\tEm execucao\t");
    }
    else if(processo->estado == pronto){
        printf("\t\tPronto para execucao\t");
    }
    printf("\t\t[%d] \t",processo->timeCpuUsed);
    printf("\t\t\t\t [%d] \t",processo->qtdInstructions);
    printf("\t\t\t\t\t[%d]\t",processo->timeStart);
    printf("\t\t\t\t[%.2f %] \t",(float)(processo->memory.memUsed * 100)/TAM_VETOR_MEMORIA);
}


memProcess *createMemory(){
    memProcess *mem = (memProcess*) malloc(sizeof(memProcess));
    mem->memUsed = 0;
    for(int i = 0;i<TAM_VETOR_MEMORIA;i++){
        mem->memory[i] = NULL;
    }
    return mem;
}
int memFull(memProcess *mem){
    if(mem->memUsed == TAM_VETOR_MEMORIA - 1){
        return TRUE;
    }
    return FALSE;
}
int memEmpty(memProcess *mem){
    if(mem->memUsed == 0){
        return TRUE;
    }
    return FALSE;
}

void insereOnMemory(memProcess *mem,int valor,int posicao){
    if(!memFull(mem) && posicao < TAM_VETOR_MEMORIA){
        estruturaMem *novaEstrutura = (estruturaMem*) malloc(sizeof(estruturaMem));
        novaEstrutura->posicao = posicao;
        novaEstrutura->valor = valor;
        mem->memory[mem->memUsed++] = novaEstrutura;
    }
    else{
        printf("\n--------------------------------------");
        printf("\nMemoria cheia ou posicao inexistente\n");
        printf("--------------------------------------\n");
    }
}