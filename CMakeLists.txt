cmake_minimum_required(VERSION 3.20)
project(estruturas C)

set(CMAKE_C_STANDARD 99)

add_executable(estruturas main.c filaEstatica.c filaEstatica.h pilhaEstatica.c pilhaEstatica.h Estados.c Estados.h TabelaProcessos.c TabelaProcessos.h)
