cmake_minimum_required(VERSION 3.16)
project(processManager C)

set(CMAKE_C_STANDARD 99)

add_executable(processManager main.c src/process/Estruturas/filaEstatica.c src/process/Estruturas/filaEstatica.h src/process/Estruturas/TabelaProcessos.c src/process/Estruturas/TabelaProcessos.h src/process/Estruturas/simulatedProcess.c src/process/Estruturas/simulatedProcess.h src/process/control.c src/process/control.h src/process/manager.c src/process/manager.h src/process/Estruturas/CPU.c src/process/Estruturas/CPU.h src/process/schedulling.h src/process/schedulling.c)

target_link_libraries(processManager m)