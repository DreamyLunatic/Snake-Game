#include "Food.h"


Food::Food(Level& level, bool& isVictory) : level(level), isVictory(isVictory)
{
	food = GetRandomEmptyPosition();
	Place();
}

void Food::Process()
{
	if (level.data[food.y][food.x] != CELL_FOOD)
	{
		food = GetRandomEmptyPosition();
		Place();
	}
}

void Food::Place()
{
	if (food.y >= 0 && food.x >= 0) level.data[food.y][food.x] = CELL_FOOD;
}

Vector2 Food::GetRandomEmptyPosition()
{
	emptyPositions.clear();
	for (int i = 0; i < level.rows; i++)
	{
		for (int j = 0; j < level.cols; j++)
		{
			if (level.data[i][j] == CELL_EMPTY) emptyPositions.push_back(Vector2(j, i));
		}
	}

	if (emptyPositions.size() <= 0)
	{
		isVictory = true;
		return Vector2(-1, -1);
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distirb(0, emptyPositions.size() - 1);

	return emptyPositions[distirb(gen)];
}
