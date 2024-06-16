#include <iostream>
#include <raylib.h>
#include <vector>

using namespace std;

// Compile: g++ -std=c++20 -o pong main.cpp -lraylib

int main() {

    cout << " Starting Game >>>" << endl;
    const int screenWidth  = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "PONG");
    SetTargetFPS(60);

    while(WindowShouldClose() == false) {
        BeginDrawing();
        // ClearBackground(RAYWHITE);  // Clear the screen with a background color

        // Drawing the Game
        DrawCircle(screenWidth/2, screenHeight/2, 20, RAYWHITE);
        DrawRectangle(10, screenHeight/2 - 60, 25, 120, RAYWHITE);
        DrawRectangle(screenWidth-35, screenHeight/2 - 60, 25, 120, RAYWHITE);


        EndDrawing();
    } 

    CloseWindow();
    return 0;
}