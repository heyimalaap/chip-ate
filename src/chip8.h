#ifndef CHIP_8_INCLUDE
#define CHIP_8_INCLUDE

#include <initializer_list>
#include <cstring>
#include <random>
#include <cstdio>
#include <fstream>
#include <SDL2/SDL.h>
#include <string>

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
            unsigned char font[16][5];
        };
    };
    unsigned char display[display_hight][display_width];
public:
    unsigned char keys[16];
    chip8();
    bool exec_instruction(unsigned short instr);
    bool load_rom(const char* rom_path);
    void step();
    void print_memory();
    void render(SDL_Renderer* renderer);
};

#endif
