#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Constants.h"
#include "Wall.h"
#include "Cat.h"


class Grid
{
    public:
        enum Contents { Empty, Solid, RubberWall, Win, Loss, OutOfBounds};
        Grid();
        ~Grid();
        void draw(sf::RenderWindow&);
        void generate_path();
        void print_path() const;
        void draw_path(sf::RenderWindow& window);
        void drawCat(sf::RenderWindow& window);
        void moveCat();
        Wall*& getCell(int row, int col) { return cell[row][col]; }
        Wall& getCellRef(int row, int col) { return *(cell[row][col]); }
        //Grid::Contents getCellContents(int row, int col);
        Wall::Type getCellContents(int row, int col) { return cell[row][col]->getType(); }
        std::vector<int>& getPath() { return path; }
        bool locationIsInThePath(int x, int y) const;
        void AddARandomWall();
        void clearCell(int x, int y);

    private:
        //int numWalls;
        sf::CircleShape* step;
        std::vector<int> path;
        Wall* cell[NumCols][NumRows];
        Cat* cat = nullptr;

        void update_path(int x, int y);
        Wall::Type randomWall();
};

#endif // GRID_H
