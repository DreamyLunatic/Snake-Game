#include <raylib.h>
#include <malloc.h>
#include "difficulties.h"
#include "InitValues.hpp"
#include "Colors.h"

#pragma once


class Grid {
public:
	Grid(Rectangle rect, Level& level);

	void GridPrint();

	void DrawGrid();
	void DrawCells();

	bool GetGridDrawnState() const { return isGridDrawed; }

private:
	const int NumRows;
	const int NumCols;
	const int TotalCells;
	const int CellSize;

	Level& level;
	Rectangle borders;

	int cellsDrawn = 0;

	float gridAppearSpeed = std::numeric_limits<float>::quiet_NaN();
	float gridTimer = { 0.0f };

	bool isGridDrawed = false;
	int drawedX = 0, drawedY = 0;

	Color GetCellColor(int cell);
};
