#ifndef POTION_H
#define POTION_H
#include <SFML/Graphics.hpp>


class Potion : public sf::Sprite
{
    public:
        Potion();
        ~Potion() = default;

    protected:

    private:
        sf::Texture potionTexture;
        sf::Vector2i location;
};

#endif // POTION_H
