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
	void NextPos()
	{
		while (1) // яблоко на свободной клетке
		{
			Fruit.pos.x = rand() % (MapWidth - 2) + 1;
			Fruit.pos.y = rand() % (MapHeight - 2) + 1;

			if (Map[Fruit.pos.x][Fruit.pos.y] == TileType::floor)
				break;
		}
	}


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

	void Close()
	{
		closeSegment(next);
	}

	void AddSegment()
	{
		SnakeSegment* last = getLastSegment(this);
		last->next = new SnakeSegment;
		last->next->pos = last->pos;		
	}

	bool CheckCollisionInSegments()
	{
		return checkCollisionInSegments(pos, next);
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

	void closeSegment(SnakeSegment* nextSegment)
	{
		if (nextSegment)
		{
			nextSegment->Close();
			delete nextSegment;
			nextSegment = nullptr;
		}
	}

	SnakeSegment* getLastSegment(SnakeSegment* nextSegment)
	{
		if (!nextSegment->next)
			return nextSegment;
		else
			return getLastSegment(nextSegment->next);
	}

	bool checkCollisionInSegments(Position pos, SnakeSegment* nextSegment)
	{
		if (nextSegment)
		{
			if (pos.x == nextSegment->pos.x && pos.y == nextSegment->pos.y)
				return true;
			else
				return checkCollisionInSegments(pos, nextSegment->next);
		}
		return false;
	}
};

SnakeSegment Snake;