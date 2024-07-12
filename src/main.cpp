#include <iostream>
#include <SDL2/SDL.h>
#include "register_site.h"

class Window {
    SDL_Window* window;

    public:

    Window(const char* title) : window{SDL_CreateWindow(title, 0, 0, 800, 600, SDL_WINDOW_SHOWN)} {}
    ~Window() { SDL_DestroyWindow(window); }
};

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        std::cerr << "Failed to initalize SDL: " << SDL_GetError();
    else {
        Window window("Seaturtle Browser");
        SDL_Delay(5000);
    }

    register_site("good", "sea", "https://github.com/tathyagarg/tathyagarg");

    SDL_Quit();

    return 0;
}