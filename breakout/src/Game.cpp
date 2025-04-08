#include <cmath>
#include <string>
#include <sstream>
using namespace std;

//#include "SoundEffect.h"
#include "Game.h"
#include "proto.h"
#include "RandomTiles.h"
#include "Rainbow.h"
#include "Crusher.h"
#include "TwoBalls.h"
#include "FallingTiles.h"
#include "Tiles150.h"

Game::Game(sf::RenderWindow& wnd, int number, int balls, int time_remaining)
    : window(wnd), gameNumber(number), numBalls(balls), timeRemaining(time_remaining),
      gameWindow(GameWindowSize), highScores(new HighScores(gameNumber)), ballsLeft(new sf::CircleShape[balls]), ballsLeftText("Balls Left", font, 24),
      timeRemainingText("", font, 24)
{
    ball[1] = nullptr;
    font.loadFromFile(ResourcePath + "Arial.ttf");
    // Game Name Text
    gameNameText.setFont(font);
    gameNameText.setString(GameName[number]);
    gameNameText.setFillColor(sf::Color(sf::Color::Yellow));
    sf::FloatRect textRect = gameNameText.getLocalBounds();
    gameNameText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    gameNameText.setPosition(950.0f,70.0f);

    scoreText.setString("Score 0");
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(150,150,250));
    scoreText.setPosition(900.0f,140.0f);

    timeRemainingText.setFillColor(sf::Color(250,150,150));
    timeRemainingText.setPosition(860.0f,300.0f);

    for (int i = 0; i < balls; i++)
    {
        ballsLeft[i].setRadius(10.0f);
        ballsLeft[i].setFillColor(sf::Color::White);
        ballsLeft[i].setPosition(sf::Vector2f(900.0f + i * 30.f - 4.0f * balls, 260.f));
    }

    ballsLeftText.setFillColor(sf::Color(150,250,150));
    ballsLeftText.setPosition(900.0f,210.0f);

    gameWindow.setFillColor(sf::Color::Black);
    gameWindow.setOutlineColor(sf::Color::Blue);
    gameWindow.setOutlineThickness(20.0f);
    gameWindow.setPosition(GameBorderWidth,GameBorderWidth);
    HSfont.loadFromFile(ResourcePath + "CourierNew.ttf");
    static std::ostringstream sout;
    sout.str("");
    sout << *highScores;
    highScoresTB = new TextBox(sout.str(), HSfont, 16, sf::Color::White, sf::Vector2f(960.0f,550.0f));
}

Game::~Game()
{
    delete tiles;
    tiles = nullptr;
    delete ball[0];
    ball[0] = nullptr;
    if (ball[1]) delete ball[1];
    ball[1] = nullptr;
    delete paddle;
    paddle = nullptr;
    delete highScores;
    highScores = nullptr;
    delete highScoresTB;
    highScoresTB = nullptr;
}

Paddle* Game::getPaddle()
{
    return paddle;
}

Ball*& Game::getBall(int ballNo)
{
    return ball[ballNo];
}

Tiles* Game::getTiles()
{
    return tiles;
}

std::string Game::getName() const
{
    return GameName[gameNumber];
}

sf::RectangleShape& Game::getGameWindow()
{
    return gameWindow;
}

int Game::getNumTiles() const
{
    return numTiles;
}

int Game::getNumBalls() const
{
    return numBalls;
}

int Game::getTimeRemaining() const
{
    return timeRemaining;
}

Game::GameStatus Game::getStatus() const
{
    return status;
}

sf::Vector2f Game::centerOfGameWindow() const
{
    float yOffset = 0.0f;
    // Move center down for Crusher game or 150 Tiles game
    if (gameNumber == 4 or gameNumber == 9) yOffset = 175.0f;
    sf::FloatRect globalRect = gameWindow.getGlobalBounds();
    sf::FloatRect localRect = gameWindow.getLocalBounds();
    sf::Vector2f center = sf::Vector2f(globalRect.top + localRect.width/2.0f, globalRect.left + localRect.height/2.0f + yOffset);
    return center;
}

int Game::getScore() const
{
    return score;
}

Game::Ball2Status Game::getBall2Status() const
{
    return ball2Status;
}

int Game::getGameNumber() const
{
    return gameNumber;
}

HighScores* Game::getHighScores() const
{
    return highScores;
}

float Game::paddleHeight() const
{
    return paddle->getPosition().y;
}

float Game::ballHeight(int ballNo) const
{
    return ball[ballNo]->getPosition().y;
}

float Game::getBallSpeed(int ballNo)
{
    return ball[ballNo]->getSpeed();
}

TextBox* Game::getHighScoresTB()
{
    return highScoresTB;
}

float Game::ballXPosition(int ballNo) const
{
    return ball[ballNo]->getPosition().x;
}

bool Game::ball2IsActive() const
{
    return ball2Status == Ball2Status::Active;
}

sf::Text& Game::getScoreText()
{
    scoreText.setString("Score " + std::to_string(score));
    return scoreText;
}

sf::Text& Game::getBallsLeftText()
{
    return ballsLeftText;
}

