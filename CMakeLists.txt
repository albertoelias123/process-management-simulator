cmake_minimum_required(VERSION 3.20)
project(process_management_simulator C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(process_management_simulator
        main.c Controle.c Controle.h Processo.c Processo.h ProcessMemory.c ProcessMemory.h filaProcessos.c filaProcessos.h Interface.c Interface.h)
