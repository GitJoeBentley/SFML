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
using sf::Keyboard;

sf::Text* Title;

int main ()
{
    srand(static_cast<unsigned>(time(0)));

    bool joyStickConnected = hasJoystick();

    // Fonts
    sf::Font font;
    font.loadFromFile(ResourcesPath + "Arial.ttf");

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Joe's Breakout Game", sf::Style::Close);

    Game* game = nullptr;
    GameSelection gameSelection = GameSelection::New;

    //GAME CLOCK & TIMER
    sf::Clock clock;
    sf::Time dt;
    sf::Clock timerClock;
    int timer = 0;
    int gameSelected;      // Player's choice of games

    // Texts
    Title = new sf::Text("Joe's Breakout Game", font, 30);
    Title->setFillColor(sf::Color::Green);
    sf::FloatRect textRect = Title->getLocalBounds();
    Title->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    // Note: Title x-position adjusted (72.0f) for difference in RenderWindow size
    Title->setPosition(sf::Vector2f(RenderWindowSize.x/2.0f + 72.0f, 0.05f * RenderWindowSize.y));

    sf::Text message("", font);
    sf::Vector2f messagePos;

    int tileValue = 0;

    // Sound effects
    SoundEffect soundEffect;

    sf::Vector2f joystick = sf::Vector2f(0.f,0.f);

    sf::Event event;

    //CrazyBall* crazyBallGame = nullptr;
    TwoBalls* twoBalls = nullptr;
    Crusher* crusher = nullptr;
    //FallingTiles* fallingTiles = nullptr;

    while (gameSelection != GameSelection::Exit)
    {
        message.setFillColor(sf::Color(10,220,250));
        message.setCharacterSize(24);
        message.setStyle(sf::Text::Bold);
        drawCenteredText(message, window);

        if (gameSelection == GameSelection::New)
        {
            // Set up the selected game
            gameSelected = start(window, font);
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
            //crazyBallGame = dynamic_cast<CrazyBall*>(game);
            break;
        case 4:
            game = new Crusher(window);
            crusher = dynamic_cast<Crusher*>(game);
            break;
        case 5:
            game = new Rainbow(window);
            break;
        case 6:
            game = new RandomTiles(window);
            break;
        case 7:
            game = new TwoBalls(window);
            twoBalls = dynamic_cast<TwoBalls*>(game);
            break;
        case 8:
            game = new FallingTiles(window);
            //fallingTiles = dynamic_cast<FallingTiles*>(game);
            break;
        case 9:
            game = new Tiles150(window);
            //tiles150 = dynamic_cast<Tiles150*>(game);
            break;
        default:
            ;
        }

        if (game) message.setPosition(game->centerOfGameWindow());
        game->drawHighScores();

        //////////// The GAME loop
        while (game->getStatus() == Game::GameStatus::NotStarted || game->getStatus() == Game::GameStatus::Active)
        {
            if (joyStickConnected) sf::Joystick::update();
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    game->setStatus(Game::GameStatus::Quit);
                    window.close();
                    break;
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    game->setStatus(Game::GameStatus::Quit);
                    window.close();
                    break;
                }

                if (Keyboard::isKeyPressed(Keyboard::X)) window.close();
                if (Keyboard::isKeyPressed(Keyboard::P))
                {
                    if (game->getStatus() == Game::GameStatus::Paused)
                    {
                        game->setStatus(Game::GameStatus::Active);
                        break;
                    }
                    else
                    {
                        game->setStatus(Game::GameStatus::Paused);
                        break;
                    }
                }

                if (game->getStatus() == Game::GameStatus::NotStarted && (Keyboard::isKeyPressed(Keyboard::Space) || sf::Joystick::isButtonPressed(0,7)))
                {
                    game->setStatus(Game::GameStatus::Active);
                    clock.restart();
                    game->decrementNumBalls();
                    break;
                }

                if (joyStickConnected)
                {
                    joystick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
                }

                // Handle the pressing and releasing of the arrow keys
                if (Keyboard::isKeyPressed(Keyboard::Left) || joystick.x < -15.f)
                {
                    game->getPaddle()->move(Paddle::Left);
                }
                else if (Keyboard::isKeyPressed(Keyboard::Right) || joystick.x > 15.f)
                {
                    game->getPaddle()->move(Paddle::Right);
                }
                else
                {
                    game->getPaddle()->stop();
                }
                if (sf::Joystick::isButtonPressed(0,7)) game->setStatus(Game::GameStatus::Active);
                else if (sf::Joystick::isButtonPressed(0,0)) game->setStatus(Game::GameStatus::GameOver);
                else {};
            }   // end of the poll event loop

            // Start of Active Game loop
            if (game->getStatus() == Game::GameStatus::Active)
            {
                game->update(clock.restart());
                if (gameSelected == 8 && game->getStatus() == Game::GameStatus::TileHitsPaddle) break;
                if (gameSelected == 7 && game->getBall2Status() == Game::Ball2Status::Inactive && game->ball2LeavesInnerRect())
                {
                    soundEffect[SoundEffect::BallHitTile].play();
                    game->getBall(1)->setFillColor(sf::Color::Magenta);
                    game->setBall2StatusActive();
                }

                window.clear();
                game->drawGameObjects();
                window.display();

                // Out of time?
                if (game->getTimeRemaining() != INT_MAX)
                {
                    timer = static_cast<int> (timerClock.getElapsedTime().asSeconds());
                    if (timer > 0)
                    {
                        game->decrementTimeRemaining();
                        timerClock.restart();
                    }
                    if (game->getTimeRemaining() == 0)
                    {
                        game->setStatus(Game::GameStatus::OutOfTime);
                        break;
                    }
                }

                // Ball hits a wall
                if (game->getBall(0)->hitTheWall() || (gameSelected == 7 && game->getBall(1)->hitTheWall()))
                {
                    soundEffect[SoundEffect::BallHitWall].play();
                }
                // ball hits a tile
                if ((tileValue = game->hitATile()) > 0 || (twoBalls && (tileValue = game->hitATile(1)) > 0))
                {
                    soundEffect[SoundEffect::BallHitTile].play();
                    game->incrementScore(tileValue);
                    //game->getBall()->update(dt);   // this is a hack to move the ball after a tile hit

                    if (game->getNumTiles() == 0 or tileValue == 100)
                    {
                        game->setStatus(Game::GameStatus::Win);
                        message.setCharacterSize(48);
                        message.setFillColor(sf::Color(20,200,20));
                        soundEffect[SoundEffect::EndOfGame].play();
                        message.setString("     You win!!!!!!!!!!!!");
                        window.clear();
                        game->drawGameObjects();
                        // Draw text and stuff outside of the game window
                        drawCenteredText(message, window);
                        window.display();
                        sf::sleep(sf::Time(sf::seconds(5.0f)));
                        break;
                    }
                    continue;
                }
                // Paddle hits wall
                if (game->paddleHitsWall())
                {
                    soundEffect[SoundEffect::PaddleHitWall].play();
                }
                // Paddle hits ball?
                else if (game->paddleHitsBall() || (gameSelected == 7 && game->paddleHitsBall(1)))
                {
                    // Paddle hit the ball
                    //game->getBall()->update(dt);
                    soundEffect[SoundEffect::PaddleHitBall].play();
                }
                // Paddle misses ball?
                else if (game->paddleMissesBall() || (gameSelected == 7 && game->paddleMissesBall(1)))
                {
                    if (game->getNumBalls() == 0)
                    {
                        message.setCharacterSize(48);
                        message.setFillColor(sf::Color(210,20,20));
                        message.setStyle(sf::Text::Bold);
                        soundEffect[SoundEffect::EndOfGame].play();
                        game->setStatus(Game::GameStatus::OutOfBalls);
                        break;
                    }
                    else
                    {
                        message.setCharacterSize(36);
                        message.setFillColor(sf::Color(10,220,50));
                        message.setString(std::to_string(game->getNumBalls()) + " ball" + (game->getNumBalls() > 1 ? "s" : "") + " to go.  Get ready ...");
                        game->decrementNumBalls();
                        soundEffect[static_cast<SoundEffect::SoundType>(SoundEffect::PaddleMissBall + (rand()%4))].play();
                        game->drawGameObjects();
                        drawCenteredText(message, window);
                        window.draw(game->getBallsLeftText());
                        window.display();
                        sf::sleep(sf::Time(sf::seconds(3.0f)));
                        if (crusher) crusher->crush();
                        game->getPaddle()->moveToStartPosition();
                        if (gameSelected == 7 && game->ball2IsActive()) game->move2BallsToStartPosition();
                        else game->getBall()->moveToStartPosition();
                        clock.restart();
                    }
                }
                // No contact with ball or paddle
                else
                {
                }

            } // End of if Active game

            window.clear();
            game->drawGameObjects();
            if (game->getStatus() == Game::GameStatus::NotStarted)
            {
                message.setString("Press the Start button or the Space bar to begin");
                drawCenteredText(message, window);
            }
            window.display();
        }  // End of the Game Loop

        TextBox* tb;
        std::string statement;
        bool hasAHighScore = false;

        // Record Game Score to High Scores?
        if (game->getHighScores()->eligible(game->getScore()))
        {
            hasAHighScore = true;
            if (game->getScore() > game->getHighScores()->getHightestScore())
                statement = "             Congratulations!!!\n    You have the highest score!!!";
            else statement = "             Congratulations!!!\n     You made the leader board  ";
        }
        else
        {
            switch (game->getStatus())
            {
            case Game::GameStatus::Quit:
                statement = "OK ... Bye Bye";
                break;
            case Game::GameStatus::OutOfTime:
                statement = "      Out of Time\n       You Lose";
                break;
            case Game::GameStatus::OutOfBalls:
                statement = "      Out of Balls\n      You Lose";
                break;
            case Game::GameStatus::TileHitsPaddle:
                statement = "A falling tile hit the paddle\n         You Lose";
                break;
            case Game::GameStatus::Win:
                statement = "\n     You win!!!!!!!!!!!!\n";
            default:
                ;
            }
        }
        game->drawGameObjects();
        tb = new TextBox(statement, font, 30, sf::Color::Magenta,game->centerOfGameWindow());
        tb->drawTB(window);
        window.display();
        sf::sleep(sf::Time(sf::seconds(5.0f)));
        delete tb;
        tb = nullptr;
        if (hasAHighScore)
        {
            game->getHighScores()->updateHighScores(Score(getName(window, font, game).c_str(),game->getScore(),time(0)));
            game->getHighScores()->WriteHighScoresFile();
        }

        //crazyBallGame = nullptr;
        twoBalls = nullptr;
        crusher = nullptr;
        if (game) delete game;
        game = nullptr;

        gameSelection = playAgain(window, font);
    }
    window.close();
}

