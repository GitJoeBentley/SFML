#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grid.h"
#include "Game.h"
#include "HighScores.h"
#include "Sounds.h"
#include "Message.h"
#include "Fonts.h"
using namespace std;

std::string getHowToPlayText();
char getKey();
bool opening(sf::RenderWindow& window, HighScores*);
bool buttonIsClicked(sf::Sprite& button, sf::Vector2f mousePosition);
void displayHighScores(sf::RenderWindow& window, HighScores* highscores);
void howtoplay(sf::RenderWindow& window);
std::string getName(sf::RenderWindow& window);


int main()
{
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(GameSize.x, GameSize.y),"Hidden Maze Game 2.0",sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Music start_music;
    start_music.openFromFile(StartSoundFile);
    start_music.setVolume(20.0f);
    start_music.play();

    Fonts fonts;

    HighScores highScores;
    Game* game = nullptr;

    //GAME CLOCK & TIMER
    sf::Clock clock;
    int timer;
    sf::Event event;
    bool playAgain = opening(window, &highScores);
    string name = "";

    // Game Loop starts here ///////////////////////////
    while (playAgain)
    {
        if (name.length() == 0) name = getName(window);

        if (start_music.getStatus() == sf::SoundSource::Playing) start_music.stop();

        game = new Game(window, name);
        game -> flash();

        while (window.isOpen())
        {
            // Check all the window's events that were triggered
            // since the last iteration of the main loop.
            while (game->getWindow().pollEvent(event))
            {
                if (event.type == sf::Event::Closed) game->getWindow().close();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))     game->toggleDisplayMaze();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))      window.close();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))      game -> flash();  // flash
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))      game->bomb();     // bomb
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))      game->light();    // light
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))      game->jump();     // jump
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))     game->move(Player::Up);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))   game->move(Player::Down);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))   game->move(Player::Left);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    game->move(Player::Right);
                else break;
            }

            // Increment time clock
            if (game->getStatus() == Game::Active)
            {
                timer = static_cast<int> (clock.getElapsedTime().asSeconds());
                if (timer > 0)
                {
                    game->getPlayer()->decrementCountdown();
                    clock.restart();
                    game->getSounds().stopmusic();
                }
                // Loss: Out of time
                if (game->getPlayer()->getCountdown() <= 0)
                {
                    game->setStatus(Game::Loss);
                    break;
                }
            }
            if (game->getStatus() == Game::Loss|| game->getStatus() == Game::Win) break;
            game->draw_and_display();
        }

        if (game->getStatus() == Game::Loss)
        {
            string txt;
            game->getSounds().play(Sounds::Loss);
            if (game->getPlayer()->getBruises() >= 50) txt = "      You lose\nToo many bruises";
            else txt = " You lose\nOut of time";
            Message msg(txt, Fonts::Arial, 60);
            msg.draw(window);
            window.display();
            sf::sleep(sf::Time(sf::seconds(4.0f)));
        }

        if (game->getStatus() == Game::Win)
        {
            Message msg("You won!!!", Fonts::Komikap, 64, MidWindow, sf::Color::Green);
            game->getSounds().play(Sounds::Win);
            msg.draw(window);
            window.display();
            sf::sleep(sf::Time(sf::seconds(5.0f)));
            highScores.updateHighScores(Score(name.c_str(), game->getScore(), game->getBruises(), 60 - game->getCountdown(), time(0)));
            highScores.WriteHighScoresFile();
        }
        game->draw_and_display();
        playAgain = game->playAgain();
    }
    if (game) delete game;
    game = nullptr;

    return 0;
}

bool opening(sf::RenderWindow& window, HighScores* highscores)
{
    sf::Sprite button[4];
    sf::RectangleShape background(sf::Vector2f(GameSize.x, GameSize.y));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile(OpeningImageFile);
    background.setTexture(&backgroundTexture);

    sf::RectangleShape buttonBox(sf::Vector2f(550.f, 700.0f));
    buttonBox.setFillColor(sf::Color::Black);
    sf::FloatRect rect = buttonBox.getLocalBounds();
    buttonBox.setOrigin(rect.left +
                        rect.width / 2.0f,
                        rect.top +
                        rect.height / 2.0f);
    buttonBox.setPosition(MidWindow);
    // top of button box
    float tobb = MidWindow.y - buttonBox.getSize().y/2.0f;

    // Title
    sf::Text title("Joe's Hidden Maze Game", Fonts::Kristan);
    title.setFillColor(sf::Color(250,150,200));
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setPosition(MidWindow.x - titleRect.width/2, tobb + 0.04f * buttonBox.getSize().y);

    // Load buttons
    sf::Texture buttonsTexture;
    buttonsTexture.loadFromFile(ButtonImageFile);
    sf::Vector2f buttonSize= {200.0f,64.0};
    sf::IntRect locationInTexture;

    for (int i = 0; i < 4; i++)
    {
        button[i].setTexture(buttonsTexture);
        locationInTexture.height = static_cast<int>(buttonSize.y);
        locationInTexture.width = static_cast<int>(buttonSize.x);
        locationInTexture.left = 0;
        locationInTexture.top = i * buttonSize.y;
        button[i].setTextureRect(locationInTexture);
        button[i].setTexture(buttonsTexture);
        float buttonXpos = MidWindow.x - buttonSize.x/2.0f;
        float buttonYpos = tobb + 0.2f * (i + 0.8f) * buttonBox.getSize().y;

        button[i].setPosition(sf::Vector2f(buttonXpos, buttonYpos));
    }
    sf::Event event;
    sf::Vector2f mousePos;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                mousePos = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                for (int i = 0; i < 4; i++)
                {
                    if (buttonIsClicked(button[i], mousePos))
                    {
                        switch (i)
                        {
                        case 0:                                     // play
                            return true;
                        case 1:                                     // How to play
                            howtoplay(window);
                            break;
                        case 2:                                     // High scores
                            displayHighScores(window, highscores);
                            break;
                        case 3:                                     // Exit
                            return false;
                        default:
                            ;
                        }
                    }
                }
                break;
            case sf::Event::KeyPressed:
                break;
            default:
                ;
            }
        }
        window.clear();
        window.draw(background);
        window.draw(buttonBox);
        window.draw(title);
        for (int i = 0; i < 4; i++)
            window.draw(button[i]);
        window.display();
    }
    return false;
}

