#ifndef FALLINGTILES_H
#define FALLINGTILES_H

#include <vector>

#include "Game.h"
#include "Tile.h"


class FallingTiles : public Game
{
    public:
        FallingTiles(sf::RenderWindow& wnd);

        // virtual functions
        virtual ~FallingTiles() = default;
        void setup();
        void update(sf::Time dt);
        int processHitTile(Tile* ptrTile, int ballNo = 0);


        std::vector<Tile*>::iterator findTile(Tile* ptrTile);
        std::vector<Tile*>& getFillingTiles();
        void insert(Tile* ptrTile);
        void fall();
        void findTileToFall();
        bool tileHitsPaddle(const sf::RectangleShape* paddle) const;
        bool tileGetsPassedThePaddle(const sf::RectangleShape* paddle);
        bool anyTileAtPaddleHeight() const;
        void processTileAtPaddleHeight();
    private:
        std::vector<Tile*> fallingTiles;
};



#endif // FALLINGTILES_H
