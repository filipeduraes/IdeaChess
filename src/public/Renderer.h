#pragma once
#include <Color.h>
#include <Vector2Int.h>
#include <SDL_render.h>

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
    void DrawRect(Vector2Int point, Vector2Int size, Color color);

private:
    void SetDrawColor(Color color);
};