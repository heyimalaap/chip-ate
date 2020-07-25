#include "chip8.h"
#include <initializer_list>
chip8::chip8() {
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
