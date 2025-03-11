#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Tiles.h"
#include "Ball.h"
#include "Paddle.h"
#include "constants.h"


class Game
{
public:
    enum class GameStatus {NotStarted, Active, Paused, Win, Loss, GameOver};
    enum class SideOfTile {None, Top, Bottom, Left, Right};

    Game(sf::RenderWindow& wnd, const std::string& name, int balls, float ballspeed, int time_remaining = INT_MAX);
    virtual ~Game();
    virtual void setup() = 0;
    Game::GameStatus getStatus() const;
    std::string getName() const;
    sf::RectangleShape& getGameWindow();
    sf::Vector2f getCenterOfGameWindow() const;
    Paddle* getPaddle();
    Ball* getBall();
    Tiles* getTiles();
    int getScore() const { return score; }
    int getNumTiles() const;
    int getNumBalls() const;
    int getTimeRemaining() const;
    void drawBallsLeft();

    const sf::Text& getGameNameText() const { return gameNameText; }
    sf::Text& getScoreText() { scoreText.setString("Score " + std::to_string(score)); return scoreText; }
    sf::Text& getBallsLeftText() { return ballsLeftText; }
    sf::Text& getTimeRemainingText();

    void incrementScore(int value = 1) { score += value; }
    void decrementNumBalls() { numBalls--; }
    void setStatus(Game::GameStatus status_);
    void decrementTimeRemaining();
    virtual int hitATile();
    bool isCloseToATile(const Tile* tile) const;
    bool hitBottomOfTile(const Tile* tile) const;
    bool hitTopOfTile(const Tile* tile) const;
    bool hitLeftSideOfTile(const Tile* tile) const;
    bool hitRightSideOfTile(const Tile* tile) const;
    SideOfTile hitTileSide(const Tile* tile) const;
    bool paddleHitsBall();
protected:
    sf::RenderWindow& window;
    GameStatus status = GameStatus::NotStarted;
    std::string name;
    int numBalls;
    float ballSpeed;
    int timeRemaining;
    sf::RectangleShape gameWindow;
    Tiles* tiles;
    Ball* ball;
    Paddle* paddle;
    int numTiles;
    int score = 0;
    sf::Font font;
    sf::Text gameNameText;
    sf::Text scoreText;
    sf::CircleShape* ballsLeft;
    sf::Text ballsLeftText;
    sf::Text timeRemainingText;
};

#endif // GAME_H
