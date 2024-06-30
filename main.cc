#include "raylib.h"

static const unsigned int screenWidth = 800;
static const unsigned int screenHeight = 600;
static const unsigned int cellSize = 40;

static void DrawGrid(void);

int main()
{
    InitWindow(screenWidth, screenHeight, "Conway's Game of Life");
    SetTargetFPS(1);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawGrid();
        DrawFPS(GetScreenWidth() - 95, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawGrid(void)
{
    for (int x = 0; x < screenWidth; x += cellSize)
    {
        for (int y = 0; y < screenHeight; y += cellSize)
        {

            DrawRectangleLines(x, y, cellSize, cellSize, BLACK);
        }
    }
};