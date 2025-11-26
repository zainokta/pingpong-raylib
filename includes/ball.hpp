#ifndef BALL_H
#define BALL_H

#include <chrono>
#include <random>
#include <raylib.h>

const float BALL_RADIUS = 6.0f;
const float BALL_SPEED = 300.0f;

struct Ball {
  Vector2 position;
  float radius;
  Vector2 speed;

  Ball()
      : position{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        speed{BALL_SPEED, BALL_SPEED}, radius(BALL_RADIUS) {}

  void Update(float dt) {
    position.x += speed.x * dt;
    position.y += speed.y * dt;

    if (position.y <= radius || position.y >= GetScreenHeight() - radius) {
      speed.y *= -1.0f;
    }
  }

  void Draw() { DrawCircleV(position, radius, BLACK); }

  void Reset() {
    position = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    int minVal = -1;
    int maxVal = 1;
    std::uniform_int_distribution<int> distribution(minVal, maxVal);

    int direction = distribution(generator);
    if (direction == 0) {
      direction = 1;
    }

    speed = {BALL_SPEED * direction, BALL_SPEED * direction};
  }

  bool IsOutLeft() const { return position.x < -radius; }

  bool IsOutRight() const { return position.x > GetScreenWidth() + radius; }

  float GetBallSpeed() const { return BALL_SPEED; }
};
#endif // !BALL_H
