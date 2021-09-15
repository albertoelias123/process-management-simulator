#include "manager.h"
#include <math.h>


#include "Estruturas/simulatedProcess.h"


void dispatcher(manager *pManager, int indexPtoCPU);
void prioritySchedulling(manager *pManager);
void fifoSchedulling(manager *pManager);
void processSort(manager *pManager);