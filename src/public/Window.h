#pragma once
#include <string>
#include <Vector2Int.h>
#include <Renderer.h>
#include <SDL_video.h>

class Window
{
private:
    SDL_Window* sdlWindow;
    Vector2Int size;

public:
    Window(const std::string& title, Vector2Int size);
    Window(Window&& other) noexcept;

    ~Window();

    Window(const Window&) = delete;
    Window& operator =(const Window&) = delete;

    Vector2Int GetSize() const;
    Renderer CreateRenderer() const;

    bool IsFocused() const;

    void UpdateSize();
};