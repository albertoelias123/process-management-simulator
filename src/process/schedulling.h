#include "manager.h"
#include <math.h>


#include "Estruturas/simulatedProcess.h"


CPU *criaCPU();
void executa(process *processo,manager *pManager);
void sum(process *processOnCpu);
void sub(process *processOnCpu);
void printCPU(CPU *cpu);

void dispatcher(manager *pManager, int indexPtoCPU);
void prioritySchedulling(manager *pManager, char *command, int nextProcess);
void nonPreemptiveSchedulling(manager *pManager, char *command, int nextProcess);
void processSort(manager *pManager);