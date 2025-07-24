#pragma once
#include <iostream>
#include <raylib.h>
#include "InitValues.hpp"

constexpr  Color SCENE_COLOR = { 32, 27, 68, 255 };
constexpr  Color CELL_COLOR = { 243, 253, 240, 255 };
constexpr  Color SNAKE_COLOR = { 229, 21, 117, 255 };
constexpr  Color SNAKE_TAIL_COLOR = { 229, 21, 117, 150 };
constexpr  Color SNAKE_HEAD_COLOR = { 239, 41, 157, 255 };
constexpr  Color WALL_COLOR = { 58, 155, 208, 255 };
constexpr  Color FOOD_COLOR = { 251, 6, 7, 255 };

struct ColorManager
{
	static Color MakeDarker(Color color)
	{
		return Color{ 
			(unsigned char)(color.r / 2), 
			(unsigned char)(color.g / 2), 
			(unsigned char)(color.b / 2), 
			color.a 
		};
	}

	static Color BWInvert(Color color)
	{
		return (float)((color.r + color.g + color.b) / 3) < 127.5f ? WHITE : BLACK;
	}
};