int start(sf::RenderWindow& window, sf::Font& font)
{
    sf::Event event;

    sf::Vector2f mousePos;
    sf::Vector2i mousePosI, saveMousePos;
    sf::Mouse mouse;
    sf::SoundBuffer ticBuffer;
    ticBuffer.loadFromFile(TicSoundFile);
    sf::Sound ticSound;
    ticSound.setBuffer(ticBuffer);
    ticSound.setVolume(100.0f);

    size_t numButtons = GameName.size();
    ButtonBox buttonBox(window, GameName, "         Click on the game you want to play\nRight-mouse click for a description of the game", font, 20 );
    sf::FloatRect* butRect = new sf::FloatRect[numButtons];
    for (size_t i = 0; i < numButtons; i++)
        butRect[i] = buttonBox.getButton(i)->getGlobalBounds();

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            mousePosI = mouse.getPosition(window);
            mousePos.x = static_cast<float>(mousePosI.x);
            mousePos.y = static_cast<float>(mousePosI.y);
            for (size_t i = 0; i < numButtons; i++)
            {
                if (butRect[i].contains(mousePos))
                {
                    buttonBox.getButton(i)->highlight();
                    ticSound.play();
                }
                else buttonBox.getButton(i)->normal();
            }
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                exit(0);
            case sf::Event::MouseButtonPressed:

                for (size_t i = 0; i < numButtons; i++)
                {
                    if (butRect[i].contains(mousePos))
                    {
                        buttonBox.getButton(i)->highlight();
                        ticSound.play();
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            delete [] butRect;
                            butRect = nullptr;
                            return i;
                        }
                        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            saveMousePos = mouse.getPosition();
                            displayGameDescription(i, window, font);
                            mouse.setPosition(saveMousePos);
                            break;
                        }
                    }
                }

            default:
                ;
            }
        }
        window.clear();
        window.draw(*Title);
        buttonBox.draw();
        window.display();
    }

    return -1;
}

