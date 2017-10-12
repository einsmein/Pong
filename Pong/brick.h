#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Brick {
private:
    Vector2f position;
    RectangleShape brickShape;

public:
    Brick();
    Brick(float startX, float startY, float width, float height);
    
    FloatRect getPosition();
    RectangleShape getShape();

	void setColor(Color color);
    void hitByBall();
};