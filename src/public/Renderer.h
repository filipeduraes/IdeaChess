#pragma once
#include <Color.h>
#include <Vector2Int.h>
#include <SDL_render.h>
#include <Texture.h>
#include <string>
#include <Rect.h>
#include <SDL_rect.h>

class Renderer
{
private:
    SDL_Renderer* sdlRenderer;
    Color clearColor;
    Color lastDrawColor;
    bool hasDrawed = false;

public:
    Renderer(SDL_Renderer* sdlRenderer);
    Renderer(Renderer&& other) noexcept;
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void Render();
    void SetClearColor(Color newClearColor);
    void Clear();
    void DrawRect(Rect rect, Color color);

    Texture LoadTexture(const std::string& path);
    void DrawTexture(Texture& texture, Rect source, Rect destination);

private:
    void SetDrawColor(Color color);

    SDL_Rect RectToSdl(const Rect& rect);
};