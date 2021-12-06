#include "Image.h"
#include "GameData.h"

Image fooTexture;

void GameInit(SDL_Renderer* renderer)
{
	fooTexture.Create(renderer, "../foo.png");
}

void GameUpdate(double deltaTime, const Uint8* currentKeyStates)
{
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
}

void GameRender(SDL_Renderer* renderer)
{
	fooTexture.Render(renderer, 240, 190);
}

void GameClose()
{
	fooTexture.Close();
}