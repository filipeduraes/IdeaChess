#include <SDL.h>
#include <cstdlib>

namespace
{
    constexpr int WindowWidth = 800;
    constexpr int WindowHeight = 600;
    constexpr const char* WindowTitle = "SDL Window";
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow
    (
        WindowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WindowWidth,
        WindowHeight,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    bool isRunning = true;

    while (isRunning)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        SDL_Delay(1);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
