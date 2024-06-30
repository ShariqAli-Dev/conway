#include "raylib.h"

static const unsigned int screenWidth = 800;
static const unsigned int screenHeight = 600;
static const unsigned int cellSize = 40;
static const unsigned int gridWidth = screenWidth / cellSize;
static const unsigned int gridHeight = screenHeight / cellSize;
static bool gridState[gridWidth][gridHeight] = {false};

static void UpdateDraw(void);
static void DrawGame(void);
static void DrawGrid(void);
static void UpdateGame(void);

int main()
{
    InitWindow(screenWidth, screenHeight, "Conway's Game of Life");
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        UpdateDraw();
    }

    CloseWindow();
    return 0;
}

void UpdateGame(void)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePosition = GetMousePosition();
        int xCell = (int)(mousePosition.x / cellSize);
        int yCell = (int)(mousePosition.y / cellSize);
        gridState[xCell][yCell] = !gridState[xCell][yCell];
    }
}

void DrawGrid(void)
{
    for (int x = 0; x < screenWidth; x += cellSize)
    {
        for (int y = 0; y < screenHeight; y += cellSize)
        {
            int xCell = x / cellSize;
            int yCell = y / cellSize;

            if (gridState[xCell][yCell])
            {
                DrawRectangle(x, y, cellSize, cellSize, BLACK);
            }
            else
            {

                DrawRectangleLines(x, y, cellSize, cellSize, LIGHTGRAY);
            }
        }
    }
};

void DrawGame(void)
{

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawGrid();
    DrawFPS(GetScreenWidth() - 95, 10);
    EndDrawing();
}

void UpdateDraw(void)
{
    UpdateGame();
    DrawGame();
}