void Game::incrementScore(int value)
{
    score += value;
    scoreText.setString("Score " + std::to_string(score));
}

void Game::decrementNumBalls()
{
    numBalls--;
}

///// Setters  /////

void Game::setStatus(Game::GameStatus status_)
{
    status = status_;
}

void Game::decrementTimeRemaining()
{
    timeRemaining--;
    if (timeRemaining == 0) status = GameStatus::OutOfTime;
}

void Game::update(sf::Time dt)
{
    paddle->update(dt);
    ball[0]->update(dt);
}

void Game::updateTimer()
{
    if (timeRemaining != INT_MAX)
    {
        if (timerClock.getElapsedTime().asSeconds() >= 1.0f)
        {
            decrementTimeRemaining();
            timerClock.restart();
        }
    }
}

void Game::updateBall2(sf::Time dt)
{
    const float RPD = 0.0174533f;   // Radians Per Degree

    sf::Vector2f ball2Position = ball[1]->getPosition();
    float speed = ball[1]->getSpeed();
    float angle = ball[1]->getAngle();

    if (ball[1]->getDirection() == Ball::Direction::Up)
    {
        ball[1]->setPosition(sf::Vector2f(ball2Position.x + speed * dt.asSeconds() * std::sin(RPD*angle), ball2Position.y - speed * dt.asSeconds() *std::cos(RPD*angle)));
    }
    else  // ball direction is down
    {
        ball[1]->setPosition(sf::Vector2f(ball2Position.x + speed * dt.asSeconds() * std::sin(RPD*angle), ball2Position.y + speed * dt.asSeconds() * std::cos(RPD*angle)));
    }
    if (ball2LeavesInnerRect())
    {
        ball[1]->setFillColor(sf::Color::Magenta);
        ball2Status = Ball2Status::Active;
    }
}

void Game::manageBall(SoundEffect& soundEffect, sf::Text& message)
{
    int tileValue;
    // Ball hits a wall
    if (ball[0]->hitTheWall() || (gameNumber == 7 && ball[1]->hitTheWall()))
    {
        soundEffect[SoundEffect::BallHitWall].play();
    }
    // ball hits a tile
    if ((tileValue = hitATile()) > 0 || (gameNumber == 7 && (tileValue = hitATile(1)) > 0))
    {
        soundEffect[SoundEffect::BallHitTile].play();
        incrementScore(tileValue);

        if (numTiles == 0 or tileValue == 100)
        {
            status = Game::GameStatus::Win;
            message.setCharacterSize(48);
            message.setFillColor(sf::Color(20,200,20));
            soundEffect[SoundEffect::EndOfGame].play();
            message.setString("     You win!!!!!!!!!!!!");
            window.clear();
            drawGameObjects();
            drawCenteredText(message, window);
            window.display();
            sf::sleep(sf::Time(sf::seconds(5.0f)));
        }
    }
}


int Game::hitATile(int ballNo)
{
    static int LoopCounter = 0;
    if (gameNumber == 6)
    {
        if (LoopCounter) LoopCounter--;
        else ball[ballNo]->setFillColor(Yellow);
    }
    bool hit = false;

    Tile* tilePtr = nullptr;
    float angle;

    for (int row = 0; row < tiles->getNumRows(); row++)
    {
        for (int col = 0; col < tiles->getNumCols(); col++)
        {
            tilePtr = tiles->getTile(row,col);
            if (!tilePtr) continue;
            SideOfTile side = hitTileSide(tilePtr, ballNo);
            if (side == SideOfTile::None) continue;
            hit = true;

            switch (side)
            {
            case SideOfTile::Bottom:
                ball[ballNo]->setDirection(Ball::Direction::Down);
                ball[ballNo]->moveDown(3);
                break;
            case SideOfTile::Top:
                ball[ballNo]->setDirection(Ball::Direction::Up);
                ball[ballNo]->moveUp(3);
                break;
            case SideOfTile::Right:
                ball[ballNo]->moveRight(5.0f);
                angle = ball[ballNo]->getAngle();
                if (ballNo == 0 && fabs(angle) < 30.0) angle = 1.5f * angle;
                ball[ballNo]->setAngle(-angle);
                break;
            case SideOfTile::Left:
                ball[ballNo]->moveLeft(5.0f);
                angle = ball[ballNo]->getAngle();
                if (ballNo == 0 && fabs(angle) < 30.0) angle = 1.5f * angle;
                ball[ballNo]->setAngle(-angle);
                break;
            default:
                ;
            }

            if (hit)    // Ball has hit a tile
            {
                return processHitTile(tilePtr, ballNo);
            }
        }
    }
    return -1;
}

