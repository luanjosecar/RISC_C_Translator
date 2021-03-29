

#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <map>

#include "globals.h"
// ---------- Mascaras para os sb e lb

#define MEM_SIZE 4096
#define MASK1 0xFF000000
#define MASK2 0xFF0000
#define MASK3 0xFF00
#define MASK4 0x000FF
//-----------------------------------

using namespace std;

int32_t mem[MEM_SIZE];


int32_t f_add(int32_t rs1, int32_t rs2){
    return rs1+rs2;
}

int32_t f_sub(int32_t rs1, int32_t rs2){
    return (rs1-rs2);
}

int32_t f_and(int32_t rs1, int32_t rs2){
    return (rs1 & rs2);
}

int32_t f_or(int32_t rs1, int32_t rs2){
    return (rs1 | rs2);
}

int32_t f_xor(int32_t rs1, int32_t rs2){
    return (rs1 ^ rs2);
}

int32_t sll(int32_t rs1, int32_t rs2){
    return rs1<<rs2;
}

int32_t srl(int32_t rs1, int32_t rs2){
    return rs1>>rs2;
}

int32_t beq(int32_t pc, int32_t rs1, int32_t rs2, int32_t dest){
    if(rs1 == rs2){
        return pc+dest-4;
    }
    else{
        return pc;
    }
} 

int32_t bne(int32_t pc, int32_t rs1, int32_t rs2, int32_t dest){
    if(rs1 != rs2){
        return pc+dest-4;
    }
    else{
        return pc;
    }
} 

int32_t bge(int32_t pc, int32_t rs1, int32_t rs2, int32_t dest){
    if(rs1 >= rs2){
        return pc+dest-4;
    }
    else{
        return pc;
    }
} 

int32_t bgeu(int32_t pc, uint32_t rs1, uint32_t rs2, int32_t dest){
    if(rs1 >= rs2){
        return pc+dest-4;
    }
    else{
        return pc;
    }
} 

int32_t blt(int32_t pc, int32_t rs1, int32_t rs2, int32_t dest){
    if(rs1 < rs2){
        return pc+dest-4;
    }
    else{
        return pc;
    }
} 

int32_t bltu(int32_t pc, uint32_t rs1, uint32_t rs2, int32_t dest){
    if(rs1 < rs2){
        return pc+dest-4;
    }
    else{
        return pc;
    }
} 

int32_t jal(int32_t pc, int32_t imm21, int32_t rd){
    if(rd != 0)
        breg[rd] = pc;
    return pc+imm21-4;
}

int32_t jalr(int32_t imm32_t, int32_t rs1, int32_t rd){
    if(rd != 0 ){
        breg[rd] = pc;
    }
    
     return breg[rs1]+ imm32_t;
    

}

int32_t auipc(int32_t pc, int32_t imm12_i, int32_t rd){
    breg[rd] = pc+imm12_i;
    return pc+imm12_i;
}

int32_t slt( int32_t rs1, int32_t rs2){
    if(rs1 < rs2){
        return 1;
    }
    else{
        return 0;
    }
}

int32_t sltu( uint32_t rs1, uint32_t rs2){
    if(rs1 < rs2){
        return 1;
    }
    else{
        return 0;
    }
}

// Lui pode ser feito apenas no switch associando o imediato ao registrador necessário

int32_t srai(int32_t rs1, int32_t rs2){
    int32_t base = (rs1 >> rs2);
    uint32_t aux = ~(~0u << rs2) << (32-rs2);

    if (rs1 < 0 && rs2 > 0){
        return (base|aux);
    }else 
    {return rs1 >> rs2;}
}

int32_t srli(int32_t sr1, int32_t rs2){
    uint32_t aux = sr1;
    return (aux>>rs2);
}


void ecall(){

    if ( breg[A7] == 1){
        //cout << "\n\n"<<breg[A0]<<"\n\n" ;
        cout <<breg[A0] ;
    }

    if ( breg[A7] == 2){
        int variavel;
        cin >> variavel;
        breg[A0] = variavel;
    }

    if(breg[A7] == 10){
        cout << "\n\n Encerando o Programa \n";
        stop_prg = true;
    }
}


