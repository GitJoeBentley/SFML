#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Tile.h"
#include "Ball.h"
#include "Game.h"


class Animation : public sf::RectangleShape
{
    public:
        Animation(sf::Vector2f pos);
        virtual ~Animation();
        void draw(sf::RenderWindow& window);
        void update(sf::Time dt);
        void hitATile() const;

    private:
        Tile* tile[32];
        Ball* ball;
        Game::SideOfTile hitTileSide(const Tile* tile) const;
};

#endif // ANIMATION_H
