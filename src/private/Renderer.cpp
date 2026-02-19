#include <Renderer.h>
#include <SDL_render.h>
#include <Color.h>
#include <Vector2Int.h>
#include <SDL_rect.h>
#include <SDL_image.h>
#include <string>
#include <Texture.h>
#include <Rect.h>

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

void Renderer::DrawRect(Rect rect, Color color)
{
    SetDrawColor(color);
    SDL_Rect sdlRect = RectToSdl(rect);
    SDL_RenderFillRect(sdlRenderer, &sdlRect);
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

Texture Renderer::LoadTexture(const std::string& path)
{
    SDL_Texture* texture = IMG_LoadTexture(sdlRenderer, path.c_str());
    return Texture(texture);
}

void Renderer::DrawTexture(Texture& texture, Rect source, Rect destination)
{
    SDL_Rect sourceRect = RectToSdl(source);
    SDL_Rect destinationRect = RectToSdl(destination);
    SDL_RenderCopy(sdlRenderer, texture.GetSdlTexture(), &sourceRect, &destinationRect);
}

SDL_Rect Renderer::RectToSdl(const Rect& rect)
{
    return { rect.point.x, rect.point.y, rect.size.x, rect.size.y };
}