#include "Image.h"

#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )
#pragma comment( lib, "SDL2_image.lib" )

constexpr int ScreenWidth = 1024;
constexpr int ScreentHeight = 768;

extern bool quit;
void GameInit(SDL_Renderer* renderer);
void GameUpdate(double deltaTime, const Uint8* currentKeyStates);
void GameRender(SDL_Renderer* renderer);
void GameClose();

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	// Main Init
	//----------------------------------------------------------------------------
	srand(time(0));
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreentHeight, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Game Init
	//----------------------------------------------------------------------------
	GameInit(renderer);

	// Main Loop
	//----------------------------------------------------------------------------
	SDL_Event e;
	int64_t frameTimeCurrent = 0;
	int64_t frameTimeLast = 0;
	int64_t frameTimeDelta = 0;
	std::chrono::high_resolution_clock clock;
	auto startTime = clock.now();
	static constexpr double MicrosecondsToSeconds = 1.0 / 1000000.0;
	while (!quit)
	{
		frameTimeCurrent = std::chrono::duration_cast<std::chrono::microseconds>(clock.now() - startTime).count();
		frameTimeDelta = frameTimeCurrent - frameTimeLast;
		frameTimeLast = frameTimeCurrent;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
		const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

		const double variableDeltaTimeSeconds = static_cast<double>(frameTimeDelta) * MicrosecondsToSeconds;
		GameUpdate(variableDeltaTimeSeconds, currentKeyStates);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		GameRender(renderer);
		SDL_RenderPresent(renderer);
	}

	// End
	//----------------------------------------------------------------------------
	GameClose();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}