Game::SideOfTile Game::hitTileSide(const Tile* tile, int ballNo) const
{
    float ballX, ballY;

    ballX= ball[ballNo]->getPosition().x;
    ballY = ball[ballNo]->getPosition().y;

    if (ball[ballNo]->getDirection() == Ball::Direction::Up   && ball[ballNo]->top() < tile->bottom() && ballY > tile->top() && ballX >= tile->left() && ballX <= tile->right())
        return SideOfTile::Bottom;
    if (ball[ballNo]->getDirection() == Ball::Direction::Down && ball[ballNo]->bottom() >= tile->top() && ball[ballNo]->top() <= tile->bottom() && ball[ballNo]->top() < tile->bottom() && ballX >= tile->left() && ballX <= tile->right())
        return SideOfTile::Top;
    if (ball[ballNo]->right() >= tile->left() && ball[ballNo]->left() <= tile->left() && ballY >= tile->top() && ballY <= tile->bottom())
        return SideOfTile::Left;
    if (ball[ballNo]->left() <= tile->right() && ball[ballNo]->right() >= tile->right() && ballY >= tile->top() && ballY <= tile->bottom())
        return SideOfTile::Right;
    return SideOfTile::None;
}

void Game::drawBallsLeft()
{
    window.draw(ballsLeftText);
    for (int i = 0; i < numBalls; i++) window.draw(ballsLeft[i]);
}

void Game::drawHighScores()
{
    highScoresTB->drawTB(window);
}

sf::Text& Game::getTimeRemainingText()
{
    timeRemainingText.setString("Time Remaining " + std::to_string(timeRemaining));
    return timeRemainingText;
}

void Game::drawGameObjects()
{
    window.draw(gameNameText);
    window.draw(scoreText);
    drawHighScores();
    if (timeRemaining != INT_MAX) window.draw(getTimeRemainingText());
    drawBallsLeft();
    window.draw(gameWindow);
    window.draw(*paddle);               // draw paddle
    window.draw(*ball[0]);
    if (ball[1]) window.draw(*ball[1]);
    tiles->draw(window);                  // draw tiles
}

bool Game::paddleHitsBall(int ballNo)
{
    if (ball[ballNo]->getDirection() == Ball::Direction::Up) return false;
    if (ball[ballNo]->bottom() < paddle->getPosition().y) return false;
    if ((paddle->left() - ball[ballNo]->right() < 1.0f) && (ball[ballNo]->left() - paddle->right() < 1.0f))
    {
        float adjustment;
        float diff = ball[ballNo]->getPosition().x - paddle->getPosition().x;
        float pct = fabs(diff / (paddle->getSize().x / 2));

        float newangle;

        if (pct < 0.6f) adjustment = static_cast<float>(rand() % 9 - 4);
        else adjustment = pct/4.f * ball[ballNo]->getAngle();
        newangle = ball[ballNo]->getAngle() + adjustment;
        if (newangle > 70) newangle = 70;
        if (newangle < -70) newangle = -70;
        ball[ballNo]->setAngle(newangle);
        ball[ballNo]->setDirection(Ball::Direction::Up);
        return true;
    }
    return false;
}

bool Game::paddleMissesBall(int ballNo)
{
    if ((ball[ballNo]->getDirection() == Ball::Direction::Down) and (ball[ballNo]->getPosition().y >= paddle->getPosition().y) and
            ((ballXPosition(ballNo) + 1.0f < paddle->left()) || (ballXPosition(ballNo) - 1.0f  >  paddle->right())))
    {
        if (gameNumber == 5)        // Rainbow
        {
            Rainbow* rainbowPtr = dynamic_cast<Rainbow*>(this);
            rainbowPtr -> decrementColor();
            ball[ballNo]->speedUp();     // 5%
        }

        return true;
    }
    return false;
}

bool Game::paddleHitsWall()
{
    sf::Vector2f paddlePos = paddle->getPosition();
    if (paddle->right() >= rightSideOfWindow() - GameBorderWidth)
    {
        paddlePos.x -= 3.0f;
        paddle->setPosition(paddlePos);
        return true;
    }
    if (paddle->left() <= leftSideOfWindow() + GameBorderWidth)
    {
        paddlePos.x += 3.0f;
        paddle->setPosition(paddlePos);
        return true;
    }
    return false;
}

float Game::rightSideOfWindow() const
{
    sf::FloatRect rect = gameWindow.getGlobalBounds();
    return rect.left + rect.width;
}

float Game::leftSideOfWindow() const
{
    sf::FloatRect rect = gameWindow.getGlobalBounds();
    return rect.left;
}

bool Game::ball2LeavesInnerRect()
{
    float ballXPos = ball[1]->getPosition().x;
    float ballYPos = ball[1]->getPosition().y;
    if (ballXPos < innerRect.left ||
            ballXPos > innerRect.left + innerRect.width ||
            ballYPos + ball[1]->getRadius() < innerRect.top - 2.f ||
            ballYPos > innerRect.top + innerRect.height + 1.f)
    {
        return true;
    }
    return false;
}

void Game::move2BallsToStartPosition()
{
    ball[0]->setPosition(sf::Vector2f(BallStartPosition.x - 8.f, BallStartPosition.y));
    ball[1]->setPosition(sf::Vector2f(BallStartPosition.x + 8.f, BallStartPosition.y));
    ball[0]->setDirection(Ball::Direction::Up);
    ball[1]->setDirection(Ball::Direction::Up);
    ball[0]->setAngle((rand()%10 + 5.f));
    ball[1]->setAngle(-(rand()%10 + 5.f));
}
