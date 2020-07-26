#include "chip8.h"
#include <initializer_list>
#include <cstring>
#include <random>

chip8::chip8() {
    // Set all registers to 0
    memset(V, 0, sizeof(V));
    I = 0;
    ST = 0;
    DT = 0;

    // Set program counter to 0x200
    PC = 0x200;

    // Set stack pointer to -1 (empty stack)
    SP = -1;

    // Load fonts
    int number = 0;
    for (unsigned f : {0xF999F, 0x72262, 0xF8F1F, 0xF1F1F,
                       0x11F99, 0xF1F8F, 0xF9F8F, 0x4421F,
                       0xF9F9F, 0xF1F9F, 0x99F9F, 0xE9E9E,
                       0xF888F, 0xE999E, 0xF8F8F, 0x88F8F}) {
        for (int i = 0; i < 5; i++)
            font[number][i] = ((f >> 4*i) & 0xF) << 4;
        number++;
    }
}

bool chip8::exec_instruction(unsigned short instr) {
    switch(instr & 0xF000) {
    case 0x0000:
        switch(instr & 0x00FF) {
        case 0xE0:      // 00E0 : Clear the display
            memset(display, 0, sizeof(display));
            PC += 2; 
            break;
        case 0xEE:      // 00EE : Return from subroutine
            if (SP == -1) {
                PC += 2; 
                return false; // Stack empty fail
            }
            PC = stack[SP--];
            PC += 2; // Next instruction
            break;
        default:        // 0nnn : Instruction not suported
            PC += 2; 
            return false;
        }
        break;
    case 0x1000:        // 1nnn : Jump to location nnn
        PC = instr & 0x0FFF;
        break;
    case 0x2000:        // 2nnn : Call subroutine at nnn
        stack[++SP] = PC;
        PC = instr & 0x0FFF;
        break;
    case 0x3000:        // 3xkk : Skip next instruction if V[x] == kk
        if (V[(instr & 0x0F00) >> 8] == (instr & 0xFF))
            PC += 4; // Skip next instruction
        else
            PC += 2; 
        break;
    case 0x4000:        // 4xkk : Skip next instruction if V[x] != kk
        if (V[(instr & 0x0F00) >> 8] != (instr & 0xFF))
            PC += 4; // Skip next instruction
        else
            PC += 2; 
        break;
    case 0x5000:        // 5xy0 : Skip next instruction if V[x] == V[y]
        switch (instr & 0xF) {
        case 0x0:   // 5xy0
            if (V[(instr & 0x0F00) >> 8] == V[(instr & 0x00F0) >> 4])
                PC += 4; // Skip next instruction
            else
                PC += 2; 
            break;
        default:
            PC += 2; 
            return false;
        }
        break;
    case 0x6000:        // 6xkk : Set V[x] = kk
        V[(instr & 0x0F00) >> 8] = (instr & 0xFF);
        PC += 2; 
        break;
    case 0x7000:        // 7xkk : Set V[x] = V[x] + kk
        V[(instr & 0x0F00) >> 8] += (instr & 0xFF);
        PC += 2; 
        break;
    case 0x8000:
        unsigned short x = (instr & 0x0F00) >> 8;
        unsigned short y = (instr & 0x00F0) >> 4;
        switch(instr & 0x000F) {
        case 0x0000:    // 8xy0 : V[x] = V[y]
            V[x] = V[y];
            PC += 2; 
            break;
        case 0x0001:    // 8xy1 : V[x] = V[x] | V[y]
            V[x] |= V[y];
            PC += 2;
            break;
        case 0x0002:    // 8xy2 : V[x] = V[x] & V[y]
            V[x] &= V[y];
            PC += 2; 
            break;
        case 0x0003:    // 8xy3 : V[x] = V[x] ^ V[y]
            V[x] ^= V[y];
            PC += 2; 
            break;
        case 0x0004:    // 8xy4 : V[x] = V[x] + v[y]; V[0xF] = carry flag
            int result = V[x] + V[y];
            V[x] = result;
            if (result > 255) V[0xF] = 1;
            else V[0xF] = 0;
            PC += 2; 
            break;
        case 0x0005:    // 8xy5 : V[x] = V[x] - V[y]; V[0xF] = not borrow
            V[x] = V[x] - V[y];
            if (V[x] > V[y]) V[0xF] = 1;
            else V[0xF] = 0;
            PC += 2;
            break;
        case 0x0006:    // 8xy6 : V[0xF] = V[x] & 0x1; V[x] >>= 1;
            V[0xF] = V[x] & 0x1;
            V[x] >>= 1;
            PC += 2;
            break;
        case 0x0007:    // 8xy7 : V[x] = V[y] - V[x]; V[0xF] = not borrow
            V[x] = V[y] - V[x];
            if (V[y] > V[x]) V[0xF] = 1;
            else V[0xF] = 0;
            PC += 2;
            break;
        case 0x000E:    // 8xyE : V[0xF] = (V[x] >> 7) & 0x1; V[x] <<= 1
            V[0xF] = (V[x] >> 7) & 0x1;
            V[x] <<= 1;
            PC += 2;
            break;
        default:
            PC += 2; 
            return false;
        }
        break;
    case 0x9000:
        switch(instr & 0xF) {
        case 0x0000:    // 9xy0 : Skip next instruction if V[x] != V[y]
            if (V[(instr & 0x0F00) >> 8] != V[(instr & 0x00F0) >> 4])
                PC += 4;
            else
                PC += 2;
            break;
        default:
            PC += 2;
            return false;
        }
        break;
    case 0xA000:        // Annn : Set I = nnn
        I = instr & 0x0FFF;
        PC += 2;
        break;
    case 0xB000:        // Bnnn : Jump to location nnn + V[0]
        PC = (instr & 0x0FFF) + V[0];
        break;
    case 0xC000:        // Cxkk : Set V[x] = (random byte) & kk
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<unsigned short> distribution(0, 255);
        unsigned char rand_byte = (unsigned char)distribution(generator);
        V[(instr & 0x0F00) >> 8] = rand_byte & (instr & 0xFF);
        PC += 2;
        break;
    case 0xD000:
        break;
    case 0xE000:
        break;
    case 0xF000:
        break;
    default:
        PC += 2; 
        return false;
    }
    return true;
}
