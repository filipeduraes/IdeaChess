#include <Window.h>
#include <SDL_mouse.h>
#include <string>
#include <Vector2Int.h>
#include <Renderer.h>
#include <SDL_video.h>
#include <cstdint>

Window::Window(const std::string& title, Vector2Int size)
    : size(size)
{
    sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

bool Window::IsFocused() const
{
    return SDL_GetMouseFocus() == sdlWindow;
}

void Window::UpdateSize()
{
    int32_t newWidth = 0;
    int32_t newHeight = 0;
    
    SDL_GetWindowSize(sdlWindow, &newWidth, &newHeight);
    size = Vector2Int(newWidth, newHeight);
}
