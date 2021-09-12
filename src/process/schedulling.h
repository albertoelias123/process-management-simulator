#include "manager.h"
#include <math.h>


void schedulling(manager *pManager, int indexPtoCPU);
void prioritySchedulling(manager *pManager, char *command, int nextProcess);
void nonPreemptiveSchedulling(manager *pManager, char *command, int nextProcess);