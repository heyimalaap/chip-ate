#include "chip8.h"
#include <initializer_list>
#include <cstring>

chip8::chip8() {
    // Set all registers to 0
    memset(V, 0, sizeof(V));
    I = 0;
    ST = 0;
    DT = 0;

    // Set program counter to 0x200
    PC = 0x200;

    // Set stack pointer to 0
    SP = 0;

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
        case 0xE0: // 00E0 : Clear the display
            memset(display, 0, sizeof(display));
            break;
        case 0xEE: // 00EE : Return from subroutine
            if (SP == 0) return false; // Stack empty fail
            PC = stack[SP--];
            break;
        default:   // 0nnn : Insturction not suported
            return false;
        }
        break;
    case 0x1000:
        break;
    case 0x2000:
        break;
    case 0x3000:
        break;
    case 0x4000:
        break;
    case 0x5000:
        break;
    case 0x6000:
        break;
    case 0x7000:
        break;
    case 0x8000:
        break;
    case 0x9000:
        break;
    case 0xA000:
        break;
    case 0xB000:
        break;
    case 0xC000:
        break;
    case 0xD000:
        break;
    case 0xE000:
        break;
    case 0xF000:
        break;
    default:
        return false;
    }
    return true;
}
