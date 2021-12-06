#include "Image.h"
#include "GameData.h"

Image floorImage;
Image wallImage;
Image appleImage;
Image snakeHeadImage;
Image snakeBodyImage;
Image failScreen;

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
	failScreen.Create(renderer, "../lose.png");

	InitMap();
}
bool quit = false;
bool LoseGame = true;
bool stopMove = true;
Position direction;
float timer = 0;
float delayMove = 0.25f;
float speedMod = 0.01f;
void GameUpdate(double deltaTime, const Uint8* currentKeyStates)
{
	timer += deltaTime;

	if (currentKeyStates[SDL_SCANCODE_ESCAPE])
	{
		quit = true;
		return;
	}

	if (LoseGame) return;

	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		stopMove = false;
		direction.x = 0;
		direction.y = -1;
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		stopMove = false;
		direction.x = 0;
		direction.y = 1;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		stopMove = false;
		direction.x = -1;
		direction.y = 0;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		stopMove = false;
		direction.x = 1;
		direction.y = 0;
	}

	if (timer > delayMove)
	{
		timer = 0;
		if (!stopMove)
		{
			Snake.Move(direction);
		}
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

	if (LoseGame)
	{
		failScreen.Render(renderer, 0, 0);
	}

}

void GameClose()
{
	floorImage.Close();
	wallImage.Close();
	appleImage.Close();
	snakeHeadImage.Close();
	snakeBodyImage.Close();
	failScreen.Close();
}