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
    uint16_t sp {4095}; // stack pointer; lifo; liczona od konca
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
            case 0x01: { // mov
                uint8_t destination = fetch();
                uint8_t value = fetch();
                MOV(destination, value);
                break;
            }

            case 0x02: { // add
                uint8_t dest = fetch();
                uint8_t src = fetch();
                ADD(dest, src);
                break;
            }
            
            case 0x03: { // sub
                uint8_t dest = fetch();
                uint8_t src = fetch();
                SUB(dest, src);
                break;
            }

            case 0x06: { // jmp
                uint8_t destination_pc = fetch();
                JMP(destination_pc);
                break;
            }

            case 0x09: { // push
                uint16_t value = fetch();
                PUSH16(value);
                break;
            }

            case 0x10: { // call
                uint8_t value = fetch();
                PUSH(value);
                break;
            }

            case 0x11: { // ret
                uint8_t value = fetch();
                PUSH(value);
                break;
            }

            case 0xFF: { // halt
                HALT();
                break;
            }
        }
    }

    void HALT() { this->halt = true; }

    void MOV(uint8_t destination, int value) { registers[destination] = value; }
    // void MOV(uint8_t destination, uint8_t source_register) { registers[destination] = registers[source_register]; }


    // ALU 
    // void ADD(uint8_t destination_reg, uint8_t source_reg) { registers[destination_reg] += registers[source_reg]; }
    void ADD(uint8_t destination_reg, int value) { registers[destination_reg] += value; }
    // napisac jeszcze jednego ADD dla register+int np r1 + 12
    // void ADD(uint8_t destination_reg, uint8_t source_reg) { registers[destination_reg] += registers[source_reg]; }
    void SUB(uint8_t destination_reg, uint8_t source_reg) { registers[destination_reg] -= registers[source_reg]; }
    // void AND();
    // void OR();
    // void XOR();
    // void NOT();
    // void SHL();
    // void SHR();
    // void CMP();
    //      ^todo

    void JMP(uint8_t destination_pc) { this->pc = destination_pc; }
    void PUSH(uint16_t value) { memory[sp--] = value; }
    void PUSH16(uint16_t value) {
        memory[sp--] = value & 0xFF;
        memory[sp--] = value >> 8;
    }
    uint8_t POP() { return memory[++sp]; }
    uint16_t POP16() {
        uint16_t lower = memory[++sp]; 
        uint16_t upper = memory[++sp]; 
        return lower | (upper<< 8);
    }
    void CALL(uint16_t destination) {
        PUSH(this->pc);
        JMP(destination);
    }
    void RET() { JMP(POP()); }

    void print(uint8_t reg_num) { std::cout << (int)registers[reg_num] << std::endl; } 
    //                                          ^^^
    // trzeba rzutowac na int bo uint8_t to unsigned char


    // TODO: wpasc na bystrzejszy sposob organizacji kodu; np by moc przeciazac funkcje; zeby nie musiec pisac takich dlugich stwitchy dla kazdego z przypadkow
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
    PUSH  = 0x09,
    CALL  = 0x10,
    RET   = 0x11,
    HALT  = 0xFF
};


int main(void){
  /*MOV r0, 10
    MOV r1, 20
    ADD r0, r1
    HALT */
    CPU cpu;

    /* instruction list */
    cpu.memory[0] = MOV;
    cpu.memory[1] = 0;
    cpu.memory[2] = 10;

    cpu.memory[3] = ADD;
    cpu.memory[4] = 0;
    cpu.memory[5] = 2;

    cpu.memory[6] = JMP;
    cpu.memory[7] = 3;

    cpu.memory[9] = HALT;

    while(!cpu.halt){
        cpu.step();
        // std::cout << "active";
        cpu.print(0);
    }

    std::cout << "\n";

    return 0;
}
