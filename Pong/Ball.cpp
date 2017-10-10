#include "stdafx.h"
#include "ball.h"

Ball::Ball(float startX, float startY) {
    position.x = startX;
    position.y = startY;

    ballShape.setSize(sf::Vector2f(10, 10));
    ballShape.setPosition(position);
}

FloatRect Ball::getPosition(){
    return ballShape.getGlobalBounds();
}

RectangleShape Ball::getShape() {
    return ballShape;
}

float Ball::getXVelocity() {
    return xVelocity;
}

void Ball::start() {
    yVelocity = -.6f;
    xVelocity = .6f;
}

void Ball::reboundSides() {
    xVelocity = -xVelocity;
}

void Ball::reboundBatOrTop() {

    //position.y -= (yVelocity * 30);
    yVelocity = -yVelocity;
}

void Ball::hitBottom() {
    // reset position of the ball to middle horizontal
    position.y = 768-35;
    position.x = 500;
    xVelocity = 0;
    yVelocity = 0;
}

void Ball::update() {
    position.x += xVelocity;
    position.y += yVelocity;
    ballShape.setPosition(position);
}