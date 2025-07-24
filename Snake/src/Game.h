#include <string>
#include "Colors.h"
#include "Grid.h"
#include "Snake.h"
#include "Button.h"
#include "Food.h"
#include "InitValues.hpp"

#pragma once

class Game
{
public:
    Game();

    void Start();

private:
    std::unique_ptr<Grid> grid;
    std::unique_ptr<Level> level;
    std::unique_ptr<Snake> snake;
    std::unique_ptr<Food> food;
    std::unique_ptr<RoundedButton<>> startButton;
    std::unique_ptr<RegularButton<>> restartButton;
    std::unique_ptr<RoundedButton<>> difficultyButton;
    std::unique_ptr<RegularButton<>> mainMenuButton;

    std::unique_ptr <TextAttributes> score;

    std::string scoreText;

    Vector2 scale = { 1, 1 };
    Rectangle gridBorders = { GRID_BORDERS.x, GRID_BORDERS.y, GRID_BORDERS.width, GRID_BORDERS.height };

    int difficultySelected = 0;

    bool isGameStarted = false;
    bool isGameOver = false;
    bool isPlayerReady = false;
    bool isVictory = false;

    void UpdateSize();

    void OnStartButtonClick();
    void OnDifficultyButtonClick();
    void OnMainMenuButtonClick();
    void RestartGame();

    void CreateGame();

    void DrawMenu();
    void DrawGame();
    void DrawVictory();
};