void displayHighScores(sf::RenderWindow& window, HighScores* highscores)
{
    sf::Sprite continueButton;
    sf::Texture continueTexture;
    continueTexture.loadFromFile(ContinueImageFile);
    continueButton.setTexture(continueTexture);
    continueButton.setPosition(sf::Vector2f(BottomWindow.x - 95.0f, BottomWindow.y));

    sf::RectangleShape background(sf::Vector2f(GameSize.x, GameSize.y));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile(OpeningImageFile);
    background.setTexture(&backgroundTexture);

    // Create High Scores text
    std::ostringstream sout;
    sout << "\n\n\n\n" << *highscores << std::endl << std::endl << std::endl << std::endl << std::endl;
    // Title
    sf::Text title("Joe's Hidden Maze Game", Fonts::Kristan);
    title.setFillColor(sf::Color(250,150,200));
    title.setPosition(sf::Vector2f(MidWindow.x - 180.0f, MidWindow.y - 160.0f));

    Message msg(sout.str(), Fonts::Courier, 16);

    sf::Event event;
    sf::Vector2f mousePos;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                mousePos = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                if (buttonIsClicked(continueButton, mousePos))  return;
                break;
            default:
                ;
            }
        }
        window.clear();
        window.draw(background);
        msg.draw(window);
        window.draw(continueButton);
        window.draw(title);
        window.display();
    }
}

void howtoplay(sf::RenderWindow& window)
{
    sf::Sprite continueButton;
    sf::Texture continueTexture;
    continueTexture.loadFromFile(ContinueImageFile);
    continueButton.setTexture(continueTexture);
    continueButton.setPosition(sf::Vector2f(BottomWindow.x - 90.0f, BottomWindow.y));

    // Get How to play file
    const std::string text = getHowToPlayText();

    // Title
    sf::Text title("Joe's Hidden Maze Game", Fonts::Kristan);
    title.setFillColor(sf::Color(250,150,200));
    title.setPosition(sf::Vector2f(TopWindow.x - 170.0f, TopWindow.y));
    Message howtoplay(text, Fonts::Arial, 18);
    sf::Event event;
    sf::Vector2f mousePos;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                mousePos = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                if (buttonIsClicked(continueButton, mousePos))
                {
                    return;
                }

                break;
            default:
                ;
            }
        }
        window.clear();
        howtoplay.draw(window);
        window.draw(continueButton);
        window.draw(title);
        window.display();
    }
}

std::string getName(sf::RenderWindow& window)
{
    std::string name;

    sf::Event event;

    char input = ' ';
    std::string text = "\nPlease type your name and press Enter ===> ";
    sf::Text namePrompt(text, Fonts::Arial, 20);
    sf::RectangleShape background(sf::Vector2f(GameSize.x, GameSize.y));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile(OpeningImageFile);
    background.setTexture(&backgroundTexture);

    sf::RectangleShape buttonBox(sf::Vector2f(600.f, 100.0f));
    buttonBox.setFillColor(sf::Color::Black);
    sf::FloatRect rect = buttonBox.getLocalBounds();
    buttonBox.setOrigin(rect.left +
                        rect.width / 2.0f,
                        rect.top +
                        rect.height / 2.0f);
    buttonBox.setPosition(MidWindow);
    namePrompt.setPosition(MidWindow.x - 250.f, MidWindow.y - 35.0f);

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
                    text = "\nPlease type your name and press Enter ===> ";
                }
                break;
            default:
                ;
            }
        }
        window.clear();
        window.draw(background);
        window.draw(buttonBox);
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

std::string getHowToPlayText()
{
    std::ifstream fin(HowToPlayFile);
    std::string text, buffer;
    if (!fin)
    {
        std::cout << "Cannot open how to play file." << std::endl;
        return "";
    }

    while (getline(fin, buffer))
    {
        text += buffer += '\n';
    }

    fin.close();
    return text;
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

bool buttonIsClicked(sf::Sprite& button, sf::Vector2f mousePosition)
{
    sf::FloatRect rectangle = button.getGlobalBounds();
    return rectangle.contains(mousePosition);
}
