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
                uint8_t first = fetch();
                uint8_t second = fetch();
                MOV(first, second);
                break;
            }
            
            case 0xFF: {
                HALT();
                break;
            }
        }
    }

    void HALT() { this->halt = true; }
    void MOV(std::size_t register_number, int value) { registers[register_number] = value; }
    void MOV(std::size_t register_number_dst, std::size_t register_number_src) { registers[register_number_dst] = registers[register_number_src]; }
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
    cpu.memory[2] = 20;
    cpu.memory[3] = HALT;

    while(!cpu.halt){
        cpu.step();
        std::cout << "active ";
    }

    std::cout << "\n";

    return 0;
}