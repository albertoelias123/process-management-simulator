#include "src/process/control.h"

int main(){
    process process1;
    processReader(&process1,"instrucoes.txt");
    imprimeProcesso(&process1);

    return EXIT_SUCCESS;
}