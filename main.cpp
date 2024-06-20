#include <iostream>
#include <raylib.h>
#include <vector>

using namespace std;

// Compile: g++ -std=c++20 -o pong main.cpp -lraylib

class Ball {
    public:
    float x;
    float y;

    int speedX;
    int speedY;
    int radius;

    Ball(float posX, float posY, int spdX, int spdY, int rad) {
        x = posX;
        y = posY;
        speedX = spdX;
        speedY = spdY;
        radius = rad;
    }

    void Draw() {
        DrawCircle(x, y, radius, RAYWHITE);
    }

    void Update() {
        x += speedX;
        y += speedY;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speedY *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speedX *= -1;
        }
    }
};


class Paddle {
    public:
    float x;
    float y;
    float width;
    float height;
    int speed;

    Paddle(float posX, float posY, float w, float h, int spd)
        : x(posX), y(posY), width(w), height(h), speed(spd) {}

    void Draw() {
        DrawRectangle(x, y, width, height, RAYWHITE);
    }
};

class PlayerPaddle : public Paddle {
    public:
    PlayerPaddle(float posX, float posY, float w, float h, int spd)
        : Paddle(posX, posY, w, h, spd) {}

    void UpdatePlayerPaddle() {
        if (IsKeyDown(KEY_UP)) y -= speed;
        if (IsKeyDown(KEY_DOWN)) y += speed;
        if (y <= 0) y = 0;
        if (y + height >= GetScreenHeight()) y = GetScreenHeight() - height;
    }
};

class MachinePaddle : public Paddle {
    public:
    MachinePaddle(float posX, float posY, float w, float h, int spd)
        : Paddle(posX, posY, w, h, spd) {}

    void UpdateMachinePaddle() {
        cout << "Machine Paddle << MOVING >>" << endl;
    }
};


int main() {

    cout << " Starting Game >>>" << endl;
    const int screenWidth  = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "PONG");
    SetTargetFPS(60);

    // needs improvement to avoid tedious math
    Ball ball = Ball(screenWidth / 2, screenHeight / 2, 7, 7, 20);
    PlayerPaddle myPaddle = PlayerPaddle(screenWidth - 35, screenHeight / 2 - 60, 25, 120, 6);
    MachinePaddle aipaddle = MachinePaddle(10, screenHeight/2 - 60, 25, 120, 6);

    while(!WindowShouldClose()) {
        BeginDrawing();

        // Updating the ball's pos after moving
        ball.Update();
        myPaddle.UpdatePlayerPaddle();
        aipaddle.UpdateMachinePaddle();

        // Drawing the Game
        ClearBackground(BLACK); // Clear the screen with a background color
        ball.Draw();
        myPaddle.Draw();
        aipaddle.Draw();

        // Drawing the middle line of game
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, RAYWHITE);
        EndDrawing();
    } 

    CloseWindow();
    return 0;
}