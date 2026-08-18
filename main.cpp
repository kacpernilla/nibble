#include <iostram>

/*
    8 registers
    r0, r1, r2, ...

    pc - program counter
    sp - stack pointer
    flags - flagi procesora

    ram: 4096 bytes
*/

class cpu {
    uint16_t registers[8];

    uint16_t pc;
    uint16_t sp;

    uint8_t memory[4096];
};

int main(void){
    std::cout << "Hello, world\n";
    return 0;
}