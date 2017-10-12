#include "stdafx.h"
#include "brick.h"

Brick::Brick() {

}

Brick::Brick(float startX, float startY, float width, float height) {
    position.x = startX;
    position.y = startY;

    brickShape.setSize(sf::Vector2f(width, height));
    brickShape.setPosition(position);
}

FloatRect Brick::getPosition() {
    return brickShape.getGlobalBounds();
}

RectangleShape Brick::getShape() {
    return brickShape;
}

void Brick::setColor(Color color) {
    brickShape.setFillColor(color);
}

void Brick::hitByBall() {
    brickShape.setFillColor(Color(15, 105, 150, 255));
}