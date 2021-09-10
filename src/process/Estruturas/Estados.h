//
// Created by pedro on 09/09/2021.
//

#ifndef ESTRUTURAS_ESTADOS_H
#define ESTRUTURAS_ESTADOS_H
#include "filaEstatica.h"


typedef struct{

    Fila *filaIndicesEstadoPronto;

}EstadoPronto;

typedef struct{

    Fila *filaIndicesEstadoBloqueado;

}EstadoBloqueado;

typedef struct{

    int indiceProcessoExecucao;

}EstadoExecucao;

void criaFilaEstadoPronto(EstadoPronto *estadoP);
void criaFilaEstadoBloqueado(EstadoBloqueado *estadoB);

#endif //ESTRUTURAS_ESTADOS_H
