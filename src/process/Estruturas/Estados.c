//
// Created by pedro on 09/09/2021.
//

#include "Estados.h"

void criaFilaEstadoPronto(EstadoPronto *estadoP){
    estadoP->filaIndicesEstadoPronto = criaFila();
}
void criaFilaEstadoBloqueado(EstadoBloqueado *estadoB){
    estadoB->filaIndicesEstadoBloqueado = criaFila();
}