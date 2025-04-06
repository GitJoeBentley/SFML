#ifndef FALLINGTILES_H
#define FALLINGTILES_H

#include <vector>

#include "Game.h"
#include "Tile.h"


class FallingTiles : public Game
{
    public:
        FallingTiles(sf::RenderWindow& wnd);
        virtual ~FallingTiles() = default;
        void setup();
        void process();
        std::vector<Tile*>& getFillingTiles();
        void insert(Tile* ptrTile);
        void fall();
        void findTileToFall();
        std::vector<Tile*>::iterator findTile(Tile* ptrTile);
        bool tileHitsPaddle(const sf::RectangleShape* paddle) const;
        bool tileGetsPassedThePaddle(const sf::RectangleShape* paddle);
        bool anyTileAtPaddleHeight() const;
        void processTileAtPaddleHeight();
    private:
        std::vector<Tile*> fallingTiles;
};



#endif // FALLINGTILES_H
