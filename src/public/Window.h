#pragma once
#include <Renderer.h>
#include <SDL_video.h>
#include <string>
#include <Vector2Int.h>

class Window
{
private:
    SDL_Window* sdlWindow;
    Vector2Int size;

public:
    Window(const std::string& title, const Vector2Int& size);
    Window(Window&& other) noexcept;

    ~Window();

    Window(const Window&) = delete;
    Window& operator =(const Window&) = delete;

    [[nodiscard]] Vector2Int GetSize() const;
    [[nodiscard]] Renderer CreateRenderer() const;
    [[nodiscard]] bool IsFocused() const;

    void UpdateSize();
};