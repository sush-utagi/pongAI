#include <iostream>
#include <raylib.h>
#include <vector>

using namespace std;

// Compile: g++ -std=c++20 -o pong main.cpp -lraylib

int PLAYER_SCORE  = 0;
int MACHINE_SCORE = 0;

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
    protected:
    void limitPaddleMovement() {
        if (y <= 0) y = 0;
        if (y + height >= GetScreenHeight()) y = GetScreenHeight() - height;
    }

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
        limitPaddleMovement();
    }
};

class MachinePaddle : public Paddle {
    public:
    MachinePaddle(float posX, float posY, float w, float h, int spd)
        : Paddle(posX, posY, w, h, spd) {}

    void UpdateMachinePaddle(int ballY) {
        if (y + height/2 < ballY) y += speed;
        if (y + height/2 > ballY) y -= speed;
        limitPaddleMovement();
    }
};


class Scoreboard {
    public:
    void Draw() {
        DrawText(to_string(PLAYER_SCORE).c_str(), GetScreenWidth()/2 + 20, 20, 20, RAYWHITE);
        DrawText(to_string(MACHINE_SCORE).c_str(), GetScreenWidth()/2 - 40, 20, 20, RAYWHITE);
    }

    void Update() {
        if (PLAYER_SCORE == 5) {
            DrawText("PLAYER WINS", GetScreenWidth()/2 - 100, GetScreenHeight()/2, 20, RAYWHITE);
            PLAYER_SCORE = 0;
            MACHINE_SCORE = 0;
        }
        if (MACHINE_SCORE == 5) {
            DrawText("MACHINE WINS", GetScreenWidth()/2 - 100, GetScreenHeight()/2, 20, RAYWHITE);
            PLAYER_SCORE = 0;
            MACHINE_SCORE = 0;
        }
    }
};



int main() {

    cout << " Starting Game >>>" << endl;
    const int screenWidth  = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "PONG");
    SetTargetFPS(60);

    // needs improvement to avoid tedious math, but this is where the game objects are initialised
    Ball ball = Ball(screenWidth / 2, screenHeight / 2, 7, 7, 20);
    PlayerPaddle myPaddle = PlayerPaddle(screenWidth - 35, screenHeight / 2 - 60, 25, 120, 6);
    MachinePaddle aipaddle = MachinePaddle(10, screenHeight/2 - 60, 25, 120, 6);
    Scoreboard sc = Scoreboard();

    while(!WindowShouldClose()) {

        // Drawing the Game
        BeginDrawing();
        ClearBackground(BLACK); // Clear the screen with a background color
        ball.Draw();
        myPaddle.Draw();
        aipaddle.Draw();
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, RAYWHITE); // middle line
        sc.Draw();
        EndDrawing();

        // Updating the ball's pos after moving
        ball.Update();
        myPaddle.UpdatePlayerPaddle();
        aipaddle.UpdateMachinePaddle(ball.y);
        sc.Update();
    

        // Check for collisions ball -> paddle
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{myPaddle.x, myPaddle.y, myPaddle.width, myPaddle.height})) {
            ball.speedX *= -1;
            PLAYER_SCORE++;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{aipaddle.x, aipaddle.y, aipaddle.width, aipaddle.height})) {
            ball.speedX *= -1;
            MACHINE_SCORE++;
        }

    } 

    CloseWindow();
    return 0;
}