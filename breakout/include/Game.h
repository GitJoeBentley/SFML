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
    enum class GameStatus {NotStarted, Active, Paused, Win, OutOfTime, OutOfBalls, TileHitsPaddle, GameOver, Quit};
    enum class SideOfTile {None, Top, Bottom, Left, Right};
    enum class Ball2Status { Inactive, Active};

    Game(sf::RenderWindow& wnd, int gameNumber, int balls = 5, int time_remaining = INT_MAX);
    virtual ~Game();
    virtual void setup() = 0;
    virtual void update(sf::Time dt);
    virtual int processHitTile(Tile* ptrTile, int ballNo = 0) = 0;

    // getters
    Game::GameStatus getStatus() const;
    std::string getName() const;
    sf::Vector2f centerOfGameWindow() const;
    int getScore() const;
    int getNumTiles() const;
    int getNumBalls() const;
    int getTimeRemaining() const;
    Ball2Status getBall2Status() const;
    int getGameNumber() const;
    HighScores* getHighScores() const;
    float paddleHeight() const;
    float rightSideOfWindow() const;
    float leftSideOfWindow() const;
    bool ball2IsActive() const;
    float ballHeight(int ballNo = 0) const;
    float ballXPosition(int ballNo = 0) const;
    bool ball2LeavesInnerRect() const;

    // non-const accessors
    sf::RectangleShape& getGameWindow();
    sf::Text& getTimeRemainingText();
    TextBox* getHighScoresTB();
    sf::Text& getScoreText();
    sf::Text& getBallsLeftText();
    Paddle* getPaddle();
    Ball*& getBall(int ballNo = 0);
    float getBallSpeed(int ballNo = 0);
    Tiles* getTiles();

    void updateBall2(sf::Time dt);
    void drawBallsLeft();
    void drawHighScores();
    void incrementScore(int value = 1);
    void decrementNumBalls();
    void setStatus(Game::GameStatus status_);
    void decrementTimeRemaining();
    int hitATile(int ballNo = 0);
    bool paddleHitsBall(int ballNo = 0);
    bool paddleMissesBall(int ballNo = 0);
    bool paddleHitsWall();
    void drawGameObjects();
    void setBall2StatusActive ();
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
    int numTiles;       // initialized by subclass setup function
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

private:
    SideOfTile hitTileSide(const Tile* tile, int ballNo = 0) const;
};

#endif // GAME_H
