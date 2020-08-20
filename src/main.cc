#include "chip8.h"
#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 320;

const int FPS = 60;
const int frameDelay = 1000/FPS;

const int keymap[16] = {
    SDLK_x,     // 0
    SDLK_1,     // 1
    SDLK_2,     // 2
    SDLK_3,     // 3
    SDLK_q,     // 4
    SDLK_w,     // 5
    SDLK_e,     // 6
    SDLK_a,     // 7
    SDLK_s,     // 8
    SDLK_d,     // 9
    SDLK_z,     // A
    SDLK_c,     // B
    SDLK_4,     // C
    SDLK_r,     // D
    SDLK_f,     // E
    SDLK_v      // F
};

int main() {
    /*
    chip8 cpu;
    cpu.load_rom("test.ch8");
    cpu.print_memory();
    while (1) {
        cpu.step();
        cpu.print_display();
    }*/

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    chip8 emu;
    emu.load_rom("test.ch8");

    if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
        window = SDL_CreateWindow("CHIP8 Emulator : ChipAte", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window != nullptr) {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                std::cerr << "Failed to create renderer. Error : " << SDL_GetError() << std::endl;
            } else {
                bool isRunning = true;
                Uint32 frameStart, frameDelta;
                frameStart = SDL_GetTicks();
                while(isRunning) {
                    while(SDL_PollEvent(&event) > 0) {
                        switch(event.type) {
                            case SDL_QUIT:
                                isRunning = false;
                                break;
                            case SDL_KEYDOWN:
                                for (int i = 0; i < 16; i++) {
                                    if (event.key.keysym.sym == keymap[i]) emu.keys[i] = 1;
                                }
                                break;
                            case SDL_KEYUP:
                                for (int i = 0; i < 16; i++) {
                                    if (event.key.keysym.sym == keymap[i]) emu.keys[i] = 0;
                                }
                                break;
                        }
                    }

                    //emu.step();
                    //emu.render(renderer);

                    frameDelta = SDL_GetTicks() - frameStart;
                    if (frameDelay <= frameDelta) {
                        emu.step();
                        frameStart = SDL_GetTicks();
                    }
                    emu.render(renderer);
                }

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
        } else {
            std::cerr << "Failed to create window. Error : " << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << "Failed to init SDL in video mode. Error : " << SDL_GetError() << std::endl;
    }

    return 0;
}

