#include <Texture.h>
#include <SDL_render.h>
#include <cstdint>
#include <Vector2Int.h>

Texture::Texture(SDL_Texture* sdlTexture)
	: sdlTexture(sdlTexture)
{
	if (IsLoaded()) 
	{
		int32_t width = 0;
		int32_t height = 0;
		uint32_t format = 0;
		int32_t access = 0;

		SDL_QueryTexture(sdlTexture, &format, &access, &width, &height);
		size = Vector2Int(width, height);
	}
}

Texture::Texture(Texture&& other) noexcept
	: size(other.size)
{
	sdlTexture = other.sdlTexture;
	other.sdlTexture = nullptr;
}

Texture::~Texture()
{
	if (IsLoaded()) 
	{
		SDL_DestroyTexture(sdlTexture);
	}
}

bool Texture::IsLoaded()
{
	return sdlTexture != nullptr;
}

SDL_Texture* Texture::GetSdlTexture()
{
	return sdlTexture;
}

Vector2Int Texture::GetSize() const
{
	return size;
}
