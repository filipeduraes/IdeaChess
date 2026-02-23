#pragma once
#include <Color.h>
#include <Rect.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <string>
#include <Texture.h>

class Renderer
{
private:
    SDL_Renderer* sdlRenderer;
    Color clearColor;
    Color lastDrawColor;
    bool hasDrawn = false;

public:
    explicit Renderer(SDL_Renderer* sdlRenderer);
    Renderer(Renderer&& other) noexcept;
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void Render() const;
    void SetClearColor(const Color& newClearColor);
    void Clear();
    void DrawRect(const Rect& rect, const Color& color);

    [[nodiscard]] Texture LoadTexture(const std::string& path) const;
    void DrawTexture(const Texture& texture, const Rect& source, const Rect& destination) const;

private:
    void SetDrawColor(const Color& color);

    static SDL_Rect RectToSdl(const Rect& rect);
};