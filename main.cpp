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
        void step();
        void MOV(std::size_t register_number, int value);
        void MOV(std::size_t register_number1, std::size_t register_number2);
        uint8_t fetch();
    


    uint16_t registers[8];
    
    uint16_t pc {};
    uint16_t sp {4095};
    
    uint8_t memory[4096];

    bool halted = {};
};

enum class Instruction: uint8_t {
    MOV = 0x01, 
    ADD = 0x02, 
    SUB = 0x03,
    PUSH = 0x04,
    HLT  = 0x05,
};

void CPU::MOV(std::size_t register_number, int value){
    registers[register_number] = value;
}


void CPU::MOV(std::size_t register_number_dst, std::size_t register_number_src){
    registers[register_number_dst] = registers[register_number_src];
}

uint8_t CPU::fetch() {
    return memory[pc++];
}

void CPU::step(){
    Instruction optcode = static_cast<Instruction>(fetch());

    switch (optcode){
        case Instruction::MOV: {
            auto reg = fetch();
            auto val = fetch();
            MOV(reg, val);
            break;
        }

        case Instruction::ADD: 
            // ...
            break;

        case Instruction::SUB: 
            // ...
            break;

        case Instruction::PUSH:
            //
            break;

        case Instruction::HLT:
            this->halted = 1;
            break;
    }
}

int main(void){
    CPU cpu;

    cpu.memory[0] = static_cast<uint8_t>(Instruction::MOV);
    cpu.memory[1] = 0;      // R0
    cpu.memory[2] = 10;     // wartość

    cpu.memory[3] = static_cast<uint8_t>(Instruction::MOV);
    cpu.memory[4] = 1;      // R1
    cpu.memory[5] = 20;

    cpu.memory[6] = static_cast<uint8_t>(Instruction::ADD);
    cpu.memory[7] = 0;      // R0
    cpu.memory[8] = 1;      // R1

    cpu.memory[9] = static_cast<uint8_t>(Instruction::HLT);

    while(!cpu.halted){
        cpu.step();
    }

    return 0;
}