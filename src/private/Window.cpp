#include <Window.h>

Window::Window(const std::string& title, Vector2Int size)
    : size(size)
{
    sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_SHOWN);
}

Window::Window(Window&& other) noexcept
{
    sdlWindow = other.sdlWindow;
    other.sdlWindow = nullptr;
    size = other.size;
}

Window::~Window()
{
    SDL_DestroyWindow(sdlWindow);
}

Vector2Int Window::GetSize() const
{
    return size;
}

Renderer Window::CreateRenderer() const
{
    SDL_Renderer* renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    return Renderer(renderer);
}