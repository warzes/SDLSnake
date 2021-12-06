#pragma warning(push, 0)
#pragma warning(disable:4365)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <chrono>
#pragma warning(pop)

#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )
#pragma comment( lib, "SDL2_image.lib" )

constexpr int ScreenWidth = 1024;
constexpr int ScreentHeight = 768;

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

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	// Main Init
	//----------------------------------------------------------------------------
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreentHeight, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Game Init
	//----------------------------------------------------------------------------
	Image fooTexture;
	Image backgroundTexture;

	fooTexture.Create(renderer, "../foo.png");
	backgroundTexture.Create(renderer, "../background.png");

	// Main Loop
	//----------------------------------------------------------------------------
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}

		const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
		}
		else if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
		}
		else if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		backgroundTexture.Render(renderer, 0, 0);
		fooTexture.Render(renderer, 240, 190);

		SDL_RenderPresent(renderer);
	}

	// End
	//----------------------------------------------------------------------------
	backgroundTexture.Close();
	fooTexture.Close();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}