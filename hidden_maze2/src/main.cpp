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
#include "Button.h"
using namespace std;

std::string getHowToPlayText();
char getKey();
bool opening(sf::RenderWindow& window, HighScores*);
bool buttonIsClicked(sf::RectangleShape& button, sf::Vector2f mousePosition);
void displayHighScores(sf::RenderWindow& window, HighScores* highscores);
void howtoplay(sf::RenderWindow& window);
std::string getName(sf::RenderWindow& window);


int main()
{
    srand(static_cast<unsigned>(time(0)));
    //srand(16);   // for debugging purposes
    sf::RenderWindow window(sf::VideoMode(GameSize.x, GameSize.y),"Hidden Maze Game 2.2",sf::Style::Close);
    //sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    //sf::RenderWindow window(desktop,"Hidden Maze Game 2.2",sf::Style::None);
    //auto rsize = window.getSize();
    //cout << rsize.x << ' ' << rsize.y << endl;
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

    // Game Controller
    sf::Joystick joystick;
    float x, y; // joystick directions


    // Game Loop starts here ///////////////////////////
    while (playAgain)
    {
        if (name.length() == 0) name = getName(window);

        if (start_music.getStatus() == sf::SoundSource::Playing) start_music.stop();
        game = new Game(window, name);
        game -> flash();

        while (window.isOpen())
        {
            x = joystick.getAxisPosition(0, sf::Joystick::X);
            y = joystick.getAxisPosition(0, sf::Joystick::Y);
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
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)    or y < -50.f) game->move(Player::Up);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  or y > 50.f)  game->move(Player::Down);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  or x < -50.f) game->move(Player::Left);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or x > 50.f)
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
        if (game->getPlayer()->getCountdown() && game->getSounds().getSound(Sounds::Tick).getStatus() == sf::SoundSource::Playing)
            game->getSounds().getSound(Sounds::Tick).stop();

        if (game->getStatus() == Game::Loss)
        {
            string txt;
            game->getSounds().play(Sounds::Loss, 100.0f);
            if (game->getPlayer()->getBruises() >= 50) txt = "      You lose\nToo many bruises";
            else txt = " You lose\nOut of time";
            game -> flash();
            Message msg(txt, Fonts::Arial, 36, MidWindow, sf::Color::Red);
            msg.draw(window);
            window.display();
            sf::sleep(sf::Time(sf::seconds(5.0f)));
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
        game -> flash();
        playAgain = game->playAgain();
    }
    if (game) delete game;
    game = nullptr;

    return 0;
}

bool opening(sf::RenderWindow& window, HighScores* highscores)
{
    sf::RectangleShape background(GameSizeF);
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile(OpeningImageFile);
    background.setTexture(&backgroundTexture);
    long counter = 0;

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
    title.setFillColor(sf::Color(0xFA96C8ff));
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setPosition(MidWindow.x - titleRect.width/2, tobb + 0.04f * buttonBox.getSize().y);

    // Load buttons
    string buttonText[4] = {"PLAY", "HOW TO PLAY", "HIGH SCORES", "EXIT"};
    sf::Color color[4] = {sf::Color(0x2cbb56ff),sf::Color(0xff7f27ff),sf::Color(0x00a2e8ff),sf::Color(0xed1c24ff)};
    sf::Color hicolor[4] = {sf::Color(0x39f265ff),sf::Color(0xffc018ff),sf::Color(0x13d8e8ff),sf::Color(0xed7ab2ff)};
    Button* but[4];
    for (int i = 0; i < 4; i++)
    {
        but[i] = new Button(buttonText[i], color[i], hicolor[i], sf::Vector2f(MidWindow.x,  tobb + 20.0f + 0.2f * (i + 1.0f) * buttonBox.getSize().y));
    }

    sf::Event event;
    sf::Vector2f mousePos;
    sf::Vector2i mousePosI;
    sf::Mouse mouse;
    sf::FloatRect butRect[4];
    for (int i = 0; i < 4; i++)
        butRect[i] = but[i]->getGlobalBounds();
    while (window.isOpen())
    {
        mousePosI = mouse.getPosition(window);
        mousePos.x = static_cast<float>(mousePosI.x);
        mousePos.y = static_cast<float>(mousePosI.y);
        for (int i = 0; i < 4; i++)
        {
            if (butRect[i].contains(mousePos)) but[i]->highlight();
            else but[i]->normal();
        }

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
                    if (buttonIsClicked(*(but[i]), mousePos))
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
        counter++;
        for (int i = 0; i < 4; i++)
        {
            if (i == 0 && counter % 100 < 5) continue;
            but[i]->draw(window);
        }
        window.draw(title);
        window.display();
    }
    return false;
}

void displayHighScores(sf::RenderWindow& window, HighScores* highscores)
{
    Button continueButton("CONTINUE", sf::Color(0xfffd55ff), sf::Color(0xfeff89ff), sf::Vector2f(BottomWindow.x, BottomWindow.y));

    sf::RectangleShape background(GameSizeF);
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
    sf::Mouse mouse;
    sf::Vector2f mousePos;
    sf::Vector2i mousePosI;
    sf::FloatRect butRect = continueButton.getGlobalBounds();
    while (window.isOpen())
    {
        mousePosI = mouse.getPosition(window);
        mousePos.x = static_cast<float>(mousePosI.x);
        mousePos.y = static_cast<float>(mousePosI.y);
        if (butRect.contains(mousePos)) continueButton.highlight();
        else continueButton.normal();

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
        continueButton.draw(window);
        window.draw(title);
        window.display();
    }
}

void howtoplay(sf::RenderWindow& window)
{
    Button continueButton("CONTINUE", sf::Color(0xfffd55ff), sf::Color(0xfeff89ff), sf::Vector2f(BottomWindow.x, BottomWindow.y));

    // Get How to play file
    const std::string text = getHowToPlayText();

    // Title
    sf::Text title("Joe's Hidden Maze Game", Fonts::Kristan);
    title.setFillColor(sf::Color(250,150,200));
    title.setPosition(sf::Vector2f(TopWindow.x - 170.0f, TopWindow.y));
    Message howtoplay(text, Fonts::Arial, 18);
    sf::Event event;
    sf::Mouse mouse;
    sf::Vector2f mousePos;
    sf::Vector2i mousePosI;
    sf::FloatRect butRect = continueButton.getGlobalBounds();
    while (window.isOpen())
    {
        mousePosI = mouse.getPosition(window);
        mousePos.x = static_cast<float>(mousePosI.x);
        mousePos.y = static_cast<float>(mousePosI.y);
        if (butRect.contains(mousePos)) continueButton.highlight();
        else continueButton.normal();
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
            default:
                ;
            }
        }
        window.clear();
        howtoplay.draw(window);
        continueButton.draw(window);
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
    sf::RectangleShape background(GameSizeF);
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

bool buttonIsClicked(sf::RectangleShape& button, sf::Vector2f mousePosition)
{

    sf::FloatRect rectangle = button.getGlobalBounds();
    // sf::FloatRect rectangle = button.getGlobalBounds();
    return rectangle.contains(mousePosition);
}