int32_t lb(uint32_t adress, int32_t kte){
    
    int32_t memAdress = (adress+kte)/4;
    int32_t tempRegist1;
    int8_t tempRegist2;
    int32_t byteAdress = ((adress+kte)%4);

    switch(byteAdress){
        case 0:
            tempRegist1 = mem[memAdress] & MASK4;
            tempRegist2 = tempRegist1;
            return tempRegist1 = tempRegist2;
        break;
        case 1:
            tempRegist1 = mem[memAdress] & MASK3;
            tempRegist2 = tempRegist1>>8;
            return tempRegist1 = tempRegist2;
        break;
        case 2:
            tempRegist1 = mem[memAdress] & MASK2;
            tempRegist2 = (tempRegist1>>16);
            return tempRegist1 = tempRegist2;
        break;
        case 3:
            tempRegist1 = mem[memAdress] & MASK1;
            tempRegist2 = (tempRegist1>>24);
            return tempRegist1 = tempRegist2;
        break;
        default:
            return 0;
            break;
    }
}

int32_t lbu(uint32_t adress, int32_t kte){
    int32_t memAdress = (adress+kte)/4;
    uint32_t tempRegist;
    int32_t byteAdress = ((adress+kte)%4);
    switch(byteAdress){
        case 0:
            tempRegist = mem[memAdress] & MASK4;
            return tempRegist & MASK4;
        break;
        case 1:
            tempRegist = mem[memAdress] & MASK3;
            tempRegist = (tempRegist>>8);
            return tempRegist & MASK4;
        break;
        case 2:
            tempRegist = mem[memAdress] & MASK2;
            tempRegist = (tempRegist>>16);
            return tempRegist & MASK4;
        break;
        case 3:
            tempRegist = mem[memAdress] & MASK1;
            tempRegist = (tempRegist>>24);
            return tempRegist & MASK4;
        break;
        default:
            return 0;
            break;
    }
}



void sb(uint32_t adress, int32_t kte, int8_t dado){
    int32_t memAdress = (adress+kte)/4;
    int32_t tempRegist1;
    int32_t tempRegist2;;
    int32_t byteAdress = ((adress+kte)%4);
    //printf("Dado = \t%8d \t\t\t%8x\n", dado, dado);
    switch(byteAdress){
        case 0:
            tempRegist2 = dado & MASK4;
            tempRegist1 = (mem[memAdress] & (~MASK4));
            tempRegist1 = (tempRegist1 | tempRegist2);
            mem[memAdress] = tempRegist1;
        break;
        case 1:
            tempRegist2 = (dado & MASK4) << 8;
            tempRegist1 = (mem[memAdress] & (~MASK3));
            tempRegist2 = (tempRegist2<<8);
            tempRegist1 = (tempRegist1 | tempRegist2);
            mem[memAdress] = tempRegist1;
        break;
        case 2:
            tempRegist2 = (dado & MASK4) << 16;
            tempRegist1 = mem[memAdress] & (~MASK2);
            tempRegist2 = (tempRegist2<<16);
            tempRegist1 = (tempRegist1 | tempRegist2);
            mem[memAdress] = tempRegist1;
        break;
        case 3:
            tempRegist2 = (dado & MASK4) <<24;
            tempRegist1 = (mem[memAdress] & (~MASK1));
            tempRegist2 = (tempRegist2<<24);
            tempRegist1 = (tempRegist1 | tempRegist2);
            mem[memAdress] = tempRegist1;
        break;
    }

}

void sw(uint32_t adress, int32_t kte, int32_t dado){
    int32_t memAdress = adress+kte;
    if( memAdress%4 == 0){
        mem[memAdress/4] = dado;
    }
    else{
        cout <<"error \n";
    }
};

int32_t lw(uint32_t adress, int32_t kte){
    int32_t memAdress = adress+kte;

    if(memAdress%4 == 0){
        //printf("Sucess \n");
        return mem[memAdress/4];
    }
    else{
        cout << "erro \n";
        return 0;
    }

}


