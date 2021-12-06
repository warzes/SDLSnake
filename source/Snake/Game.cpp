#include "Image.h"
#include "GameData.h"

Image floorImage;
Image wallImage;
Image appleImage;
Image snakeHeadImage;
Image snakeBodyImage;
Image failScreen;

bool quit = false;
bool LoseGame = false;
bool stopMove = true;
Position direction;
float timer = 0;
float delayMove = 0.25f;
float speedMod = 0.03f;

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
	Fruit.NextPos();
}

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

			// Collision Check
			if (Map[Snake.pos.x][Snake.pos.y] == TileType::wall) // fail
			{
				LoseGame = true;
			}
			if (Fruit.pos.x == Snake.pos.x && Fruit.pos.y == Snake.pos.y)
			{
				Snake.AddSegment();
				Fruit.NextPos();
				delayMove -= speedMod;
				if (delayMove < 0.1f) // ускоряем игру
					delayMove = 0.1f;
			}
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
	Snake.Close();

	floorImage.Close();
	wallImage.Close();
	appleImage.Close();
	snakeHeadImage.Close();
	snakeBodyImage.Close();
	failScreen.Close();
}