#include <Color.h>
#include <Rect.h>
#include <Renderer.h>
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <string>
#include <Texture.h>
#include <Vector2Int.h>

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

void Renderer::Render() const
{
    SDL_RenderPresent(sdlRenderer);
}

void Renderer::SetClearColor(const Color& newClearColor)
{
    clearColor = newClearColor;
}

void Renderer::Clear()
{
    SetDrawColor(clearColor);
    SDL_RenderClear(sdlRenderer);
}

void Renderer::DrawRect(const Rect& rect, const Color& color)
{
    SetDrawColor(color);
    const SDL_Rect sdlRect = RectToSdl(rect);
    SDL_RenderFillRect(sdlRenderer, &sdlRect);
}

void Renderer::SetDrawColor(const Color& color)
{
    if (hasDrawn && lastDrawColor == color)
    {
        return;
    }

    SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);
    lastDrawColor = color;

    hasDrawn = true;
}

Texture Renderer::LoadTexture(const std::string& path) const
{
    SDL_Texture* texture = IMG_LoadTexture(sdlRenderer, path.c_str());
    return Texture(texture);
}

void Renderer::DrawTexture(const Texture& texture, const Rect& source, const Rect& destination) const
{
    const SDL_Rect sourceRect = RectToSdl(source);
    const SDL_Rect destinationRect = RectToSdl(destination);
    SDL_RenderCopy(sdlRenderer, texture.GetSdlTexture(), &sourceRect, &destinationRect);
}

SDL_Rect Renderer::RectToSdl(const Rect& rect)
{
    return { rect.point.x, rect.point.y, rect.size.x, rect.size.y };
}