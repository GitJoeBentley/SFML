#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Constants.h"
#include "Message.h"
using namespace std;

Game::Game(sf::RenderWindow& wind, const std::string& name_)
    : window(wind),
      sounds(),
      border(sf::Vector2f(GameWindowSize, GameWindowSize)),
      door1(CellSize),door2(CellSize),
      titleText(name_ + "'s Hidden Maze Game - Version 2.0", Fonts::Kristan, 36),
      statusText("Time 60\nBruises 0\nScore 0", Fonts::Courier, 24 ),
      displayMaze(false)
{
    border.setOutlineThickness(CellWidth);
    borderTexture.loadFromFile(BorderImageFile);
    border.setTexture(&borderTexture);
    border.setOutlineColor(sf::Color(sf::Color(20,130,10)));
    border.setPosition(WindowHorizontalOffset, WindowVerticalOffset);
    door1.setFillColor(sf::Color(0,0,0));
    door1.setPosition(WindowHorizontalOffset - CellWidth, WindowVerticalOffset + 0 * CellWidth);
    door2.setFillColor(sf::Color(sf::Color::Green));
    door2.setPosition(WindowHorizontalOffset + NumRows * CellWidth, WindowVerticalOffset + (NumRows-1) * CellWidth);

    arrowTexture.loadFromFile(ArrowImageFile);
    arrow1.setTexture(arrowTexture);
    arrow2.setTexture(arrowTexture);
    arrow1.setPosition(WindowHorizontalOffset - 2 * CellWidth, WindowVerticalOffset + 0 * CellWidth);
    arrow2.setPosition(WindowHorizontalOffset + (NumRows+1) * CellWidth, WindowVerticalOffset + (NumRows-1) * CellWidth);

    titleText.setPosition(WindowHorizontalOffset / 2, CellWidth);
    titleText.setFillColor(sf::Color(250,150,200));

    statusText.setPosition(850.0f, 25.0f);
    statusText.setFillColor(sf::Color(250,250,180));

    refresh(name_);

    sounds.playmusic();

    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color(0*255,0,1*255));
    timeBar.setPosition((GameSize.x / 2) - timeBarStartWidth / 2, 85);
}

Game::~Game()
{
    if (grid) delete grid;
    grid = nullptr;
    if (player) delete player;
    player = nullptr;
}

// getters
sf::RenderWindow& Game::getWindow()
{
    return window;
}

sf::RectangleShape& Game::getBorder()
{
    return border;
}

Grid* Game::getGrid()
{
    return grid;
}

Player* Game::getPlayer()
{
    return player;
}

int Game::getScore() const
{
    return player->getScore();
}

int Game::getBruises() const
{
    return player->getBruises();
}

Game::GameStatus Game::getStatus() const
{
    return status;
}

Sounds& Game::getSounds()
{
    return sounds;
}

int Game::getCountdown() const
{
    return player -> getCountdown();
}

//setters
void Game::setStatus(Game::GameStatus status_)
{
    status = status_;
}
void Game::toggleDisplayMaze()
{
    displayMaze = !displayMaze;
}

void Game::incrementBruises()
{
    player->incrementBruises();
}
void Game::decrementScore()
{
    player->decrementScore();
}

void Game::refresh(const string& name_)
{
    if (grid) delete grid;
    if (player) delete player;
    grid = new Grid();
    player = new Player(name_, *grid, sounds, window);
}

void Game::bounce()
{
    sounds.play(Sounds::Bounce, 50);
    player->bounce();
}

void Game::move(Player::Direction direction)
{
    if (status == Game::NotStarted) status = Game::Active;
    sf::Vector2i playerLoc = player->getLocation();
    if (playerLoc == sf::Vector2i(NumCols-1,NumRows-1) && direction == Player::Right)
    {
        status = Game::Win;
        return;
    }
    player-> move(direction);
    if (player->getBruises() >= 50) status = Game::Loss;
    return;
}

bool Game::bomb()
{
    return player -> bomb();
}

bool Game::light()
{
    return player -> light();
}

