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
		renderSegment(renderer, snakeBodyImage, next);
	}

	void Move(Position dir)
	{
		Position temp = pos;
		pos.x += dir.x;
		pos.y += dir.y;
		if (pos.x < 0) pos.x = MapWidth - 1;
		if (pos.y < 0) pos.y = MapHeight - 1;
		if (pos.x >= MapWidth) pos.x = 0;
		if (pos.y >= MapHeight) pos.y = 0;

		moveSegment(temp, next);
	}

	Position pos = { MapWidth /2, MapHeight /2};
	SnakeSegment* next = nullptr;

private:
	void renderSegment(SDL_Renderer* renderer, Image& snakeBodyImage, SnakeSegment* nextSegment)
	{
		if (nextSegment)
		{
			snakeBodyImage.Render(renderer, nextSegment->pos.x * TileImageSize, nextSegment->pos.y * TileImageSize);
			renderSegment(renderer, snakeBodyImage, nextSegment->next);
		}
	}

	void moveSegment(Position newPos, SnakeSegment* nextSegment)
	{
		if (nextSegment)
		{
			Position temp = nextSegment->pos;
			nextSegment->pos = newPos;
			moveSegment(temp, nextSegment->next);
		}
	}
};

SnakeSegment Snake;