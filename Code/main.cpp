
#include <iostream>
#include <iomanip>
#include <map>
#include <stdint.h>
#include <string>

using namespace std;

#include "globals.h"
#include "memoria.cpp"
#include "riscv.cpp"

int main (int argc, const char * argv[]) {

    int n;
    init();     // inicia parametros globais

    load_mem("code.bin", 0);
    load_mem("data.bin", 0x2000);
    mem[8196/4] = 0;
    // Coloquei esse apenas para parar o erro da memoria
    

    run();
    /*
    cout << "\n"<<rd<<"\n";
    cout << "Numero de instrucoes a imprimir: ";
    cin >> n;
    for (int i=0; i < n; i++) {
        fetch();
        //cout << "\n decode : ";
        decode();
        //cout << "\n execute :";
        execute();
        cout << "Instr = " << instr_str[instruction]
             <<  " Imm = " << imm32_t
             << " rs1 = " << rs1
             << " rs2 = " << rs2
             << " rd = " << rd
             << " PC = " << pc
             << endl;
    }

    int address;

    cout << "\nNumero de palavras a imprimir: ";
    cin >> n;
    cout << "\n\nEndereco inicial: ";
    cin >> address;
    for (int i=0; i < n; i++) {
        int end = (address>>2) + i;
        printf("mem[%d] = %x\n", end, mem[end]);
    }
    */
    cout << "\n\n Registradores \n";
    dump_registers();

    return 0;

}
