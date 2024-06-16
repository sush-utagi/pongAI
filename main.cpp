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
    int   speed;

    // Paddle(float posX, float posY, float w, float h, int spd) {
    //     x = posX;
    //     y = posY;
    //     width = w;
    //     height = h;
    //     speed = spd;
    // }

    void Draw() {
        DrawRectangle(x, y, width, height, RAYWHITE);
    }

    void UpdatePlayerPaddle() {
        if(IsKeyDown(KEY_W)) y -= speed;
        if(IsKeyDown(KEY_S)) y += speed;
    }
};

Paddle playerPaddle;

int main() {

    cout << " Starting Game >>>" << endl;
    const int screenWidth  = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "PONG");
    SetTargetFPS(60);

    Ball ball = Ball(screenWidth / 2, screenHeight / 2, 7, 7, 20);

    playerPaddle.width = 25;
    playerPaddle.height = 120;
    playerPaddle.x = screenWidth - playerPaddle.width - 10;
    playerPaddle.y = screenHeight / 2 - playerPaddle.height / 2;
    playerPaddle.speed = 6;
    // Paddle leftPaddle = Paddle(10, screenHeight/2 - 60, 25, 120, 6);
    // Paddle rightPaddle = Paddle(screenWidth-);

    while(WindowShouldClose() == false) {
        BeginDrawing();

        // Updating the ball's pos after moving
        ball.Update();
        playerPaddle.UpdatePlayerPaddle();

        // Drawing the Game
        ClearBackground(BLACK); // Clear the screen with a background color
        ball.Draw();
        playerPaddle.Draw();
        // leftPaddle.Draw();
        // rightPaddle.Draw();
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, RAYWHITE);


        EndDrawing();
    } 

    CloseWindow();
    return 0;
}