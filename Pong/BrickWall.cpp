#include "stdafx.h"
#include "brickwall.h"
#include "brick.h"

BrickWall::BrickWall(int numCol, int numRow, int brickWidth, int brickHeight, int gap, int leftBound, int topBound) {
    bricks = new Brick[numCol*numRow];  //Brick *bricks = new Brick[numCol*numRow]
    brickHit = new int[numCol*numRow];

    for (int i = 0; i < numCol; i++) {
        for (int j = 0; j < numRow; j++) {
            //brickHit[i*numCol + j] = 0;
            //bricks[i*numCol + j] = Brick(leftBound + i * (gap + brickWidth), topBound + j * (gap + brickHeight), brickWidth, brickHeight);
        }
    }
}
//
//FloatRect* BrickWall::getPosition() {
//    
//}
//
RectangleShape* BrickWall::getBrickShapes() {
    RectangleShape* brickShapes = new RectangleShape[numRow*numCol];
    for (int i = 0; i < numCol; i++) {
        for (int j = 0; j < numRow; j++) {
            brickShapes[i*numCol+j] = bricks[i*numCol + j].getShape();
        }
    }
    return brickShapes;
}

void BrickWall::resetWall() {
    for (int i = 0; i < numCol; i++) {
        for (int j = 0; j < numRow; j++) {
            brickHit[i*numCol + j] = 0;
            bricks[i*numCol + j].setColor(Color::White);
        }
    }
}

int BrickWall::detectHit(FloatRect ballPosition) {
    int numHit = 0;
    for (int i = 0; i < numCol; i++) {
        for (int j = 0; j < numRow; j++) {
            if (brickHit[i*numCol + j] == 0) {
                if (bricks[i*numCol + j].getPosition().intersects(ballPosition)) {
                    brickHit[i*numCol + j] = 1;
                    bricks[i*numCol + j].hitByBall();
                    numHit++;
                }
            }
            else if (brickHit[i*numCol + j] > 0 && brickHit[i*numCol + j] < 15) {
                brickHit[i*numCol + j]++;
            }
            else if (brickHit[i*numCol + j] > 15) {
                brickHit[i*numCol + j] = -1;
            }
        }
    }
    return numHit;
}