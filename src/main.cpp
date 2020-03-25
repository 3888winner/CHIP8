#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <chrono>
#include <thread>
#include "CPU.hpp"
#include "Screen.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
const SDL_Color COLOR_BG = {0x00, 0x00, 0x00, 0xFF};
const SDL_Color COLOR_FG = {0xFF, 0xFF, 0xFF, 0xFF};

int main(int argc, char *argv[])
{
    Screen screen = Screen(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BG, COLOR_FG);
    screen.InitializeScreen();

    CPU cpu = CPU();
    cpu.InitializeMemory();

    cpu.LoadGame("PONG");

    bool quit = false;

    while (!quit)
    {

        cpu.EmulateCycle();

        if (cpu.drawFlag)
        {
            screen.DrawScreen(cpu.gfx);
            cpu.drawFlag = 0;
        }

        if (cpu.soundFlag)
        {
            screen.Sound();
        }

        screen.key_press(cpu.key);
        quit = screen.quit;

        std::this_thread::sleep_for(std::chrono::microseconds(16667));
    }

    return 0;
}