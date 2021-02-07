#pragma once

#include "SDL.h"

class Screen
{
    public:
        Screen(int w, int h, SDL_Color bg, SDL_Color fg);
        ~Screen();

    private:
        int width;
        int height;
        SDL_Color foreground;
        SDL_Color background;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_AudioSpec wavSpec;
        SDL_AudioDeviceID deviceId;
        Uint32 wavLength;
        Uint8 *wavBuffer;

    public:
        bool quit;

    public:
        void InitializeScreen();
        void DrawScreen(unsigned char reg[64][32]);
        int key_press(unsigned char *key);
        void Sound();

    private:
        unsigned char keymap[16] = {
            SDLK_1,
            SDLK_2,
            SDLK_3,
            SDLK_4,
            SDLK_q,
            SDLK_w,
            SDLK_e,
            SDLK_r,
            SDLK_a,
            SDLK_s,
            SDLK_d,
            SDLK_f,
            SDLK_z,
            SDLK_x,
            SDLK_c,
            SDLK_v,
        };
};