GameSelection playAgain(sf::RenderWindow& window, sf::Font& font)
{
    sf::Event event;
    GameSelection choice[3] = {GameSelection::Same, GameSelection::New, GameSelection::Exit};

    sf::Vector2f mousePos;
    sf::Vector2i mousePosI, saveMousePos;
    sf::Mouse mouse;

    sf::SoundBuffer ticBuffer;
    ticBuffer.loadFromFile(TicSoundFile);
    sf::Sound ticSound;
    ticSound.setBuffer(ticBuffer);
    ticSound.setVolume(100.0f);

    std::vector<std::string> buttonLabels = {"Same Game", "New Game","Exit"};
    size_t numButtons = buttonLabels.size();
    ButtonBox buttonBox(window, buttonLabels, "        Do you want to play\nthe same game or a new game?", font, 24 );
    sf::FloatRect* butRect = new sf::FloatRect[numButtons];
    for (size_t i = 0; i < numButtons; i++)
        butRect[i] = buttonBox.getButton(i)->getGlobalBounds();

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            mousePosI = mouse.getPosition(window);
            mousePos.x = static_cast<float>(mousePosI.x);
            mousePos.y = static_cast<float>(mousePosI.y);
            for (size_t i = 0; i < numButtons; i++)
            {
                if (butRect[i].contains(mousePos))
                {
                    buttonBox.getButton(i)->highlight();
                    ticSound.play();
                }
                else buttonBox.getButton(i)->normal();
            }
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                return GameSelection::Exit;
            case sf::Event::MouseButtonPressed:

                for (size_t i = 0; i < numButtons; i++)
                {
                    if (butRect[i].contains(mousePos))
                    {
                        buttonBox.getButton(i)->highlight();
                        ticSound.play();
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            delete [] butRect;
                            butRect = nullptr;
                            return choice[i];
                        }
                        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            saveMousePos = mouse.getPosition();
                            displayGameDescription(i, window, font);
                            mouse.setPosition(saveMousePos);
                            break;
                        }
                    }
                }

            default:
                ;
            }
        }
        window.clear();
        window.draw(*Title);

        buttonBox.draw();
        window.display();
    }

    return GameSelection::Exit;
}

