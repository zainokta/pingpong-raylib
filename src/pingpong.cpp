#include "../includes/ball.hpp"
#include "../includes/paddle.hpp"
#include "raylib.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main() {
  int scorePlayer1 = 0;
  int scorePlayer2 = 0;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ping Pong");
  SetTargetFPS(60);

  Paddle player1(0);
  Paddle player2(SCREEN_WIDTH - PADDLE_WIDTH);

  Ball ball;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    player1.Update(dt, IsKeyDown(KEY_W), IsKeyDown(KEY_S));
    player2.Update(dt, IsKeyDown(KEY_UP), IsKeyDown(KEY_DOWN));
    ball.Update(dt);

    player1.HandleBallCollision(ball);
    player2.HandleBallCollision(ball);

    if (ball.IsOutLeft()) {
      scorePlayer2++;
      ball.Reset();
    }

    if (ball.IsOutRight()) {
      scorePlayer1++;
      ball.Reset();
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    player1.Draw();
    player2.Draw();

    ball.Draw();

    DrawText(TextFormat("Score Player 1: %i", scorePlayer1), 200, 80, 20,
             BLACK);
    DrawText(TextFormat("Score Player 2: %i", scorePlayer2), 400, 80, 20,
             BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
