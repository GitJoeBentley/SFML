#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "constants.h"
#include "proto.h"
#include "Ball.h"
#include "Paddle.h"
#include "Tiles.h"
#include "SoundEffect.h"
#include "Game.h"
#include "BasicGame.h"
#include "EasyGame.h"
#include "OneRedTile.h"
#include "CrazyBall.h"
#include "Crusher.h"
#include "Rainbow.h"
#include "RandomTiles.h"
#include "TwoBalls.h"
#include "FallingTiles.h"
#include "Tiles150.h"
#include "ButtonBox.h"
#include "Message.h"
#include "TextBox.h"

using std::cout;
using std::endl;



int main ()
{
    srand(static_cast<unsigned>(time(0)));

    // Fonts
    sf::Font font;
    font.loadFromFile(ResourcePath + "Arial.ttf");

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Joe's Breakout Game", sf::Style::Close);
    sf::Text* title;

    Game* game = nullptr;
    GameSelection gameSelection = GameSelection::New;
    TextBox* tb;
    std::string statement;
    bool hasAHighScore = false;

    //GAME CLOCK & TIMER
    sf::Clock clock;
    sf::Clock timerClock;
    int gameSelected;      // Player's choice of games

    // Texts
    title = new sf::Text("Joe's Breakout Game", font, 30);
    title->setFillColor(sf::Color::Green);
    sf::FloatRect textRect = title->getLocalBounds();
    title->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    // Note: Title x-position adjusted (72.0f) for difference in RenderWindow size
    title->setPosition(sf::Vector2f(RenderWindowSize.x/2.0f + 72.0f, 0.05f * RenderWindowSize.y));

    sf::Text message("", font);
    sf::Vector2f messagePos;

    // Sound effects
    SoundEffect soundEffect;

    sf::Vector2f joystick = sf::Vector2f(0.f,0.f);
    std::string startStr = "To start the game,\nPress the Space Bar on the Keyboard,\nor the Left Button on the Mouse";
    if (sf::Joystick::isConnected(0)) startStr += "\nor the Start Button on the Controller";


    while (gameSelection != GameSelection::Exit)
    {
        message.setFillColor(sf::Color(10,220,250));
        message.setCharacterSize(24);
        message.setStyle(sf::Text::Bold);
        drawCenteredText(message, window);

        if (gameSelection == GameSelection::New)
        {
            // Set up the selected game
            gameSelected = start(window, font, title);
        }
        switch (gameSelected)
        {
        case -1:
            game->setStatus(Game::GameStatus::Quit);
            window.close();
            break;
        case 0:
            game = new EasyGame(window);
            break;
        case 1:
            game = new BasicGame(window);
            break;
        case 2:
            game = new OneRedTile(window);
            break;
        case 3:
            game = new CrazyBall(window);
            break;
        case 4:
            game = new Crusher(window);
            break;
        case 5:
            game = new Rainbow(window);
            break;
        case 6:
            game = new RandomTiles(window);
            break;
        case 7:
            game = new TwoBalls(window);
            break;
        case 8:
            game = new FallingTiles(window);
            break;
        case 9:
            game = new Tiles150(window);
            break;
        default:
            ;
        }

        if (game) message.setPosition(game->centerOfGameWindow());
        game->drawHighScores();

        //////////// The GAME loop
        while (game && (game->getStatus() == Game::GameStatus::NotStarted || game->getStatus() == Game::GameStatus::Active))
        {
            // Look at the mouse, keyboard, or controller
            pollEvent(window, clock, game, joystick);

            // Start of Active Game loop
            if (game->getStatus() == Game::GameStatus::Active)
            {
                game->update(clock.restart());
                game->updateTimer();
                game->manageBall(soundEffect);
                game->managePaddle(soundEffect, message, clock);
            } // End of if Active game

            window.clear();
            game->drawGameObjects();
            if (game->getStatus() == Game::GameStatus::NotStarted)
            {
                message.setString(startStr);
                drawCenteredText(message, window);
            }
            window.display();
        }  // End of the Game Loop

        // Create statement for end of game status
        switch (game->getStatus())
        {
        case Game::GameStatus::Quit:
            statement = "\n               OK ... Bye Bye            \n";
            break;
        case Game::GameStatus::OutOfTime:
            statement = "\n                  Out of Time\n";
            break;
        case Game::GameStatus::OutOfBalls:
            statement = "\n                  Out of Balls\n";
            break;
        case Game::GameStatus::TileHitsPaddle:
            statement = "\n     A falling tile hit the paddle\n";
            break;
        case Game::GameStatus::Win:
            statement = "\n               You win!!!!!!!!!!!!\n";
        default:
            ;
        }
        window.setMouseCursorVisible(true);

        if (game->getStatus() == Game::GameStatus::Quit) break;

        // Record Game Score to High Scores?
        if (game->getScore() && game->getHighScores()->eligible(game->getScore()))
        {
            hasAHighScore = true;
            soundEffect[SoundEffect::EndOfGame].play();
            if (game->getScore() > game->getHighScores()->getHightestScore())
                statement += "\n             Congratulations!!!\n    You have the highest score!!!\n";
            else statement += "\n             Congratulations!!!\n     You made the leader board  \n";
        }

        game->drawGameObjects();
        tb = new TextBox(statement, font, 30, sf::Color::Magenta,game->centerOfGameWindow());
        tb->drawTB(window);
        window.display();
        sf::sleep(sf::Time(sf::seconds(4.0f)));
        delete tb;
        tb = nullptr;
        if (hasAHighScore)
        {
            game->getHighScores()->updateHighScores(Score(getName(window, font, game).c_str(),game->getScore(),time(0)));
            game->getHighScores()->WriteHighScoresFile();
        }

        if (game) delete game;
        game = nullptr;

        gameSelection = playAgain(window, font, title);
    }
    window.close();
}
