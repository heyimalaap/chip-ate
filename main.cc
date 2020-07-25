#include <iostream>

constexpr short display_width = 64;
constexpr short display_hight = 32;

class chip8 {
private:
    union {
        unsigned char Memory[0x1000] = {0};
        struct {
            unsigned char V[16];
            unsigned short I;
            unsigned char ST;
            unsigned char DT;
            unsigned short PC;
            unsigned short SP;
            unsigned short stack[16];
            unsigned char display[display_width][display_hight];
            unsigned char font[16][5];
        };
    };
public:
    chip8() {
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
};


int main() {
    return 0;
}

