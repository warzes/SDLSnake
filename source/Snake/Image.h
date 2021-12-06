#pragma once

#pragma warning(push, 0)
#pragma warning(disable:4365)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <chrono>
#pragma warning(pop)

class Image
{
public:
	void Create(SDL_Renderer* renderer, const char* filepath)
	{
		SDL_Surface* loadedSurface = IMG_Load(filepath);
		m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		m_width = loadedSurface->w;
		m_height = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
	}
	void Close()
	{
		SDL_DestroyTexture(m_texture);
	}

	void Render(SDL_Renderer* renderer, int x, int y)
	{
		SDL_Rect renderQuad = { x, y, m_width, m_height };
		SDL_RenderCopy(renderer, m_texture, nullptr, &renderQuad);
	}
private:
	SDL_Texture* m_texture = nullptr;
	int m_width = 0;
	int m_height = 0;
};