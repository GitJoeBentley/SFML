#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "constants.h"
#include "Ball.h"
#include "Paddle.h"
#include "Tiles.h"
#include "SoundEffect.h"
#include "HighScores.h"
#include "Game.h"
#include "BasicGame.h"
#include "EasyGame.h"
#include "OneRedTile.h"
#include "Button.h"
#include "ButtonBox.h"
#include "TextBox.h"
#include "Message.h"

using std::cout;
using std::endl;
using sf::Keyboard;

enum class GameSelection { Exit, Same, New};

bool hasJoystick();
char getKey();
int start(sf::RenderWindow& window, sf::Font& font);
GameSelection playAgain(sf::RenderWindow& window, sf::Font& font);
void displayGameDescription(size_t gameNumber, sf::RenderWindow& window, sf::Font& font);
bool buttonIsClicked(sf::RectangleShape& button, sf::Vector2f mousePosition);
void drawCenteredText(sf::Text& text, sf::RenderWindow& window);
std::string getName(sf::RenderWindow& window, sf::Font& font);


// TODO (Joe#1#): replace this file with main.cpp ...
//

int main ()
{
    srand(static_cast<unsigned>(time(0)));

    bool joyStickConnected = hasJoystick();

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "", sf::Style::Close);
    window.setTitle(sf::String("Joe's Breakout"));

    Game* game;
    HighScores* highScores;
    TextBox* highScoresTB;
    std::ostringstream sout;

    GameSelection gameSelection = GameSelection::New;

    //GAME CLOCK & TIMER
    sf::Clock clock;
    sf::Time dt;
    sf::Clock timerClock;
    int timer = 0;
    int gameSelected;      // Player's choice of games

    // Fonts
    sf::Font font;
    font.loadFromFile(ResourcesPath + "Arial.ttf");
    sf::Font HSfont;
    HSfont.loadFromFile(ResourcesPath + "CourierNew.ttf");

    // Texts
    sf::Text message("", font);
    int tileValue = 0;

    // Sound effects
    SoundEffect soundEffect;

    sf::Vector2f joystick = sf::Vector2f(0.f,0.f);

    sf::Event event;
    while (gameSelection != GameSelection::Exit)
    {
        message.setFillColor(sf::Color(10,220,250));
        message.setCharacterSize(24.0f);
        message.setStyle(sf::Text::Bold);
        if (!joyStickConnected) message.setString("Press the Space bar to begin");
        else message.setString("Press the Start button to begin");
        drawCenteredText(message, window);

        if (gameSelection == GameSelection::New)
        {
            // Set up the selected game
            gameSelected = start(window, font);
        }
        switch (gameSelected)
        {
        case -1:
            game->setStatus(Game::GameStatus::GameOver);
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
        default:
            ;
        }
        message.setPosition(game->getCenterOfGameWindow());

        // Update highscores
        highScores = new HighScores(gameSelected);
        sout.str("");
        sout << *highScores;
        highScoresTB = new TextBox(sout.str(), HSfont, 16, sf::Color::White, sf::Vector2f(950.0f,550.0f));
        highScoresTB->draw(window);

        //////////// The GAME loop
        while (game->getStatus() == Game::GameStatus::NotStarted || game->getStatus() == Game::GameStatus::Active)
        {
            if (joyStickConnected) sf::Joystick::update();
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    game->setStatus(Game::GameStatus::GameOver);
                    window.close();
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    game->setStatus(Game::GameStatus::GameOver);
                    window.close();
                }

                if (Keyboard::isKeyPressed(Keyboard::X)) window.close();
                if (game->getStatus() == Game::GameStatus::NotStarted && (Keyboard::isKeyPressed(Keyboard::Space) || sf::Joystick::isButtonPressed(0,7)))
                {
                    game->getPaddle()->moveToStartPosition();
                    game->getBall()->moveToStartPosition();
                    game->setStatus(Game::GameStatus::Active);
                    clock.restart();
                    game->decrementNumBalls();
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
            }

            if (game->getStatus() == Game::GameStatus::Active)
            {
                dt = clock.restart();
                game->getPaddle()->update(dt);
                game->getBall()->update(dt);
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
                        message.setString("      Out of Time\n      Game Over");
                        game->setStatus(Game::GameStatus::Loss);
                        drawCenteredText(message, window);
                        window.display();
                        sf::sleep(sf::Time(sf::seconds(5.0f)));
                        break;
                    }
                }

                // ball hits a tile
                tileValue = game->hitATile();
                if (tileValue > 0)
                {
                    soundEffect[SoundEffect::BallHitTile].play();
                    game->incrementScore(tileValue);
                    game->getBall()->update(dt);   // this is a hack to move the ball after a tile hit

                    if (game->getNumTiles() == 0 or tileValue == 100)
                    {
                        game->setStatus(Game::GameStatus::Win);
                        message.setCharacterSize(48);
                        message.setFillColor(sf::Color(20,200,20));
                        soundEffect[SoundEffect::EndOfGame].play();
                        message.setString("     You win!!!!!!!!!!!!");
                        window.clear();

                        // Draw text and stuff outside of the game window
                        window.draw(game->getGameNameText());
                        window.draw(game->getScoreText());
                        highScoresTB->draw(window);
                        if (game->getTimeRemaining() != INT_MAX) window.draw(game->getTimeRemainingText());
                        game->drawBallsLeft();
                        // Draw stuff inside the game window
                        window.draw(game->getGameWindow());
                        window.draw(*(game->getPaddle()));               // draw paddle
                        window.draw(*(game->getBall()));
                        game->getTiles()->draw(window);                  // draw tiles
                        drawCenteredText(message, window);
                        window.display();
                        sf::sleep(sf::Time(sf::seconds(5.0f)));
                        break;
                    }
                    continue;
                }

                // ball hits the wall
                else if (game->getBall()->hitTheWall())
                    soundEffect[SoundEffect::BallHitWall].play();

                // Check for paddle hitting the right wall
                if (game->getPaddle()->getPosition().x > (GameWindowSize.x - game->getPaddle()->getSize().x/2.0f + GameBorderWidth))
                {
                    soundEffect[SoundEffect::PaddleHitWall].play();
                    game->getPaddle()->move(Paddle::Left, 1.0f);
                }

                // Check for paddle hitting the left wall
                else if (game->getPaddle()->getPosition().x < (game->getPaddle()->getSize().x/2.0f + GameBorderWidth))
                {
                    soundEffect[SoundEffect::PaddleHitWall].play();
                    game->getPaddle()->move(Paddle::Right, 1.0f);
                }

                // Check for paddle hitting the ball
                else if (game->getPaddle()->hitTheBall(game->getBall()))
                {
                    game->getBall()->update(dt);
                    soundEffect[SoundEffect::PaddleHitBall].play();
                }

                // paddle misses the ball
                else if (game->getBall()->getPosition().y >= GameWindowSize.y)
                {
                    if (game->getNumBalls() == 0)
                    {
                        message.setCharacterSize(48);
                        message.setFillColor(sf::Color(210,20,20));
                        message.setStyle(sf::Text::Bold);
                        soundEffect[SoundEffect::EndOfGame].play();
                        message.setString("Game Over");
                        game->setStatus(Game::GameStatus::Loss);
                        drawCenteredText(message, window);
                        game->drawBallsLeft();
                        window.display();
                        sf::sleep(sf::Time(sf::seconds(3.0f)));
                        break;
                    }
                    else
                    {
                        message.setCharacterSize(36);
                        message.setFillColor(sf::Color(10,220,50));
                        message.setString(std::to_string(game->getNumBalls()) + " ball" + (game->getNumBalls() > 1 ? "s" : "") + " to go.  Get ready ...");
                        game->decrementNumBalls();
                        soundEffect[static_cast<SoundEffect::SoundType>(SoundEffect::PaddleMissBall + (rand()%4))].play();
                        game->getPaddle()->moveToStartPosition();
                        game->getBall()->moveToStartPosition();
                        window.draw(game->getBallsLeftText());

                    }
                    drawCenteredText(message, window);
                    window.display();
                    sf::sleep(sf::Time(sf::seconds(3.0f)));
                    dt = clock.restart();
                }

                // no contact with paddle or ball
                else
                {
                }
            }          // if (gameStarted)

            // Update the window
            window.clear();
            // Draw text and stuff outside of the game window
            window.draw(game->getScoreText());
            highScoresTB->draw(window);
            if (game->getTimeRemaining() != INT_MAX) window.draw(game->getTimeRemainingText());

            game->drawBallsLeft();

            // Draw stuff inside the game window
            window.draw(game->getGameWindow());
            window.draw(game->getGameNameText());
            window.draw(*(game->getPaddle()));               // draw paddle
            window.draw(*(game->getBall()));
            game->getTiles()->draw(window);                  // draw tiles
            window.display();
        }  // End of the Game Loop

        // Record Game Score to High Scores?
        if (highScores->eligible(game->getScore()))
        {
            if (game->getScore() > highScores->getHightestScore())
                message.setString("          Congratulations!!!\nYou have the highest score!!!");
            else message.setString("              Congratulations!!!\nYou made the high scores leader board.");
            message.setCharacterSize(24);
            message.setFillColor(sf::Color(21,220,20));
            drawCenteredText(message, window);
            highScores->updateHighScores(Score(getName(window, font).c_str(),game->getScore(),time(0)));
            highScores->WriteHighScoresFile();
        }
        delete game;
        game = nullptr;
        delete highScores;
        highScores = nullptr;
        delete highScoresTB;
        highScoresTB = nullptr;

        //sf::sleep(sf::Time(sf::seconds(1.0f)));
        gameSelection = playAgain(window, font);
    }
    window.close();
}

