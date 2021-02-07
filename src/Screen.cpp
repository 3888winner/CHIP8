#include "Screen.hpp"
#include "SDL.h"
#include <iostream>

Screen::Screen(int w, int h, SDL_Color bg, SDL_Color fg)
{
    width = w;
    height = h;
    background = bg;
    foreground = fg;
    quit = false;
}

Screen::~Screen()
{

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
}

/**
 *  @brief Initialize SDL2 screen and sound settings
*/
void Screen::InitializeScreen()
{

    window = NULL;
    renderer = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << std::endl
                  << SDL_GetError();
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        // Create window
        window = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            std::cout << "Window could not be created! SDL_Error:" << std::endl
                      << SDL_GetError();
        }
        else
        {
            // Create window renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: " << std::endl
                          << SDL_GetError();
            }

            SDL_RenderSetScale(renderer, 10, 10);
            SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
            SDL_RenderClear(renderer);

            SDL_RenderPresent(renderer);

            SDL_Init(SDL_INIT_AUDIO);
            SDL_LoadWAV("src\\beep.wav", &wavSpec, &wavBuffer, &wavLength);
            SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
        }
    }
}

void Screen::Sound(){
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}

/**
*   @brief Update renderers to display new screen
*   @param reg A 2D 64*32 array 
*/
void Screen::DrawScreen(unsigned char reg[64][32])
{
    
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 32; y++)
        {
            if (reg[x][y] == 1)
            {
                SDL_SetRenderDrawColor(renderer, foreground.r, foreground.g, foreground.b, foreground.a);
                SDL_RenderDrawPoint(renderer, x, y);
            }
            else{
                SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    SDL_RenderPresent(renderer);
}


int Screen::key_press(unsigned char *key)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
    {
        quit = true;
    }

    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            quit = true;
        }
        else
        {
            for (int i = 0; i < 16; i++)
            {
                if (event.key.keysym.sym == keymap[i])
                {
                    key[i] = 1;
                    return i;
                }
            }
        }
    }

    if (event.type == SDL_KEYUP)
    {
        for (int i = 0; i < 16; i++)
        {
            if (event.key.keysym.sym == keymap[i])
            {
                key[i] = 0;
                return i;
            }
        }
    }
    return -1;
}
