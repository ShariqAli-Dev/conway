#include "raylib.h"

static const unsigned int screen_width = 800;
static const unsigned int screen_height = 600;
static const unsigned int cell_size = 25;
static const unsigned int grid_width = screen_width / cell_size;
static const unsigned int grid_height = screen_height / cell_size;
static bool grid_state[grid_width][grid_height] = {false};
static bool pause = false;

static void update_draw(void);
static void update_game(void);
static void draw_game(void);
static void draw_grid(void);

int main()
{
    InitWindow(screen_width, screen_height, "Conway's Game of Life");
    SetTargetFPS(5);

    while (!WindowShouldClose())
    {
        update_draw();
    }

    CloseWindow();
    return 0;
}

void draw_grid(void)
{
    for (int x_pixel = 0; x_pixel < screen_width; x_pixel += cell_size)
    {
        for (int y_pixel = 0; y_pixel < screen_height; y_pixel += cell_size)
        {
            int x_cord = x_pixel / cell_size;
            int y_cord = y_pixel / cell_size;
            bool is_grid_alive = grid_state[x_cord][y_cord];
            if (is_grid_alive)
            {
                DrawRectangle(x_pixel, y_pixel, cell_size, cell_size, BLACK);
            }
            else
            {
                DrawRectangleLines(x_pixel, y_pixel, cell_size, cell_size, LIGHTGRAY);
            }
        }
    }
}

void draw_game(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_grid();
    if (pause)
    {
        DrawText("[P] to unpause, click cell to edit", 10, 10, 30, GREEN);
    }
    else
    {
        DrawText("[P] to pause, pause to edit", 10, 10, 30, GREEN);
    }
    DrawFPS(GetScreenWidth() - 90, 10);
    EndDrawing();
}

void get_cell_neighbors(int x, int y, int *alive_neighbors, int *dead_neighbors)
{
    // create a 3x3 grid where I am the center, (0,0)
    for (int vir_x = -1; vir_x < 2; vir_x++)
    {
        for (int vir_y = -1; vir_y < 2; vir_y++)
        {
            if (vir_x == 0 && vir_y == 0)
                continue;

            int neighbor_x = vir_x + x;
            int neighbor_y = vir_y + y;

            bool is_x_in_boundry = neighbor_x >= 0 && neighbor_x < grid_width;
            bool is_y_in_boundry = neighbor_y >= 0 && neighbor_y < grid_height;
            if (!is_x_in_boundry || !is_y_in_boundry)
                continue;

            bool is_neighbor_alive = grid_state[neighbor_x][neighbor_y];
            if (is_neighbor_alive)
            {
                (*alive_neighbors)++;
            }
            else
            {
                (*dead_neighbors)++;
            }
        }
    }
}

void update_game(void)
{

    bool temp_grid_state[grid_width][grid_height] = {false};
    if (IsKeyPressed('P'))
    {
        pause = !pause;
        // virtualGrid to hold new state
        // bool temp_grid_state[grid_width][grid_height] = {false};
    }

    if (pause)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse_position = GetMousePosition();
            int x_cord = (int)(mouse_position.x / cell_size);
            int y_cord = (int)(mouse_position.y / cell_size);
            grid_state[x_cord][y_cord] = !grid_state[x_cord][y_cord];
        }
    }
    else
    {

        for (int x = 0; x < grid_width; x++)
        {
            for (int y = 0; y < grid_height; y++)
            {
                int alive_neighbors = 0;
                int dead_neighbors = 0;
                get_cell_neighbors(x, y, &alive_neighbors, &dead_neighbors);
                bool is_cell_alive = grid_state[x][y];
                if (is_cell_alive)
                {
                    if (alive_neighbors < 2 || alive_neighbors > 3)
                    {
                        temp_grid_state[x][y] = false;
                    }
                    else
                    {
                        temp_grid_state[x][y] = true;
                    }
                }
                else
                {
                    if (alive_neighbors == 3)
                        temp_grid_state[x][y] = true;
                }
            }
        }

        // set the grid_state to the temp grid state
        for (int x = 0; x < grid_width; x++)
        {
            for (int y = 0; y < grid_height; y++)
            {
                grid_state[x][y] = temp_grid_state[x][y];
            }
        }
    }
}

void update_draw(void)
{
    update_game();
    draw_game();
}