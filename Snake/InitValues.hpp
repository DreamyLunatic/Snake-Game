#include <raylib.h>
#include <iostream>
#include <array> 
#include <string_view> 

#pragma once

constexpr size_t SCREEN_WIDTH							= 800;
constexpr size_t SCREEN_HEIGHT							= 600;
constexpr size_t FPS									= 30;

constexpr Rectangle START_BUTTON_BORDERS				= { 300, 80, 200, 86 };
constexpr Rectangle RESTART_BUTTON_BORDERS				= { 300, 500, 200, 80 };
constexpr Rectangle GRID_BORDERS						= { 50, 80, 700, 500 };
constexpr Rectangle SCORE_BORDERS						= { 50, 10, 180, 60 };

constexpr std::pair<Color, Color> START_BUTTON_COLORS	= { YELLOW, BLUE };

const int CELL_EMPTY = 0;
const int CELL_WALL = 1;
const int CELL_FOOD = 2;
const int CELL_SNAKE = 3;
const int CELL_SNAKE_TAIL = 4;
const int CELL_SNAKE_HEAD = 5;