void Game::draw_and_display()
{
    float timePercentRemaining = player->getCountdown()/60.0f;
    window.clear();
    window.draw(border);
    window.draw(door2);
    window.draw(arrow2);
    statusText.setString(string("Time ") + std::to_string(getCountdown()) + "\nBruises " + std::to_string(player->getBruises()) + "\nScore " + std::to_string(player->getScore()));
    window.draw(statusText);
    window.draw(titleText);
    timeBar.setSize(sf::Vector2f(timeBarStartWidth * timePercentRemaining, timeBarHeight));
    // change timebar color
    timeBar.setFillColor(sf::Color((1-timePercentRemaining)*255,timePercentRemaining*255,0));

    window.draw(timeBar);
    if (player->getPath().size() > 1) player->draw_path(window);

    if (displayMaze)
    {
        grid->draw_path(window);
        grid->draw(window);
    }
    else border.setTexture(&borderTexture);

    player->draw(window);
    if (getStatus() == Game::NotStarted && !displayMaze) start();
    // Start ticking sound
    if (getCountdown() == 10 && sounds.getSound(Sounds::Tick).getStatus() == sf::SoundSource::Stopped) sounds.play(Sounds::Tick, 20.0f);
    window.display();
}

bool Game::playAgain()
{
    Message playagain("Play again?  (Y/N)", Fonts::Arial, 48);

    sf::Event event;
    statusText.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return false;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) return true;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) return false;
            else break;
        }
        window.draw(border);
        window.draw(door2);
        window.draw(arrow2);
        statusText.setString(string("Time ") + std::to_string(getCountdown()) + "\nBruises " + std::to_string(player->getBruises()) + "\nScore " + std::to_string(player->getScore()));
        window.draw(statusText);
        window.draw(titleText);
        player->draw_path(window);
        player->draw(window);
        playagain.draw(window);
        window.display();
    }

    return false;
}

void Game::start()
{
    Message temp("Press the Right Arrow key to start", Fonts::Arial);
    temp.draw(window);
    player->draw(window);
    window.draw(arrow1);
}

Wall::Type Game::jump()
{
    if (player->jumped())
    {
        sounds.play(Sounds::Fart);
        return Wall::None;
    }

    Message msg("Press an arrow key to indicate\n     the direction of the jump\n or Escape to cancel the jump", Fonts::Arial);

    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return Wall::None;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return jump(Player::Up);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return  jump(Player::Down);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return jump(Player::Left);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return jump(Player::Right);
            else break;
        }
        //msg.draw();
        msg.draw(window);
        window.display();
    }
    return Wall::None;
}

Wall::Type Game::jump(Player::Direction direction)
{
    sf::Vector2i location = player->getLocation();
    if ((location.y < 2 && direction == Player::Up) ||
            (location.x < 2 && direction == Player::Left) ||
            (location.y > 38 && direction == Player::Down) ||
            (location.x > 38 && direction == Player::Right))
        return Wall::None;
    sf::Vector2i newLocation(location);
    switch (direction)
    {
    case Player::Up:
        newLocation.y-=2;
        break;
    case Player::Down:
        newLocation.y+=2;
        break;
    case Player::Left:
        newLocation.x-=2;
        break;
    case Player::Right:
        newLocation.x+=2;
    default:
        ;
    }
    player->setJumped();
    player->decrementCountdown(3);
    player->incrementBruises();
    player->decrementScore();
    return player->processMove(newLocation);
}

bool Game::flash()
{
    if (!player->flashed())
    {
        sf::Clock clock;
        int elapsedTime;
        toggleDisplayMaze();
        while (window.isOpen())
        {
            elapsedTime = clock.getElapsedTime().asMilliseconds();
            if (elapsedTime > 1000.0f) break;
            draw_and_display();
        }
        toggleDisplayMaze();
        if (status == Active)
        {
            player->setFlashed();
            player->incrementBruises();
            grid->AddARandomWall();
            player->decrementCountdown(3);
            player->decrementScore();
            player->incrementBruises();
            bounce();
        }
        return true;
    }
    sounds.play(Sounds::Fart);
    return false;
}
