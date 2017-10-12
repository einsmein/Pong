#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat {
private:
    Vector2f position;
    RectangleShape batShape;

    float batSpeed = .5f;

public:
    Bat(float startX, float startY);

    FloatRect getPosition();
    RectangleShape getShape();

    void setXPosition(float x);
	void setColor(Color color);

    void moveLeft();
    void moveRight();
    void update();
};