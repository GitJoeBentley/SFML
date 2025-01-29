#ifndef FONTS_H
#define FONTS_H
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>


class Fonts
{
public:
    Fonts();
    ~Fonts() = default;
    static sf::Font Arial;
    static sf::Font Kristan;
    static sf::Font Courier;
    static sf::Font Komikap;

private:
};

#endif // FONTS_H
