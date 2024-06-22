#include "raylib.h"

enum CellState { C_BLACK, C_BLUE, C_GREEN };

// Function to draw a 500x500 grid
void DrawGrid(int gridSize, int gridWidth, int gridHeight, CellState grid[50][50]) {
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {
            Color cellColor;
            switch (grid[x][y]) {
                case C_BLACK: cellColor = BLACK; break;
                case C_BLUE: cellColor = BLUE; break;
                case C_GREEN: cellColor = GREEN; break;
            }
            DrawRectangle(x * gridSize, y * gridSize, gridSize, gridSize, cellColor); // Fill
            DrawRectangleLines(x * gridSize, y * gridSize, gridSize, gridSize, DARKGRAY); // Border
        }
    }
}

// Function to clear the grid
void ClearGrid(CellState grid[50][50], int gridWidth, int gridHeight) {
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {
            grid[x][y] = C_BLACK;
        }
    }
}

// Function to remove any existing green square
void RemoveGreen(CellState grid[50][50], int gridWidth, int gridHeight) {
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {
            if (grid[x][y] == C_GREEN) {
                grid[x][y] = C_BLACK;
            }
        }
    }
}

int main() {
    // Initialize the window
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Dijkstra's Algorithm - Grid");

    // Grid settings
    const int gridSize = 15;
    const int gridWidth = 50;   // 500 / 15 = 33 cells
    const int gridHeight = 50;  // 500 / 15 = 33 cells

    // Grid state
    CellState grid[50][50] = { C_BLACK };

    // Set target FPS
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Handle mouse input
        Vector2 mousePos = GetMousePosition();
        int x = mousePos.x / gridSize;
        int y = mousePos.y / gridSize;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                grid[x][y] = C_BLUE;
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                RemoveGreen(grid, gridWidth, gridHeight);
                grid[x][y] = C_GREEN;
            }
        }

        // Handle space key input to clear the grid
        if (IsKeyPressed(KEY_SPACE)) {
            ClearGrid(grid, gridWidth, gridHeight);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the grid
        DrawGrid(gridSize, gridWidth, gridHeight, grid);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
