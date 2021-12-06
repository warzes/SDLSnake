#pragma once

constexpr auto MapWidth = 32;
constexpr auto MapHeight = 24;
constexpr auto TileImageSize = 32;

enum class TileType
{
	floor,
	wall
};

TileType Map[MapWidth][MapHeight];

struct Position
{
	int x = 0;
	int y = 0;
};

struct FruitData
{
	Position pos;
} Fruit;

struct SnakeSegment
{
	void Render(SDL_Renderer* renderer, Image& snakeHeadImage, Image& snakeBodyImage)
	{
		snakeHeadImage.Render(renderer, pos.x * TileImageSize, pos.y * TileImageSize);
		renderSegment(renderer, snakeBodyImage);
	}

	Position pos = { MapWidth /2, MapHeight /2};
	SnakeSegment* next = nullptr;

private:
	void renderSegment(SDL_Renderer* renderer, Image& snakeBodyImage)
	{
		if (next)
		{
			snakeBodyImage.Render(renderer, next->pos.x * TileImageSize, next->pos.y * TileImageSize);
			renderSegment(renderer, snakeBodyImage);
		}
	}
};

SnakeSegment Snake;