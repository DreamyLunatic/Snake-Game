#include <unordered_map>
#include <iostream>
#include "InitValues.hpp"

#pragma once

struct Level {
	const char* name;

	size_t rows;
	size_t cols;

	std::vector<std::vector<int>> data; 
	
	Level() : name("Level"), rows(0), cols(0), data() {} // Default constructor 
	Level(size_t c, size_t r) : name("Level"), rows(r), cols(c), data(r, std::vector<int>(c)) {}
	Level(const char* name, std::vector<std::vector<int>> data) : name(name), rows(data.size()), cols(data[0].size()), data(data) {}
};

class Difficulties {
public: 
	static Difficulties& getInstance() {
		static Difficulties instance;
		return instance;
	}

	const Level& getLevel(int n) const {
		return levels.at(n);
	}

	Difficulties(const Difficulties&) = delete; // Prevent copy constructor 
	Difficulties& operator=(const Difficulties&) = delete; // Prevent assignment operator 
private:
	std::unordered_map<int, Level> levels;
	Difficulties() {
		std::vector<std::vector<int>> easy =
		{
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		};
		std::vector<std::vector<int>> medium =
		{
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		};

		std::vector<std::vector<int>> hard =
		{
			std::vector<int>					{ 0, 0, CELL_WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, CELL_WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, CELL_WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, CELL_WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, CELL_WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, CELL_WALL, 0, 0, 0, 0, 0, 0, CELL_WALL, 0, 0},
			std::vector<int>					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CELL_WALL, 0, 0},
		};

		levels[0] = Level("Easy", easy);
		levels[1] = Level("Medium", medium);
		levels[2] = Level("Hard", hard);
	}
};
