#ifndef PROTO_H_INCLUDED
#define PROTO_H_INCLUDED
#include "types.h"
#include "Game.h"

bool hasJoystick();
char getKey();
int start(sf::RenderWindow& window, sf::Font& font);
GameSelection playAgain(sf::RenderWindow& window, sf::Font& font);
void displayGameDescription(size_t gameNumber, sf::RenderWindow& window, sf::Font& font);
bool buttonIsClicked(sf::RectangleShape& button, sf::Vector2f mousePosition);
void drawCenteredText(sf::Text& text, sf::RenderWindow& window);
std::string getName(sf::RenderWindow& window, sf::Font& font, Game* game);
int getColorIndex(sf::Color color);

#endif // PROTO_H_INCLUDED
