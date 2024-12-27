#ifndef CAT_H
#define CAT_H
#include <SFML/Graphics.hpp>

class Cat : public sf::Sprite
{
    public:
        Cat();
        ~Cat();

    protected:

    private:
        sf::Texture catTexture;
        sf::Vector2i location;
};

#endif // CAT_H
