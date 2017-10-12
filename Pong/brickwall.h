#pragma once
#include <SFML/Graphics.hpp>
#include "brick.h"

using namespace sf;

class BrickWall {
private:
    Brick* bricks;
    int* brickHit;

    int numCol;
    int numRow;
    Vector2f position;
    RectangleShape brickShape;

public:
    BrickWall(int numCol, int numRow, int brickWidth, int brickHeight, int gap, int leftBound, int topBound);

    FloatRect* getPosition();
    RectangleShape* getBrickShapes();

    void resetWall();
    int detectHit(FloatRect ballPosition);

};