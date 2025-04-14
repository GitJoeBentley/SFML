#include <fstream>
#include <SFML/Graphics.hpp>
#include "Message.h"
#include "ButtonBox.h"
#include "proto.h"
#include "Animation.h"

void displayGameDescription(size_t gameNumber, sf::RenderWindow& window, sf::Font& font)
{
    sf::Vector2u RenderWindowSize = window.getSize();

    const std::string digit = "0123456789D";
    const std::string filename = ResourcePath + "gamedescription" + digit[gameNumber] + ".txt";
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


int getColorIndex(sf::Color color)
{
    for (int i = 0; i < 7; i++)
        if (color == RainbowColor[i]) return i;
    return -1;
}

void pollEvent(sf::RenderWindow& window, sf::Clock& clock, Game* game, sf::Vector2f& joystick)
{
    int currentMPosX;
    static int minMouseX = static_cast<int>(GameBorderWidth + game->getPaddle()->getSize().x / 2);
    static int maxMouseX = static_cast<int>(GameWindowSize.x + GameBorderWidth - game->getPaddle()->getSize().x / 2);
    sf::Event event;

    if (game->getDevice() == Game::Control::Mouse)
    {
        currentMPosX = sf::Mouse::getPosition(window).x;
        if (currentMPosX < minMouseX)
        {
            sf::Mouse::setPosition(sf::Vector2i(minMouseX,sf::Mouse::getPosition(window).y), window);
            currentMPosX = minMouseX;
        }
        if (currentMPosX > maxMouseX)
        {
            sf::Mouse::setPosition(sf::Vector2i(maxMouseX,sf::Mouse::getPosition(window).y), window);
            currentMPosX = maxMouseX;
        }
        game->getPaddle()->setPosition(sf::Vector2f(currentMPosX, game->getPaddle()->getPosition().y));
    }

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            game->setStatus(Game::GameStatus::Quit);
            return;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::isButtonPressed(0,0))
        {
            game->setStatus(Game::GameStatus::Quit);
            return;
        }

        if (game->getStatus() == Game::GameStatus::NotStarted)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) game->setDevice(Game::Control::Keyboard);
            if (sf::Joystick::isButtonPressed(0,7)) game->setDevice(Game::Control::Joystick);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) game->setDevice(Game::Control::Mouse);
            if (game->getDevice() != Game::Control::None)
            {
                window.setMouseCursorVisible(false);
                game->setStatus(Game::GameStatus::Active);
                clock.restart();
                game->decrementNumBalls();
            }
            return;
        }

        if (game->getDevice() == Game::Control::Joystick)
        {
            sf::Joystick::update();
            joystick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
        }

        // Handle the pressing and releasing of the arrow keys
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || joystick.x < -15.f)
        {
            game->getPaddle()->move(Paddle::Left);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || joystick.x > 15.f)
        {
            game->getPaddle()->move(Paddle::Right);
        }
        else
        {
            game->getPaddle()->stop();
        }
    }
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

GameSelection playAgain(sf::RenderWindow& window, sf::Font& font, sf::Text* title)
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
    ButtonBox buttonBox(window, buttonLabels, font, 24 );
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
                    }
                }

            default:
                ;
            }
        }
        window.clear();
        window.draw(*title);

        buttonBox.draw();
        window.display();
    }

    return GameSelection::Exit;
}


int start(sf::RenderWindow& window, sf::Font& font, sf::Text* title)
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
    sf::Clock clock;
    sf::Time dt;

    size_t numButtons = GameName.size();
    ButtonBox buttonBox(window, GameName, font, 20 );
    sf::FloatRect* butRect = new sf::FloatRect[numButtons];
    for (size_t i = 0; i < numButtons; i++)
        butRect[i] = buttonBox.getButton(i)->getGlobalBounds();

    sf::Vector2f buttonBoxUpperLeft = buttonBox.getUpperLeftCorner();
    Animation** animation = new Animation*[10];
    for (int i = 0; i < 5; i++)
    {
        animation[i] = new Animation(sf::Vector2f(buttonBoxUpperLeft.x - 360.f, buttonBoxUpperLeft.y + i * 142.0f));
        animation[i + 5] = new Animation(sf::Vector2f(buttonBoxUpperLeft.x + buttonBox.getBoxSize().x + 40.f, buttonBoxUpperLeft.y + i * 142.0f));
    }

    while (window.isOpen())
    {
        dt = clock.restart();

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

                            if (i == numButtons - 1)
                            {
                                saveMousePos = mouse.getPosition();
                                displayGameDescription(i, window, font);
                                mouse.setPosition(saveMousePos);
                                break;
                            }
                            // Clean up before leaving
                            delete [] butRect;
                            butRect = nullptr;
                            for (int i = 0; i < 10; i++)
                            {
                                delete animation[i];
                                animation[i] = nullptr;
                            }
                            delete animation;
                            animation = nullptr;

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
        // process animations
        for (int i = 0; i < 10; i++)
        {
            animation[i]->update(dt);
            animation[i]->hitATile();
        }
        window.clear();

        window.draw(*title);
        buttonBox.draw();
        for (int i = 0; i < 10; i++) animation[i]->draw(window);
        window.display();
    }

    return -1;
}
