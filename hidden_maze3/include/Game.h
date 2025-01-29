#ifndef GAME_H
#define GAME_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grid.h"
#include "Player.h"
#include "Sounds.h"
#include "HighScores.h"
#include "Constants.h"
#include "Fonts.h"

class Game
{
public:
    enum GameStatus {NotStarted, Active, Paused, Win, Loss, GameOver};

    Game(sf::RenderWindow& wind, /*Fonts& fonts,*/ const std::string& name);
    ~Game();
    void refresh(const std::string& name_);


    void draw_and_display();

    // getters
    sf::RenderWindow& getWindow();
    sf::RectangleShape& getBorder();
    Grid* getGrid();
    Player* getPlayer();
    int getScore() const;
    int getBruises() const;
    Game::GameStatus getStatus() const;
    Sounds& getSounds();
    int getCountdown() const;

    //setters
    void setStatus(Game::GameStatus status_);
    void toggleDisplayMaze();
    void incrementBruises();
    void decrementScore();

    bool flash(float time = 1000.0f);
    Wall::Type jump();
    Wall::Type jump(Player::Direction direction);
    void start();
    bool playAgain();
    void bounce();
    void move(Player::Direction direction);
    bool bomb();
    bool light();

private:
    sf::RenderWindow& window;
    GameStatus status = NotStarted;
    Sounds sounds;
    sf::RectangleShape border;
    sf::RectangleShape door1;
    sf::RectangleShape door2;
    sf::Texture arrowTexture;
    sf::Texture borderTexture;
    sf::Sprite arrow1;
    sf::Sprite arrow2;
    sf::Text titleText;
    sf::Text statusText;

    bool displayMaze;
    Grid* grid = nullptr;
    Player* player = nullptr;
    sf::RectangleShape timeBar;
    const float timeBarStartWidth = 720;
    const float timeBarHeight = 25;
};

#endif // Game_H
