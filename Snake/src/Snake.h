#include <raylib.h>
#include <deque>
#include <iostream>
#include "Colors.h"
#include "difficulties.h"

#pragma once

class Direction { 
public: 
    enum class Value { UP, DOWN, LEFT, RIGHT }; 

    static const Value UP = Value::UP;
    static const Value DOWN = Value::DOWN;
    static const Value LEFT = Value::LEFT;
    static const Value RIGHT = Value::RIGHT;
};

class Snake
{
public:
    Snake(Level& level, bool& isGameOver);

    void Process();

    int GetScore() { return snake.size(); }
private:
    Level& level;
    bool& isGameOver;

    std::deque<Vector2> snake;

    float snakeSpeed = { 0.4f };
    float snakeTimer = { 0.0f };

    float speedDelta = 0.0f;

    Direction::Value headDirection = Direction::RIGHT;

    void Move();

    void Place();
    void DecreaseTail();

    void GameOver();
};