bool hasJoystick()
{
    sf::Joystick::update();
    return sf::Joystick::isConnected(0);
}

// Determine what key is pressed
char getKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return  'a';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        return  'b';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        return  'c';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return  'd';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        return  'e';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        return  'f';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        return  'g';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        return  'h';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        return  'i';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        return  'j';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        return  'k';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        return  'l';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        return  'm';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        return  'n';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        return  'o';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        return  'p';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        return  'q';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        return  'r';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return  's';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        return  't';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
        return  'u';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
        return  'v';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return  'w';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        return  'x';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        return  'y';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        return  'z';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return  ' ';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        return  '\n';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
        return  '\b';
    return ' ';
}

void displayGameDescription(size_t gameNumber, sf::RenderWindow& window, sf::Font& font)
{
    sf::Vector2u RenderWindowSize = window.getSize();

    const std::string digit = "0123456789";
    const std::string filename = ResourcesPath + "gamedescription" + digit[gameNumber] + ".txt";
    std::string text, buffer;

    std::ifstream fin(filename.c_str());
    if (!fin)
    {
        std::cout << "Cannot open game description file" << std::endl;
        return;
    }

    while (getline(fin, buffer))
    {
        text += buffer += '\n';
    }

    Message description(text, font, 20, sf::Vector2f(RenderWindowSize.x/2.0f, RenderWindowSize.y/ 2.0f));
    sf::Event event;
    sf::Mouse mouse;
    sf::Vector2f mousePos;
    sf::Vector2i mousePosI;
    sf::FloatRect buttRect = description.getContinueButtonPosition();
    while (window.isOpen())
    {
        mousePosI = mouse.getPosition(window);
        mousePos.x = static_cast<float>(mousePosI.x);
        mousePos.y = static_cast<float>(mousePosI.y);
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (buttRect.contains(mousePos))
                {
                    return;
                }
            default:
                ;
            }
        }
        description.draw(window);
        window.display();
    }
}

bool buttonIsClicked(sf::RectangleShape& button, sf::Vector2f mousePosition)
{

    sf::FloatRect rectangle = button.getGlobalBounds();
    return rectangle.contains(mousePosition);
}

void drawCenteredText(sf::Text& text, sf::RenderWindow& window)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    window.draw(text);
}

std::string getName(sf::RenderWindow& window, sf::Font& font, Game* game)
{
    std::string name;

    sf::Event event;

    char input = ' ';

    std::string text = "Enter Your name for the High Scores Leaderboard ===> ";
    sf::Text namePrompt(text, font, 20);
    namePrompt.setPosition(window.getSize().x/10.0f, 0.75f * window.getSize().y);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                input = getKey();
                if ((input >= 'a' && input <= 'z')||(input >= 'A' && input <= 'Z')||input == ' ')
                {
                    name += input;
                }
                if (input == '\b') // backspace
                {
                    name = "";
                    text = "Enter Your name for the High Scores Leaderboard ===> ";
                }
                break;
            default:
                ;
            }
        }
        window.clear();
        namePrompt.setString((text+name+'_').c_str());
        game->drawGameObjects();
        window.draw(namePrompt);
        window.display();
        if (isspace(name[0]))
            name = name.substr(1);  // remove leading space from name
        name[0] = toupper(name[0]);

        if (input == '\n')
        {
            window.clear();
            return name;
        }
    }
    return name;
}

int getColorIndex(sf::Color color)
{
    for (int i = 0; i < 7; i++)
        if (color == RainbowColor[i]) return i;
    return -1;
}
