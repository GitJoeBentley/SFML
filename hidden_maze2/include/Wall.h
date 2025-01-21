#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

class Wall : public sf::RectangleShape
{
public:
    enum Type {None, Soft, Medium, Hard, Solid, Rubber, Cat, Potion};

    Wall(Type type_, int col, int row);
    virtual ~Wall();

    Type getType() const
    {
        return type;
    }
    void setType(Type type)
    {
        this ->type = type;
    }
    Wall& operator--();
    sf::Color color() const;
    void updateColor();

private:
    Type type;
};

#endif // WALL_H
