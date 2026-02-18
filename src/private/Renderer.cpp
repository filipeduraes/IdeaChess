#include <Renderer.h>
#include <SDL_render.h>
#include <Color.h>
#include <Vector2Int.h>
#include <SDL_rect.h>

Renderer::Renderer(SDL_Renderer* sdlRenderer)
    : sdlRenderer(sdlRenderer),
      clearColor(Colors::Black)
{
}

Renderer::Renderer(Renderer&& other) noexcept
{
    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(sdlRenderer);
}

void Renderer::Render()
{
    SDL_RenderPresent(sdlRenderer);
}

void Renderer::SetClearColor(Color newClearColor)
{
    clearColor = newClearColor;
}

void Renderer::Clear()
{
    SetDrawColor(clearColor);
    SDL_RenderClear(sdlRenderer);
}

void Renderer::DrawRect(Vector2Int point, Vector2Int size, Color color)
{
    SetDrawColor(color);
    SDL_Rect rect = { point.x, point.y, size.x, size.y };
    SDL_RenderFillRect(sdlRenderer, &rect);
}

void Renderer::SetDrawColor(Color color)
{
    if (hasDrawed && lastDrawColor == color)
    {
        return;
    }

    SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);
    lastDrawColor = color;

    hasDrawed = true;
}