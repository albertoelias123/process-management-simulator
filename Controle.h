//
// Created by pedro on 14/08/2021.
//

#ifndef PROCESS_MANAGEMENT_SIMULATOR_CONTROLE_H
#define PROCESS_MANAGEMENT_SIMULATOR_CONTROLE_H

#include "ArvoreProcessos.h"


void processControl(TipoApontador *noRaiz);//processo controle
void processManager(int pipefd[2],TipoApontador *noRaiz);//processo gerenciador de processos



#endif //PROCESS_MANAGEMENT_SIMULATOR_CONTROLE_H
