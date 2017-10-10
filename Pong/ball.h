#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
private:
    Vector2f position;
    RectangleShape ballShape;

    float xVelocity = 0;// .6f;
    float yVelocity = 0;// .6f;

public:
    Ball(float startX, float startY);

    FloatRect getPosition();
    RectangleShape getShape();

    float getXVelocity();

    void setPosition(float x, float y);
    void start();
    void reboundSides();
    void reboundBatOrTop();
    void hitBottom();
    void update();
};