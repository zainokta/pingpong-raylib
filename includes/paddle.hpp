#ifndef PADDLE_H
#define PADDLE_H

#include "ball.hpp"
#include <raylib.h>

const float PADDLE_SPEED = 400.0f;
const float PADDLE_HEIGHT = 80.0f;
const float PADDLE_WIDTH = 15.0f;

struct Paddle {
  Rectangle position;
  float width;
  float height;

  Paddle(float x) {
    position = {x, GetScreenHeight() / 2.0f - PADDLE_HEIGHT / 2.0f,
                PADDLE_WIDTH, PADDLE_HEIGHT};
  }

  void Draw() { DrawRectangleRec(position, BLACK); }

  void Update(float dt, bool moveKeyUp, bool moveKeyDown) {
    if (moveKeyUp && position.y > 0) {
      position.y -= PADDLE_SPEED * dt;
    }
    if (moveKeyDown && position.y < GetScreenHeight() - position.height) {
      position.y += PADDLE_SPEED * dt;
    }
  }

  void HandleBallCollision(Ball &ball) {
    if (CheckCollisionCircleRec(ball.position, ball.radius, position)) {
      ball.speed.x = -ball.speed.x;

      float hitPos = (ball.position.y - position.y) / position.height;
      ball.speed.y = (hitPos - 0.5f) * ball.GetBallSpeed() * 2;
    }
  }
};
#endif // !PADDLE_H
