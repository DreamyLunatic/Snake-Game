#include "Grid.h"

Grid::Grid(Rectangle rect, Level& level) 
	: level(level), NumCols(level.cols), NumRows(level.rows), TotalCells(NumCols* NumRows), CellSize(std::min((rect.height / level.rows), (rect.width / level.cols)))
{
	float width = level.cols * CellSize;
	float height = level.rows * CellSize;

	float x = rect.x + (rect.width - width) / 2 - CellSize;
	float y = rect.y + (rect.height - height) / 2;

	borders = Rectangle{ x, y, width, height };
	gridAppearSpeed = (float)(2.0f / ((float)level.cols * (float)level.rows));
}

void Grid::GridPrint()
{
	for (int i = 0; i < level.rows; i++)
	{
		for (int j = 0; j < level.cols; j++)
		{
			std::cout << "[" << level.data[i][j] << "]";
		}
		std::cout << std::endl;
	}
}

void Grid::DrawGrid()
{
	if (!isGridDrawed) DrawCells();

	for (int i = 0; i < cellsDrawn; i++)
	{
		auto& data = level.data[i / NumCols][(NumCols - 1) - (i % NumCols)];

		DrawRectangleRoundedLines({
			borders.x + borders.width - i % NumCols * CellSize,
			borders.y + i / NumCols * CellSize,
			(float)(CellSize*0.9), (float)(CellSize*0.9)
			}, 0.2f, 32, CELL_COLOR); // Cell

		if (data != CELL_EMPTY) DrawRectangleRounded({
			borders.x + borders.width - i % NumCols * CellSize + (float)(CellSize*0.9)/12,
			borders.y + i / NumCols * CellSize + (float)(CellSize*0.9) / 12,
			(float)(CellSize*0.9) - (float)(CellSize * 0.9) / 6, (float)(CellSize*0.9) - (float)(CellSize * 0.9) / 6
			}, 0.4f, 32, GetCellColor(data)); // Insides of cell 
	
	}
}

void Grid::DrawCells()
{
	if (isGridDrawed) return;

	if (gridTimer >= gridAppearSpeed)
	{
		for (int i = 0; i < (gridTimer / gridAppearSpeed); i++)
		{
			drawedY = cellsDrawn / NumCols;
			drawedX = cellsDrawn - drawedY * NumCols;

			DrawRectangleLinesEx({ borders.x + borders.width - (drawedX)*CellSize, borders.y + drawedY * CellSize, (float)CellSize, (float)CellSize },
				3, CELL_COLOR);

			cellsDrawn++;
			if (TotalCells <= cellsDrawn) {
				isGridDrawed = true;
				return;
			}
		}

		gridTimer = 0;
	}
	gridTimer += GetFrameTime();

}

Color Grid::GetCellColor(int cell)
{
	return (cell == CELL_FOOD ? FOOD_COLOR :
		cell == CELL_WALL ? WALL_COLOR :
		cell == CELL_SNAKE ? SNAKE_COLOR : 
		cell == CELL_SNAKE_TAIL ? SNAKE_TAIL_COLOR : SNAKE_HEAD_COLOR);
}
