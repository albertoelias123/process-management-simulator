cmake_minimum_required(VERSION 3.20)
project(estruturas C)

set(CMAKE_C_STANDARD 99)

add_executable(estruturas main.c src/process/Estruturas/filaEstatica.c src/process/Estruturas/filaEstatica.h src/process/Estruturas/pilhaEstatica.c src/process/Estruturas/pilhaEstatica.h src/process/Estruturas/Estados.c src/process/Estruturas/Estados.h src/process/Estruturas/TabelaProcessos.c src/process/Estruturas/TabelaProcessos.h src/process/Estruturas/simulatedProcess.c src/process/Estruturas/simulatedProcess.h src/process/control.c src/process/control.h src/process/manager.c src/process/manager.h src/process/Estruturas/CPU.c src/process/Estruturas/CPU.h)
