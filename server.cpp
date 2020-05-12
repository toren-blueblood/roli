#include "SDL.h"
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = SDL_LoadBMP("../resources/holi.bmp");
    if (surface == nullptr){
        SDL_Log("SDL_LoadBMP Error: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr){
        SDL_Log("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect rect;
    SDL_GetClipRect(surface, &rect);
    SDL_FreeSurface(surface);

    SDL_Surface *surface_stick = SDL_LoadBMP("../resources/sti.bmp");
    if (surface_stick == nullptr){
        SDL_Log("SDL_LoadBMP Error: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture_stick = SDL_CreateTextureFromSurface(renderer, surface_stick);
    if (texture_stick == nullptr){
        SDL_Log("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect stick_rect;
    SDL_GetClipRect(surface_stick, &stick_rect);
    SDL_FreeSurface(surface_stick);
    stick_rect.x = 100;
    stick_rect.y = 100;

    SDL_Rect stick_state[4];
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j){
            stick_state[i+2*j].x = i * stick_rect.w / 2;
            stick_state[i+2*j].y = j * stick_rect.h / 2;;
            stick_state[i+2*j].w = stick_rect.w/2;
            stick_state[i+2*j].h = stick_rect.h/2;
        }
    }

    SDL_Event event;
    bool quit = false;
    int stick_state_index = 0;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_UP]) {
            stick_rect.y = (stick_rect.y - 10) % 500;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            stick_rect.y = (stick_rect.y + 10) % 500;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            stick_rect.x = (stick_rect.x - 10) % 700;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            stick_rect.x = (stick_rect.x + 10) % 700;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_RenderCopy(renderer, texture_stick, &stick_state[stick_state_index], &stick_rect);

        SDL_RenderPresent(renderer);
        stick_state_index = (stick_state_index + 1) % 4;
        SDL_Delay(80);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