int start(sf::RenderWindow& window, sf::Font& font)
{
    sf::Event event;
    sf::Vector2u RenderWindowSize = window.getSize();

    sf::Vector2f mousePos;
    sf::Vector2i mousePosI, saveMousePos;
    sf::Mouse mouse;
    sf::SoundBuffer ticBuffer;
    ticBuffer.loadFromFile(TicSoundFile);
    sf::Sound ticSound;
    ticSound.setBuffer(ticBuffer);
    ticSound.setVolume(100.0f);

    sf::Text title("Joe's Breakout Game", font, 30);
    title.setFillColor(sf::Color::Green);
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    std::vector<std::string> buttonLabels = {"Easy Game","Basic Game","One Red Tile","Crazy Ball","The Crusher","Random Tiles","Game#7"};
    size_t numButtons = buttonLabels.size();
    ButtonBox buttonBox(window, buttonLabels, "         Click on the game you want to play\nRight-mouse click for a description of the game", font, 20 );
    sf::FloatRect* butRect = new sf::FloatRect[numButtons];
    for (size_t i = 0; i < numButtons; i++)
        butRect[i] = buttonBox.getButton(i)->getGlobalBounds();

    title.setPosition(sf::Vector2f(RenderWindowSize.x/2.0f, 0.1 * RenderWindowSize.y));

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
                return -1;
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
        window.draw(title);
        buttonBox.draw();
        window.display();
    }

    return -1;
}

