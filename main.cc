#include "raylib.h"
#include <stdio.h>

static const unsigned int screenWidth = 800;
static const unsigned int screenHeight = 600;
static const unsigned int cellSize = 50;
static const unsigned int gridWidth = screenWidth / cellSize;
static const unsigned int gridHeight = screenHeight / cellSize;
static bool gridState[gridWidth][gridHeight] = {false};
static bool pause = false;

static void UpdateDraw(void);
static void DrawGame(void);
static void DrawGrid(void);
static void UpdateGame(void);

int main()
{
    InitWindow(screenWidth, screenHeight, "Conway's Game of Life");
    SetTargetFPS(10);

    while (!WindowShouldClose())
    {
        UpdateDraw();
    }

    CloseWindow();
    return 0;
}

void CellGetAliveAndDeadNeighbors(int xCell, int yCell, int *aliveNeighbors, int *deadNeighbors)
{
    // create a virtual 3x3 grid, I am the center
    *aliveNeighbors = 0;
    *deadNeighbors = 0;

    for (int xCord = -1; xCord < 2; xCord++)
    {
        for (int yCord = -1; yCord < 2; yCord++)
        {
            // im at the center, continue
            if (xCord == 0 && yCord == 0)
                continue;

            int xCordNeighbor = xCord + xCell;
            int yCordNeighbor = yCord + yCell;

            bool neighborXInBoundry = xCordNeighbor >= 0 && xCordNeighbor < gridWidth;
            bool neighborYInBoundry = yCordNeighbor < gridHeight && yCordNeighbor >= 0;
            if (neighborXInBoundry && neighborYInBoundry)
            {
                if (gridState[xCordNeighbor][yCordNeighbor])
                {
                    (*aliveNeighbors)++;
                }
                else
                {
                    (*deadNeighbors)++;
                }
            }
        }
    }
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
    if (IsKeyPressed('P'))
    {
        pause = !pause;
    }
    if (!pause)
    {
        bool newGridState[gridWidth][gridHeight] = {false};
        // cell logic
        for (int x = 0; x < gridWidth; x += x++)
        {
            for (int y = 0; y < gridHeight; y++)
            {
                bool cellIsAlive = gridState[x][y];
                int aliveNeighbors = 0;
                int deadNeighbors = 0;
                CellGetAliveAndDeadNeighbors(x, y, &aliveNeighbors, &deadNeighbors);
                printf("aliveN: %d, deadN, %d\n", aliveNeighbors, deadNeighbors);
                if (cellIsAlive)
                {
                    if (aliveNeighbors < 2 || aliveNeighbors > 3)
                    {
                        newGridState[x][y] = false;
                    }
                    else
                    {
                        newGridState[x][y] = true;
                    }
                }
                else
                {
                    // neighbors == 3, live
                    if (aliveNeighbors == 3)
                        gridState[x][y] = true;
                }
            }
        }

        // make gridState = newGridState;
        for (int x = 0; x < gridWidth; x++)
        {
            for (int y = 0; y < gridHeight; y++)
            {
                gridState[x][y] = newGridState[x][y];
            }
        }
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
}

void DrawGame(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawGrid();

    if (pause)
    {
        DrawText("[P] to Unpause, go edit cells", 10, 10, 30, GREEN);
    }
    else
    {
        DrawText("[P] to Pause", 10, 10, 30, GREEN);
    }

    DrawFPS(GetScreenWidth() - 95, 10);
    EndDrawing();
}

void UpdateDraw(void)
{
    UpdateGame();
    DrawGame();
}
