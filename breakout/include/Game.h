#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Tiles.h"
#include "Ball.h"
#include "Paddle.h"
#include "constants.h"
#include "HighScores.h"
#include "TextBox.h"



class Game
{
public:
    enum class GameStatus {NotStarted, Active, Paused, Win, OutOfTime, OutOfBalls, GameOver, Quit};
    enum class SideOfTile {None, Top, Bottom, Left, Right};
    enum class Ball2Status { Inactive, Active};

    Game(sf::RenderWindow& wnd, int gameNumber, int balls = 5, int time_remaining = INT_MAX);
    virtual ~Game();
    virtual void setup() = 0;
    Game::GameStatus getStatus() const;
    std::string getName() const;
    sf::RectangleShape& getGameWindow();
    sf::Vector2f getCenterOfGameWindow() const;
    Paddle* getPaddle();
    Ball* getBall(int ballNo = 0);
    Tiles* getTiles();
    int getScore() const
    {
        return score;
    }
    int getNumTiles() const;
    int getNumBalls() const;
    int getTimeRemaining() const;
    void drawBallsLeft();
    void drawHighScores();
    Ball2Status getBall2Status() const
    {
        return ball2Status;
    }
    int getGameNumber() const
    {
        return gameNumber;
    }
    HighScores* getHighScores() const
    {
        return highScores;
    }
    float paddleHeight() const
    {
        return paddle->getPosition().y;
    }
    float ballHeight(int ballNo = 0) const
    {
        return ball[ballNo]->getPosition().y;
    }
    float rightSideOfWindow() const;
    float leftSideOfWindow() const;

    float topEdgeOfPaddle() const
    {
        return paddle->getPosition().y - paddle->getSize().y / 2.f;
    }
    float rightEdgeOfPaddle() const
    {
        return paddle->getPosition().x + paddle->getSize().x / 2.f;
    }
    float leftEdgeOfPaddle() const
    {
        return paddle->getPosition().x - paddle->getSize().x / 2.f;
    }
    float bottomEdgeOfBall(int ballNo = 0) const
    {
        return ball[ballNo]->getPosition().y + ball[ballNo]->getRadius();
    }
    float rightEdgeOfBall(int ballNo = 0) const
    {
        return ball[ballNo]->getPosition().x + ball[ballNo]->getRadius();
    }
    float leftEdgeOfBall(int ballNo = 0) const
    {
        return ball[ballNo]->getPosition().x - ball[ballNo]->getRadius();
    }
    float ballXPosition(int ballNo = 0) const
    {
        return ball[ballNo]->getPosition().x;
    }

    const sf::Text& getGameNameText() const
    {
        return gameNameText;
    }
    sf::Text& getScoreText()
    {
        scoreText.setString("Score " + std::to_string(score));
        return scoreText;
    }
    sf::Text& getBallsLeftText()
    {
        return ballsLeftText;
    }
    sf::Text& getTimeRemainingText();
    TextBox* getHighScoresTB();

    void incrementScore(int value = 1)
    {
        score += value;
        scoreText.setString("Score " + std::to_string(score));
    }
    void decrementNumBalls()
    {
        numBalls--;
    }
    void setStatus(Game::GameStatus status_);
    void decrementTimeRemaining();
    virtual int hitATile(int ballNo = 0);
    bool isCloseToATile(const Tile* tile) const;
    bool hitBottomOfTile(const Tile* tile) const;
    bool hitTopOfTile(const Tile* tile) const;
    bool hitLeftSideOfTile(const Tile* tile) const;
    bool hitRightSideOfTile(const Tile* tile) const;
    SideOfTile hitTileSide(const Tile* tile, int ballNo = 0) const;
    bool paddleHitsBall(int ballNo = 0);
    bool paddleMissesBall(int ballNo = 0);
    bool paddleHitsWall();
    void drawGameObjects();
    bool ball2LeavesInnerRect();
    bool ball2IsActive() const { return ball2Status == Ball2Status::Active;}

    void setBall2StatusActive ()
    {
        ball2Status = Ball2Status::Active;
    }
    void move2BallsToStartPosition();
protected:
    sf::RenderWindow& window;
    GameStatus status = GameStatus::NotStarted;
    int gameNumber;
    int numBalls;
    int timeRemaining;
    sf::RectangleShape gameWindow;
    Tiles* tiles;
    Ball* ball[2];
    Paddle* paddle;
    HighScores* highScores;
    TextBox* highScoresTB;
    int numTiles;
    int score = 0;
    sf::CircleShape* ballsLeft;
    sf::Font font;
    sf::Font HSfont;
    sf::Text gameNameText;
    sf::Text scoreText;
    sf::Text ballsLeftText;
    sf::Text timeRemainingText;
    int LoopCounter = 0;
    Ball2Status ball2Status = Ball2Status::Inactive;
    sf::FloatRect innerRect;
};

#endif // GAME_H
