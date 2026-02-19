#pragma once
#include <SDL_render.h>
#include <Vector2Int.h>

class Texture
{
private:
	SDL_Texture* sdlTexture = nullptr;
	Vector2Int size = Vector2Int::Zero();

public:
	Texture(SDL_Texture* sdlTexture);
	Texture(Texture&& other) noexcept;

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	~Texture();

	bool IsLoaded();
	SDL_Texture* GetSdlTexture();

	Vector2Int GetSize() const;
};