#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "constants.h"

class Tile : public sf::RectangleShape
{
public:
// TODO (Joe#1#): change Tile ctor to initialize Rectasngle Shape and not store width and height ...
//
    Tile(float width, float height);

/*     float getTileWidth() const
 *     {
 *         return tileWidth;
 *     }
 *     float getTileHeight() const
 *     {
 *         return tileHeight;
 *     }
 */

    void setLocation(sf::Vector2f loc)
    {
        setPosition(loc);
    }

    float getTopOfTile() const
    {
        return getPosition().y - getSize().y / 2.0f;
    }

    float getBottomOfTile() const
    {
        return getPosition().y + getSize().y / 2.0f;
    }
    float getLeftSideOfTile() const
    {
        return getPosition().x - getSize().x / 2.0f;
    }
    float getRightSideOfTile() const
    {
        return getPosition().x + getSize().x / 2.0f;
    }

private:
    //float tileWidth;
    //float tileHeight;
    //sf::RectangleShape tile;
    //bool visible;
    //sf::Vector2f location;
};

#endif // TILE_H
