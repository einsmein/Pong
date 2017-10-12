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
	Bat bat2(windowWidth / 3 - 25, windowHeight - 20);

	bat2.setColor(Color::Yellow);

    // create a ball
    Ball ball(windowWidth / 2, windowHeight - 35);
	Ball ball2(windowWidth / 3, windowHeight - 35);

    // create brick wall
    const int numBrickCol = 10;
    const int numBrickRow = 6;
    const int gap = 5;
    int brickWidth = (windowWidth - windowWidth*0.05 * 2 - numBrickCol*gap) / numBrickCol;
    int brickHeight = 10;
    int leftBound = windowWidth*0.05;
    int topBound = 100;
	Brick bricks[numBrickCol][numBrickRow];
	int brickHit[numBrickCol][numBrickRow];

	for (int i = 0; i < numBrickCol; i++) {
		for (int j = 0; j < numBrickRow; j++) {
			brickHit[i][j] = 0;
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
				ball2.start();
                gameStarted = true;
            }
        }

		if (gameStarted) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				if (bat2.getPosition().left > 0)  bat2.moveLeft();
			}
			else if (Keyboard::isKeyPressed(Keyboard::D)) {
				if (bat2.getPosition().left + bat2.getPosition().width < windowWidth)  bat2.moveRight();
			}

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
        if (ball.getPosition().top > windowHeight || ball2.getPosition().top > windowHeight) {
            ball.hitBottom();
			ball2.hitBottom();
            bat.setXPosition(windowWidth / 2 - 25);
            ball.setPosition(windowWidth / 2, windowHeight - 35);
			bat2.setXPosition(windowWidth / 3 - 25);
			ball2.setPosition(windowWidth / 3, windowHeight - 35);
            lives--;
            if (lives < 1) {
                score = 0;
                lives = 3;

				for (int i = 0; i < numBrickCol; i++) {
					for (int j = 0; j < numBrickRow; j++) {
						brickHit[i][j] = 0;
						bricks[i][j].setColor(Color::White);
					}
				}
            }
            gameStarted = false;
        }

        // Handle ball hitting the top
        if (ball.getPosition().top < 0) {
            ball.reboundBatOrTop();
        }
		if (ball2.getPosition().top < 0) {
			ball2.reboundBatOrTop();
		}

        // Handle ball hitting the sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > windowWidth) {
            ball.reboundSides();
        }
		if (ball2.getPosition().left < 0 || ball2.getPosition().left + ball2.getPosition().width > windowWidth) {
			ball2.reboundSides();
		}

        // Handle ball hitting the bat
        if (ball.getPosition().intersects(bat.getPosition()) ||
			ball.getPosition().intersects(bat2.getPosition())) {
            ball.reboundBatOrTop();
        }
		if (ball2.getPosition().intersects(bat.getPosition()) ||
			ball2.getPosition().intersects(bat2.getPosition())) {
			ball2.reboundBatOrTop();
		}
        // Handle ball hitting the brick
        for (int i = 0; i < numBrickCol; i++) {
            for (int j = 0; j < numBrickRow; j++) {

				if (brickHit[i][j] == 0) {
					if (ball.getPosition().intersects(bricks[i][j].getPosition())) {
						ball.reboundBatOrTop();
						//delete &(bricks[i][j]);
						brickHit[i][j] = 1;
						score++;
					}
					if (ball2.getPosition().intersects(bricks[i][j].getPosition())) {
						ball2.reboundBatOrTop();
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
            }
        }

        bat.update();
        ball.update();

		bat2.update();
		ball2.update();

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
		window.draw(bat2.getShape());
		window.draw(ball2.getShape());
		for (int i = 0; i < numBrickCol; i++) {
			for (int j = 0; j < numBrickRow; j++) {
				if (brickHit[i][j] != -1) {
					window.draw(bricks[i][j].getShape());
				}
			}
		}

        window.draw(hud);
        window.display();
    }

    return 0;
}

