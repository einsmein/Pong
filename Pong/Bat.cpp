#include "stdafx.h"
#include "bat.h"


// This the constructor and it is called when we create an object
Bat::Bat(float startX, float startY) {
    position.x = startX;
    position.y = startY;

    batShape.setSize(sf::Vector2f(60, 5));
    batShape.setPosition(position);
}

FloatRect Bat::getPosition() {
    return batShape.getGlobalBounds();
}

RectangleShape Bat::getShape() {
    return batShape;
}

void Bat::setXPosition(float x) {
    position.x = x;
}

void Bat::moveLeft() {
    position.x -= batSpeed;
}

void Bat::moveRight() {
    position.x += batSpeed;
}

void Bat::update() {
    batShape.setPosition(position);
}