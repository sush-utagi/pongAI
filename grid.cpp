#include "raylib.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <thread>
#include <chrono>

// compile with: g++ -std=c++20 grid.cpp -o grid -lraylib

enum CellState { CELL_BLACK, CELL_BLUE, CELL_GREEN, CELL_RED, CELL_PATH };

const int INF = std::numeric_limits<int>::max();
const std::vector<Vector2> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// Function to draw a 500x500 grid
void DrawGrid(int gridSize, int gridWidth, int gridHeight, CellState grid[50][50]) {
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {
            Color cellColor;
            switch (grid[x][y]) {
                case CELL_BLACK: cellColor = BLACK; break;
                case CELL_BLUE: cellColor = BLUE; break;
                case CELL_GREEN: cellColor = GREEN; break;
                case CELL_RED: cellColor = RED; break;
                case CELL_PATH: cellColor = DARKGRAY; break; // Path color
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
            grid[x][y] = CELL_BLACK;
        }
    }
}

// Function to remove any existing green square
void RemoveGreen(CellState grid[50][50], int gridWidth, int gridHeight) {
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {
            if (grid[x][y] == CELL_GREEN) {
                grid[x][y] = CELL_BLACK;
            }
        }
    }
}

// Function to find the shortest path using Dijkstra's algorithm
void SimulateDijkstra(CellState grid[50][50], int gridWidth, int gridHeight, int gridSize) {
    std::cout << "Simulating Dijkstra's algorithm..." << std::endl;

    // Find green and red squares
    Vector2 start, end;
    bool startFound = false, endFound = false;

    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            if (grid[i][j] == CELL_GREEN) {
                start = { (float)i, (float)j };
                startFound = true;
            }
            if (grid[i][j] == CELL_RED) {
                end = { (float)i, (float)j };
                endFound = true;
            }
        }
    }

    if (!startFound || !endFound) {
        std::cout << "Green or Red cell not found!" << std::endl;
        return;
    }

    std::cout << "Start at: " << start.x << " " << start.y << std::endl;
    std::cout << "End at: " << end.x << " " << end.y << std::endl;

    // Initialize Dijkstra's algorithm
    std::vector<std::vector<int>> dist(gridWidth, std::vector<int>(gridHeight, INF));
    std::vector<std::vector<Vector2>> prev(gridWidth, std::vector<Vector2>(gridHeight, {-1, -1}));
    dist[(int)start.x][(int)start.y] = 0;

    auto compare = [&dist](Vector2 a, Vector2 b) {
        return dist[(int)a.x][(int)a.y] > dist[(int)b.x][(int)b.y];
    };

    std::priority_queue<Vector2, std::vector<Vector2>, decltype(compare)> pq(compare);
    pq.push(start);

    while (!pq.empty()) {
        Vector2 current = pq.top();
        pq.pop();

        if (current.x == end.x && current.y == end.y) break;

        for (const auto& dir : directions) {
            Vector2 neighbor = { current.x + dir.x, current.y + dir.y };
            if (neighbor.x >= 0 && neighbor.x < gridWidth && neighbor.y >= 0 && neighbor.y < gridHeight) {
                if (grid[(int)neighbor.x][(int)neighbor.y] == CELL_BLUE) continue; // Skip obstacles

                int newDist = dist[(int)current.x][(int)current.y] + 1;
                if (newDist < dist[(int)neighbor.x][(int)neighbor.y]) {
                    dist[(int)neighbor.x][(int)neighbor.y] = newDist;
                    prev[(int)neighbor.x][(int)neighbor.y] = current;
                    pq.push(neighbor);

                    // Visualize the current step
                    BeginDrawing();
                    ClearBackground(BLACK);
                    DrawGrid(gridSize, gridWidth, gridHeight, grid);

                    // Draw white rectangle covering both current and neighbor cells
                    int rectX = std::min(current.x, neighbor.x) * gridSize;
                    int rectY = std::min(current.y, neighbor.y) * gridSize;
                    int rectWidth = gridSize * (std::abs(current.x - neighbor.x) + 1);
                    int rectHeight = gridSize * (std::abs(current.y - neighbor.y) + 1);

                    DrawRectangle(rectX, rectY, rectWidth, rectHeight, WHITE);

                    EndDrawing();

                    // Pause to visualize the process
                    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }
    }

    // Trace the path from end to start
    Vector2 step = end;
    while (step.x != -1 && step.y != -1 && !(step.x == start.x && step.y == start.y)) {
        if (grid[(int)step.x][(int)step.y] == CELL_BLACK) {
            grid[(int)step.x][(int)step.y] = CELL_PATH; // Mark the path
        }
        step = prev[(int)step.x][(int)step.y];
    }
}

int main() {
    // Initialize the window
    const int screenWidth = 750;
    const int screenHeight = 750;
    InitWindow(screenWidth, screenHeight, "Dijkstra's Algorithm - Grid");

    // Grid settings
    const int gridSize = 15;
    const int gridWidth = 50;
    const int gridHeight = 50;

    // Grid state
    CellState grid[50][50] = { CELL_BLACK };

    // Set target FPS
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Handle mouse input
        Vector2 mousePos = GetMousePosition();
        int x = mousePos.x / gridSize;
        int y = mousePos.y / gridSize;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                grid[x][y] = CELL_BLUE;
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                RemoveGreen(grid, gridWidth, gridHeight);
                grid[x][y] = CELL_GREEN;
                grid[49][49] = CELL_RED;
            }
        }

        // Handle space key input to clear the grid
        if (IsKeyPressed(KEY_SPACE)) {
            ClearGrid(grid, gridWidth, gridHeight);
        }

        // Handle 'S' key input to simulate Dijkstra's algorithm
        if (IsKeyPressed(KEY_S)) {
            SimulateDijkstra(grid, gridWidth, gridHeight, gridSize);
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
