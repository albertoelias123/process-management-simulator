//
// Created by alber on 09/09/2021.
//

#ifndef FROMZERO_CONTROL_H
#define FROMZERO_CONTROL_H

#include "manager.h"
#include "schedulling.h"


typedef struct control_ {
    pid_t pid;
    char *command;
    int *pipe;
}control;

void sendCommandByPipeToProcessManager(const control *pcontrol);
int choiceMode();
char* commandInteractive();
char* commandsFromFile();
void setupControl(control* pcontrol,int *pipe);
void loopControl(control* pcontrol);

#endif //FROMZERO_CONTROL_H