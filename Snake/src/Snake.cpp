#include "Snake.h"

Snake::Snake(Level& level, bool& isGameOver) : level(level), isGameOver(isGameOver)
{
	int centreX = level.cols / 2;
	int centreY = level.rows / 2;

	int snakePos = 0;

	if (centreX > 1 && centreY > 1)
	{
		snakePos = centreX + 1;
	}
	else
	{
		isGameOver = true;

		return;
	}

	for (int i = (snakePos > 3 ? 3 : snakePos == 3 ? 2 : snakePos == 2 ? 1 : 0); i > 0; i--) snake.emplace_back(Vector2{ (float)snakePos - i, (float)centreY });
	

	headDirection = Direction::RIGHT;

	Place();
}

void Snake::Process()
{
	if (isGameOver == true) return;

	speedDelta = (float)(snake.size() / 5) * 0.005;
	snakeSpeed += (GetMouseWheelMove() * 0.05);

	if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && headDirection != Direction::DOWN && headDirection != Direction::UP) {
		headDirection = Direction::UP;
		Move();
	}
	else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && headDirection != Direction::RIGHT && headDirection != Direction::LEFT) {
		headDirection = Direction::LEFT;
		Move();
	}
	else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && headDirection != Direction::UP && headDirection != Direction::DOWN) {
		headDirection = Direction::DOWN;
		Move();
	}
	else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && headDirection != Direction::LEFT && headDirection != Direction::RIGHT) {
		headDirection = Direction::RIGHT;
		Move();
	}

	if (snakeTimer >= (snakeSpeed - speedDelta))
	{
		Move();
		snakeTimer = 0;
	}

	snakeTimer += GetFrameTime();
}

void Snake::Move()
{
	Vector2 position = Vector2{ snake.back().x, snake.back().y };
	
	if (headDirection == Direction::DOWN) position.y++;
	else if (headDirection == Direction::UP) position.y--;
	else if (headDirection == Direction::RIGHT) position.x++;
	else if (headDirection == Direction::LEFT) position.x--;
	
	if (position.y < 0 || position.y >= level.rows || position.x < 0 || position.x >= level.cols)
	{
		GameOver();
		return;
	}
	
	auto cell = level.data[(int)position.y][(int)position.x];
	if (cell != CELL_FOOD)
	{
		if (cell != CELL_EMPTY && cell != CELL_SNAKE_TAIL)
		{
			GameOver();
			return;
		}
		DecreaseTail();
	}
		
	snake.emplace_back(position);
	Place();

	snakeTimer = 0;
	return;
}

void Snake::Place()
{
	if (snake.size() > 1) level.data[(int)snake[0].y][(int)snake[0].x] = CELL_SNAKE_TAIL;
	for (int i = 1; i < snake.size(); i++)
	{
		if (i != (snake.size() - 1)) level.data[(int)snake[i].y][(int)snake[i].x] = CELL_SNAKE;
		else level.data[(int)snake[i].y][(int)snake[i].x] = CELL_SNAKE_HEAD;
	}
}

void Snake::DecreaseTail()
{
	level.data[(int)snake.front().y][(int)snake.front().x] = CELL_EMPTY;
	snake.erase(snake.begin());
}

void Snake::GameOver()
{
	isGameOver = true;
	return;
}

