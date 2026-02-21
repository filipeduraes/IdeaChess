#include <Application.h>
#include <memory>
#include <Renderer.h>
#include <Vector2Int.h>
#include <Window.h>
#include <SDL_timer.h>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_video.h>
#include <SDL_image.h>
#include <Input.h>
#include <cstdint>

Application::~Application()
{
    SDL_Quit();
    IMG_Quit();
}

void Application::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG) != 0)
    {
        return;
    }

    window = std::make_unique<Window>(WindowTitle, Vector2Int(700, 700));
    renderer = std::make_unique<Renderer>(window->CreateRenderer());

    onInitializeRenderer.Invoke(window.get(), renderer.get());
}

void Application::Run()
{
    uint64_t previous = SDL_GetPerformanceCounter();
    uint64_t lag = 0;

    while (true)
    {
        uint64_t current = SDL_GetPerformanceCounter();
        uint64_t elapsed = current - previous;
        previous = current;
        lag += elapsed;

        PollInput();

        if (input.GetLastEvent() == EventType::Quit)
        {
            break;
        }

        while (lag / SDL_GetPerformanceFrequency() >= FIXED_UPDATE_MS) 
        {
            onUpdate.Invoke();
            lag -= FIXED_UPDATE_MS;
        }
        
        onRender.Invoke();
    }
}

void Application::PollInput()
{
    input.Cleanup();
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        input.PollInput(event);

        bool windowResized = event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED;

        if (windowResized)
        {
            window->UpdateSize();
        }
    }
}