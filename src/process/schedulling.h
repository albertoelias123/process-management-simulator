#include "manager.h"
#include <math.h>


#include "Estruturas/simulatedProcess.h"


void dispatcher(manager *pManager, int indexPtoCPU);
void schedulling(manager *pManager);
void prioritySchedulling(manager *pManager);
void nonPreemptiveSchedulling(manager *pManager);
void processSort(manager *pManager);