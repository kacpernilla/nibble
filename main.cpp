#include <iostream>
#include <cstdint>
#include <cstddef>

/*
    8 registers
    r0, r1, r2, ...

    pc - program counter
    sp - stack pointer
    flags - flagi procesora

    ram: 4096 bytes
*/

class CPU {
    public:
    uint8_t registers[8] {};
    uint16_t pc {};
    uint16_t sp {};
    uint8_t flags {};

    uint8_t memory[4096] {};

    bool halt {};

    ////

    uint8_t fetch(){
        return memory[pc++];
    }

    void step(){
        uint8_t opcode = fetch();

        switch(opcode) {
            case 0x01: {
                uint8_t destination = fetch();
                uint8_t value = fetch();
                MOV(destination, value);
                break;
            }

            case 0x02: {
                uint8_t dest = fetch();
                uint8_t src = fetch();
                ADD(dest, src);
                break;
            }
            
            case 0xFF: {
                HALT();
                break;
            }
        }
    }

    void HALT() { this->halt = true; }

    void MOV(uint8_t destination, int value) { registers[destination] = value; }
    // void MOV(uint8_t destination, uint8_t source_register) { registers[destination] = registers[source_register]; }

    void ADD(uint8_t destination_reg, uint8_t source_reg) { registers[destination_reg] += registers[source_reg]; }

    void print(uint8_t reg_num) { std::cout << (int)registers[reg_num]; } 
    //                                          ^^^
    // trzeba rzutowac na int bo uint8_t to unsigned char
};


enum ISA {
    MOV   = 0x01,
    ADD   = 0x02,
    SUB   = 0x03,
    LOAD  = 0x04,
    STORE = 0x05,
    JMP   = 0x06,
    CMP   = 0x07,
    JZ    = 0x08,
    HALT  = 0xFF
};


int main(void){
    /*MOV r0, 10
    MOV r1, 20
    ADD r0, r1
    HALT */
    CPU cpu;

    cpu.memory[0] = MOV;
    cpu.memory[1] = 0;
    cpu.memory[2] = 10;

    cpu.memory[3] = MOV;
    cpu.memory[4] = 1;
    cpu.memory[5] = 20;

    cpu.memory[6] = ADD;
    cpu.memory[7] = 0;
    cpu.memory[8] = 1;

    cpu.memory[9] = HALT;

    while(!cpu.halt){
        cpu.step();
    }

    cpu.print(0);
    std::cout << "\n";

    return 0;
}
