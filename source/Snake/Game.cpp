#include "Image.h"
#include "GameData.h"

Image floorImage;
Image wallImage;
Image appleImage;
Image snakeHeadImage;
Image snakeBodyImage;

void InitMap()
{
	for (size_t x = 0; x < MapWidth; x++)
	{
		for (size_t y = 0; y < MapHeight; y++)
		{
			int r = rand() % 200;
			if (r < 3)
				Map[x][y] = TileType::wall;
			else
				Map[x][y] = TileType::floor;
		}
	}

	while (1) // €блоко на свободной клетке
	{
		Fruit.pos.x = rand() % (MapWidth - 2) + 1;
		Fruit.pos.y = rand() % (MapHeight - 2) + 1;

		if (Map[Fruit.pos.x][Fruit.pos.y] == TileType::floor)
			break;
	}
	
}

void GameInit(SDL_Renderer* renderer)
{
	floorImage.Create(renderer, "../floor.png");
	wallImage.Create(renderer, "../wall.png");
	appleImage.Create(renderer, "../apple.png");
	snakeHeadImage.Create(renderer, "../snakeHead.png");
	snakeBodyImage.Create(renderer, "../snakeBody.png");

	InitMap();
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
	for (size_t x = 0; x < MapWidth; x++)
	{
		for (size_t y = 0; y < MapHeight; y++)
		{
			if (Map[x][y] == TileType::wall)
				wallImage.Render(renderer, x * TileImageSize, y * TileImageSize);
			else
				floorImage.Render(renderer, x * TileImageSize, y * TileImageSize);
		}
	}

	appleImage.Render(renderer, Fruit.pos.x * TileImageSize, Fruit.pos.y * TileImageSize);

	Snake.Render(renderer, snakeHeadImage, snakeBodyImage);

}

void GameClose()
{
	floorImage.Close();
	wallImage.Close();
	appleImage.Close();
	snakeHeadImage.Close();
	snakeBodyImage.Close();
}