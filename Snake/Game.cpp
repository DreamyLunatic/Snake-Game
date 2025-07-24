#include "Game.h"

Game::Game()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake the game");

    SetTargetFPS(FPS);
}

void Game::Start()
{
    UpdateSize();

    while (!WindowShouldClose()) {
        if (IsWindowResized()) UpdateSize();  // If any changes in window size happends -> positions are controlled 

        BeginDrawing();
        ClearBackground(SCENE_COLOR);        

        if (isGameStarted) DrawGame();
        else DrawMenu();

        EndDrawing();
    }

    CloseWindow();
    return;
}

void Game::UpdateSize()
{
    scale.x = (float)GetScreenWidth() / (float)SCREEN_WIDTH;
    scale.y = (float)GetScreenHeight() <= 1 ? 10 : (float)GetScreenHeight() / (float)SCREEN_HEIGHT; // Prevent problems when height < 1

    gridBorders = { GRID_BORDERS.x * scale.x, GRID_BORDERS.y * scale.y, GRID_BORDERS.width * scale.x, GRID_BORDERS.height * scale.y };

    if (isGameStarted)
    {
        grid = std::make_unique<Grid>(gridBorders, *level);

        scoreText = "Score: " + std::to_string(snake->GetScore());
        score = std::make_unique<TextAttributes>(scoreText.c_str(), Rectangle({ SCORE_BORDERS.x * scale.x, SCORE_BORDERS.y * scale.y, SCORE_BORDERS.width * scale.x, SCORE_BORDERS.height * scale.y }), GetFontDefault(), 3);
    }

    startButton = std::make_unique<RoundedButton<>>(
        Rectangle{ START_BUTTON_BORDERS.x * scale.x, START_BUTTON_BORDERS.y * scale.y, START_BUTTON_BORDERS.width * scale.x, START_BUTTON_BORDERS.height * scale.y },
        std::bind(&Game::OnStartButtonClick, this), "Start", GetFontDefault(), START_BUTTON_COLORS);
    restartButton = std::make_unique<RegularButton<>>(Rectangle{ RESTART_BUTTON_BORDERS.x * scale.x, RESTART_BUTTON_BORDERS.y * scale.y, RESTART_BUTTON_BORDERS.width * scale.x, RESTART_BUTTON_BORDERS.height * scale.y },
        std::bind(&Game::RestartGame, this), "Restart", GetFontDefault(), START_BUTTON_COLORS);
    difficultyButton = std::make_unique<RoundedButton<>>(Rectangle{ START_BUTTON_BORDERS.x * scale.x, (START_BUTTON_BORDERS.y + 200) * scale.y, START_BUTTON_BORDERS.width * scale.x, START_BUTTON_BORDERS.height * scale.y },
        std::bind(&Game::OnDifficultyButtonClick, this), Difficulties::getInstance().getLevel(0).name, GetFontDefault(), START_BUTTON_COLORS);
    mainMenuButton = std::make_unique<RegularButton<>>(Rectangle{ START_BUTTON_BORDERS.x * scale.x, START_BUTTON_BORDERS.y * scale.y, START_BUTTON_BORDERS.width * scale.x, START_BUTTON_BORDERS.height * scale.y },
        std::bind(&Game::OnMainMenuButtonClick, this), "Main menu", GetFontDefault(), START_BUTTON_COLORS);
}

void Game::RestartGame()
{
    isGameOver = false;
    isPlayerReady = false;

    CreateGame();
    return;
}

void Game::CreateGame()
{
    level = std::make_unique<Level>(Difficulties::getInstance().getLevel(difficultySelected));
    grid = std::make_unique<Grid>(
        Rectangle{ GRID_BORDERS.x * scale.x, GRID_BORDERS.y * scale.y, GRID_BORDERS.width * scale.x, GRID_BORDERS.height * scale.y }, *level);
    snake = std::make_unique<Snake>(*level, isGameOver);
    food = std::make_unique<Food>(*level, isVictory);

    scoreText = "Score: " + std::to_string(snake->GetScore());
    score = std::make_unique<TextAttributes>(scoreText.c_str(), Rectangle({ SCORE_BORDERS.x * scale.x, SCORE_BORDERS.y * scale.y, SCORE_BORDERS.width * scale.x, SCORE_BORDERS.height * scale.y }), GetFontDefault(), 3);

    return;
}

void Game::DrawVictory()
{
    DrawText("VICTORY", 200, 200, 20, GREEN);
    mainMenuButton->Draw();

    return;
}

void Game::DrawMenu()
{
    startButton->Draw();
    difficultyButton->Draw();
}

void Game::DrawGame()
{
    DrawRectangleLines((int)gridBorders.x, (int)gridBorders.y, (int)gridBorders.width, (int)gridBorders.height, CELL_COLOR);
    grid->DrawGrid();

    if (isPlayerReady)
    {
        if (isGameOver)
        {
            restartButton->Draw();
            mainMenuButton->Draw();
        }
        if (isVictory) DrawVictory();
        else
        {
            food->Process();
            snake->Process();

            scoreText = "Score: " + std::to_string(snake->GetScore());
            score = std::make_unique<TextAttributes>(scoreText.c_str(), Rectangle({ SCORE_BORDERS.x * scale.x, SCORE_BORDERS.y * scale.y, SCORE_BORDERS.width * scale.x, SCORE_BORDERS.height * scale.y }), GetFontDefault(), 3);
            DrawText(score->pText, score->position.x, score->position.y, score->fontSize, GREEN);
        }
    }
    else
    {
        DrawText("Press any button to start", SCREEN_WIDTH / 2 * scale.x, SCREEN_HEIGHT / 2 * scale.y, 20 * (scale.x + scale.y) / 2, ColorManager::BWInvert(SCENE_COLOR));
        
        if (GetKeyPressed()) isPlayerReady = true;
    }
}

void Game::OnDifficultyButtonClick()
{
    difficultySelected++;
    if (difficultySelected >= 3) difficultySelected = 0;
    level = std::make_unique<Level>(Difficulties::getInstance().getLevel(difficultySelected));

    difficultyButton->ChangeText(level->name);
    return;
}

void Game::OnMainMenuButtonClick()
{
    isGameOver = false;
    isVictory = false;
    isGameStarted = false;
    isPlayerReady = false;

    return;
}

void Game::OnStartButtonClick()
{
    isGameStarted = true;
    CreateGame();
    grid->GridPrint();

    restartButton = std::make_unique<RegularButton<>>(Rectangle{ RESTART_BUTTON_BORDERS.x * scale.x, RESTART_BUTTON_BORDERS.y * scale.y, RESTART_BUTTON_BORDERS.width * scale.x, RESTART_BUTTON_BORDERS.height * scale.y },
        std::bind(&Game::RestartGame, this), "Restart", GetFontDefault(), START_BUTTON_COLORS);

    std::cout << "Hello Button" << std::endl;
    return;
}