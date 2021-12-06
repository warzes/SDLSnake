#pragma once

constexpr auto MapWidth = 32;
constexpr auto MapHeight = 24;

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
		pos.x = rand() % (MapWidth - 2) + 1;
		pos.y = rand() % (MapHeight - 2) + 1;
	}

	Position pos;
} Fruit;

struct SnakeSegment
{
	Position pos;
	SnakeSegment* next = nullptr;
};

SnakeSegment Snake;