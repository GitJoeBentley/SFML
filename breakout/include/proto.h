#ifndef PROTO_H_INCLUDED
#define PROTO_H_INCLUDED
#include "Game.h"

enum class GameSelection { Exit, Same, New};

bool hasJoystick();
char getKey();
int start(sf::RenderWindow& window, sf::Font& font, sf::Text* title);
GameSelection playAgain(sf::RenderWindow& window, sf::Font& font, sf::Text* title);
void displayGameDescription(size_t gameNumber, sf::RenderWindow& window, sf::Font& font);
bool buttonIsClicked(sf::RectangleShape& button, sf::Vector2f mousePosition);
void drawCenteredText(sf::Text& text, sf::RenderWindow& window);
std::string getName(sf::RenderWindow& window, sf::Font& font, Game* game);
int getColorIndex(sf::Color color);
void pollEvent(sf::RenderWindow& window, sf::Clock& clock, Game* game, sf::Vector2f& joystick, bool joyStickConnected);


#endif // PROTO_H_INCLUDED
