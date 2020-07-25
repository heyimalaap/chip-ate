#include <iostream>

class chip8 {
private:
    const short display_width = 64;
    const short display_hight = 32;

    union {
        unsigned char Memory[0x1000];
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
        
    }
};


int main() {
    return 0;
}

