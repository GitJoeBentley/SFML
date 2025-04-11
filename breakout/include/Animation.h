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
        void hitATile();
        Game::SideOfTile hitTileSide(const Tile* tile) const;
        void update(sf::Time dt);

    private:
        Tile* tile[32];
        Ball* ball;
};

#endif // ANIMATION_H