GameSelection playAgain(sf::RenderWindow& window, sf::Font& font)
{
    sf::Event event;
    sf::Vector2u RenderWindowSize = window.getSize();
    GameSelection choice[3] = {GameSelection::Same, GameSelection::New, GameSelection::Exit};

    sf::Vector2f mousePos;
    sf::Vector2i mousePosI, saveMousePos;
    sf::Mouse mouse;
// TODO (Joe#1#): Create file scope variables

    sf::SoundBuffer ticBuffer;
    ticBuffer.loadFromFile(TicSoundFile);
    sf::Sound ticSound;
    ticSound.setBuffer(ticBuffer);
    ticSound.setVolume(100.0f);

// TODO (Joe#1#): Move the title to a global variable ...
    sf::Text title("Joe's Breakout Game", font, 30);
    title.setFillColor(sf::Color::Green);
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    std::vector<std::string> buttonLabels = {"Same Game", "New Game","Exit"};
    size_t numButtons = buttonLabels.size();
    ButtonBox buttonBox(window, buttonLabels, "        Do you want to play\nthe same game or a new game?", font, 24 );
    sf::FloatRect* butRect = new sf::FloatRect[numButtons];
    for (size_t i = 0; i < numButtons; i++)
        butRect[i] = buttonBox.getButton(i)->getGlobalBounds();

    title.setPosition(sf::Vector2f(RenderWindowSize.x/2.0f, 0.1 * RenderWindowSize.y));

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
        window.draw(title);

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

    const std::string digit = "01234567";
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
                std::cout << buttRect.left << ' ' << buttRect.top << "   " << mousePos.x << ' ' << mousePos.y << std::endl;
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
    // sf::FloatRect rectangle = button.getGlobalBounds();
    return rectangle.contains(mousePosition);
}

void drawCenteredText(sf::Text& text, sf::RenderWindow& window)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    window.draw(text);
}

std::string getName(sf::RenderWindow& window, sf::Font& font)
{
    std::string name;

    sf::Event event;

    char input = ' ';

    std::string text = "Enter Your name for the High Scores Leaderboard ===> ";
    sf::Text namePrompt(text, font, 20);
    namePrompt.setPosition(window.getSize().x/10.0f, 0.6f * window.getSize().y);

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
