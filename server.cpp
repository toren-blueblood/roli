#include "SDL.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "holi";

    SDL_Window *window;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Delay(5000);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
