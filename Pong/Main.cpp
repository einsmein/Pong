// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bat.h"
#include "ball.h"
#include "brick.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    int windowWidth = 1024;
    int windowHeight = 768;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

    int score = 0;
    int lives = 3;

    // create a bat
    Bat bat(windowWidth / 2 - 25, windowHeight - 20);

    // create a ball
    Ball ball(windowWidth / 2, windowHeight - 35);

    // create brick wall
    const int numBrickRow = 10;
    const int numBrickCol = 6;
    const int gap = 5;
    int brickWidth = (windowWidth - windowWidth*0.05 * 2 - numBrickRow*gap) / numBrickRow;
    int brickHeight = 10;
    int leftBound = windowWidth*0.05;
    int topBound = 100;
    Brick bricks[numBrickRow][numBrickCol];
    bool brickHit[numBrickRow][numBrickCol];

    for (int i = 0; i < numBrickRow; i++) {
        for (int j = 0; j < numBrickCol; j++) {
            brickHit[i][j] = false;
            bricks[i][j] = Brick(leftBound + i * (gap + brickWidth), topBound + j * (gap + brickHeight), brickWidth, brickHeight);
        }
    }

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
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (!gameStarted) {
                ball.start();
                gameStarted = true;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if(bat.getPosition().left > 0)  bat.moveLeft();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if(bat.getPosition().left + bat.getPosition().width < windowWidth)  bat.moveRight();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
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

        // Handle ball hitting the brick
        for (int i = 0; i < numBrickRow; i++) {
            for (int j = 0; j < numBrickCol; j++) {
                if (brickHit[i][j] == false) {
                    if (ball.getPosition().intersects(bricks[i][j].getPosition())) {
                        ball.reboundBatOrTop();
                        //delete &(bricks[i][j]);
                        brickHit[i][j] = true;
                        score++;
                    }
                }
            }
        }

        bat.update();
        ball.update();

        // Update the HUD text
        std::stringstream ss;
        ss << "Score: " << score << "      Lives: " << lives;
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
        for (int i = 0; i < numBrickRow; i++) {
            for (int j = 0; j < numBrickCol; j++) {
                if (brickHit[i][j] == false) {
                    window.draw(bricks[i][j].getShape());
                }
            }
        }

        window.draw(hud);
        window.display();
    }

    return 0;
}
