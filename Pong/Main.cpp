// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bat.h"
#include "ball.h"
#include "brick.h"
#include "brickwall.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    int windowWidth = 1024;
    int windowHeight = 670;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

    int score = 0;
    int lives = 3;

    // create a bat
    Bat bat(windowWidth / 2 - 25, windowHeight - 20);

    // create a ball
    Ball ball(windowWidth / 2, windowHeight - 35);

    // create brick wall
    const int numBrickCol = 10;
    const int numBrickRow = 6;
    const int gap = 7;
    int brickWidth = (windowWidth - windowWidth*0.04 * 2 - numBrickCol*gap) / numBrickCol;
    int brickHeight = 15;
    int leftBound = windowWidth*0.04;
    int topBound = 100;
    // ========================= OLD ONE ======================
    Brick bricks[numBrickCol][numBrickRow];
    int brickHit[numBrickCol][numBrickRow];

    for (int i = 0; i < numBrickCol; i++) {
        for (int j = 0; j < numBrickRow; j++) {
            brickHit[i][j] = 0;
            bricks[i][j] = Brick(leftBound + i * (gap + brickWidth), topBound + j * (gap + brickHeight), brickWidth, brickHeight);
        }
    }
    // ========================================================

    // ========================= NEW ONE ======================
    //BrickWall brickWall(numBrickCol, numBrickRow, brickWidth, brickHeight, gap, leftBound, topBound);
    // ========================================================

    // Create a "Text" object called "message". Weird but we will learn about objects soon
    Text hud;
    Font font;
    font.loadFromFile("DS-DIGIT.ttf");
    hud.setFont(font);
    hud.setCharacterSize(20);
    hud.setFillColor(Color::White);

    bool gameStarted = false;

    // Game loop
    while (window.isOpen()) {

        /*
        Handle the player input
        *********************************************************************
        *********************************************************************
        *********************************************************************
        */
        Event event;
        if (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            //delete bricks;
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (!gameStarted) {
                ball.start();
                gameStarted = true;
            }
        }

        if (gameStarted) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (bat.getPosition().left > 0)  bat.moveLeft();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (bat.getPosition().left + bat.getPosition().width < windowWidth)  bat.moveRight();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
        }

        /*
        Update the frame
        *********************************************************************
        *********************************************************************
        *********************************************************************
        */

        // Handle ball hitting the bottom
        if (ball.getPosition().top > windowHeight) {
            ball.hitBottom();
            bat.setXPosition(windowWidth / 2 - 25);
            ball.setPosition(windowWidth / 2, windowHeight - 35);
            lives--;
            if (lives < 1) {
                score = 0;
                lives = 3;

                // reset bricks
                // ========================= NEW ONE ======================
                //brickWall.resetWall();
                // ========================================================
                // ========================= OLD ONE ======================
                for (int i = 0; i < numBrickCol; i++) {
                    for (int j = 0; j < numBrickRow; j++) {
                        brickHit[i][j] = 0;
                        bricks[i][j].setColor(Color::White);
                    }
                }
                // ========================================================
            }
            gameStarted = false;
        }

        // Handle ball hitting the top
        if (ball.getPosition().top < 0) {
            ball.reboundBatOrTop();
        }

        // Handle ball hitting the sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > windowWidth) {
            ball.reboundSides();
        }

        // Handle ball hitting the bat
        if (ball.getPosition().intersects(bat.getPosition())) {
            ball.reboundBatOrTop();
        }

        // Handle brick hit and brick blink
        for (int i = 0; i < numBrickRow; i++) {
            for (int j = 0; j < numBrickCol; j++) {

                // Handle ball hitting the brick
                // ========================= NEW ONE ======================
                //int brickHit = brickWall.detectHit(ball.getPosition());
                //if (brickHit > 0) {
                //    score += brickHit;
                //    ball.reboundBatOrTop();
                //}
                // ========================================================
                // ========================= OLD ONE ======================
                if (brickHit[i][j] == 0) {
                    if (ball.getPosition().intersects(bricks[i][j].getPosition())) {
                        ball.reboundBatOrTop();
                        //delete &(bricks[i][j]);
                        brickHit[i][j] = 1;
                        score++;
                    }
                }

                // Handle brick hit previously, now blink
                else if (brickHit[i][j] > 0 && brickHit[i][j] <= 50) {
                    bricks[i][j].hitByBall();
                    brickHit[i][j] += 1;
                }

                else if (brickHit[i][j] > 50) {
                    bricks[i][j].hitByBall();
                    brickHit[i][j] = -1;
                }
                // ========================================================
            }
        }

        bat.update();
        ball.update();

        // Update the HUD text
        std::stringstream ss;
        ss << "Score: " << score << "      Lives: " << lives << "       ball y velocity: " << ball.getYVelocity();
        hud.setString(ss.str());


        /*
        Draw the frame
        *********************************************************************
        *********************************************************************
        *********************************************************************
        */

        // Clear everything from the last frame
        window.clear(Color(26, 128, 182, 255));

        window.draw(bat.getShape());
        window.draw(ball.getShape());

        // ========================= NEW ONE ======================
        //RectangleShape* brickShapes = brickWall.getBrickShapes();
        //for (int i = 0; i < numBrickCol; i++) {
        //    for (int j = 0; j < numBrickRow; j++) {
        //        window.draw(brickShapes[i*numBrickCol + j]);
        //    }
        //}
        // ========================================================
        // ========================= OLD ONE ======================
        for (int i = 0; i < numBrickCol; i++) {
            for (int j = 0; j < numBrickRow; j++) {
                if (brickHit[i][j] != -1) {
                    window.draw(bricks[i][j].getShape());
                }
            }
        }
        // ========================================================

        window.draw(hud);
        window.display();
    }

    return 0;
}
