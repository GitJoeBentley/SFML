#include "Fonts.h"
#include "Constants.h"
#include <iostream>
using namespace std;

sf::Font Fonts::Arial;
sf::Font Fonts::Kristan;
sf::Font Fonts::Courier;
sf::Font Fonts::Komikap;

Fonts::Fonts()
{
    Arial.loadFromFile(ArialFile);
    Courier.loadFromFile(CourierFile);
    Kristan.loadFromFile(KristanFile);
    Komikap.loadFromFile(KomikapFile);
}
