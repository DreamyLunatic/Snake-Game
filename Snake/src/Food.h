#include "difficulties.h"
#include "InitValues.hpp"
#include <random>

#pragma once


class Food
{
public:
	Food(Level& level, bool& isVictory);

	void Process();
private:
	Level& level;
	bool& isVictory;

	Vector2 food;
	std::vector<Vector2> emptyPositions;

	Vector2 GetRandomEmptyPosition();

	void Place();
};