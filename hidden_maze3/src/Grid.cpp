#include "Grid.h"
#include "Cat.h"
#include "externs.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;


Grid::Grid() : step(nullptr), cell(new Wall**[NumRows])
{
    for (int i = 0; i < NumRows; i++) cell[i] = new Wall*[NumCols];
    for (int r = 0; r < NumRows; r++)
        for (int c = 0; c < NumCols; c++)
            cell[r][c] = nullptr;
    int row, col;
    Wall::Type walltype;

    for (int i = 0; i < NumRows * NumCols / 2; i++)
    {
        row = rand() % NumRows;
        col = rand() % NumCols;
        if (row == 0 and col == 0) continue;
        if (cell[row][col]) continue;
        walltype = randomWall();
        if (walltype != Wall::None) cell[row][col] = new Wall(walltype, col, row);
    }
    generate_path();
    moveCat();
    movePotion();

    /***** Print the grid for debugging purposes
    for (int r = 0; r < NumRows; r++)
    {
        for (int c = 0; c < NumCols; c++)
        {
            if (cell[r][c]) cout << (int)(cell[r][c]->getType());
            else cout << '0';
        }
    }
    ******************************************/
}

void Grid::moveCat()
{
    int row, col;
    bool FoundLocationForCat = false;
    while (!FoundLocationForCat)
    {
        row = rand() % NumRows - 2 + 1;
        col = rand() % NumCols - 2 + 1;
        if (!locationIsInThePath(row, col)) FoundLocationForCat = true;
    }
    cat = new Cat();
    cat->setPosition(sf::Vector2f(UpperLeft.x + col * CellWidth, UpperLeft.y + row * CellWidth));
    for (int r = row; r <= row+1; r++)
    {
        for (int c = col; c <= col + 1; c++)
        {
            if (cell[r][c]) delete cell[r][c];
            cell[r][c] = new Wall(Wall::Cat, r, c);
        }
    }
}

void Grid::movePotion()
{
    int row, col;
    bool FoundLocationForPotion = false;
    while (!FoundLocationForPotion)
    {
        row = rand() % NumRows - 2 + 1;
        col = rand() % NumCols - 2 + 1;
        if (!locationIsInThePath(row, col)) FoundLocationForPotion = true;
    }
    potion = new Potion();
    potion->setPosition(sf::Vector2f(UpperLeft.x + col * CellWidth, UpperLeft.y + row * CellWidth));
    for (int r = row; r <= row+1; r++)
    {
        for (int c = col; c <= col + 1; c++)
        {
            if (cell[r][c]) delete cell[r][c];
            cell[r][c] = new Wall(Wall::Potion, r, c);
        }
    }
}

Wall::Type Grid::randomWall()
{
    int r = rand() % 32;
    if (r > 8) return Wall::Solid;
    else if (r > 4) return Wall::Hard;
    else if (r > 2) return Wall::Medium;
    else if (r > 1) return Wall::Soft;
    return Wall::Rubber;
}

Grid::~Grid()
{
    for (int r = 0; r < NumRows; r++)
    {
        for (int c = 0; c < NumCols; c++)
        {
            if (cell[r][c])
            {
                if (cell[r][c]) delete cell[r][c];
                cell[r][c] = nullptr;
            }
        }
    }
    delete [] step;
}

void Grid::AddARandomWall()
{
    int x, y, r;
    // Make sure location is empty and not in the path
    do
    {
        y = rand() % NumRows;
        x = rand() % NumCols;
    }
    while (locationIsInThePath(x, y) && !(cell[y][x]));
    r = randomWall();
    if (r) cell[x][y] = new Wall(static_cast<Wall::Type>(r), x, y);
}

void Grid::draw(sf::RenderWindow& window)
{
    Wall::Type cellType;
    for (int r = 0; r < NumRows; r++)
    {
        for (int c = 0; c < NumCols; c++)
        {
            if (cell[r][c])
            {
                // Jump over the cat and potion
                cellType = (cell[r][c])->getType();
                if (cellType == Wall::Cat || cellType == Wall::Potion) continue;
                window.draw(*(cell[r][c]));
            }
        }
    }
    window.draw(*cat);
    window.draw(*potion);
}

void Grid::generate_path()
{
    update_path(0,0);
    int move, last_move = -1;
    int row = 0, col = 0;
    while (!(row == NumRows-1 and col == NumCols-1))
    {
        move = rand() % 6;
        switch (move)
        {
        case 0:   // move down
            if (row < NumRows-1 && last_move != 5)
            {
                row++;
                update_path(row, col);
            }
            else move = last_move;
            break;
        case 1:   // move down 2
            if (row < NumRows-2)
            {
                row++;
                update_path(row, col);
                row++;
                update_path(row, col);
            }
            else move = last_move;
            break;
        case 2:   // move right
            if (col < NumCols-1 && last_move != 4)
            {
                col++;
                update_path(row, col);
            }
            else move = last_move;
            break;
        case 3:   // move right 3
            if (col < NumCols-3)
            {
                col++;
                update_path(row, col);
                col++;
                update_path(row, col);
                col++;
                update_path(row, col);
            }
            else move = last_move;

            break;
        case 4:   // move left
            if (col > 0 && last_move != 2 && last_move != 3)
            {
                col--;
                update_path(row, col);
            }
            else move = last_move;

            break;
        case 5:   // move up
            if (row > 0 && last_move != 0 && last_move != 1)
            {
                row--;
                update_path(row, col);
            }
            else move = last_move;

            break;
        default:
            ;
        }
        last_move = move;
    }
    //sort(path.begin(), path.end());
    //std::vector<int>::iterator it = std::unique(path.begin(), path.end());
    //path.resize(std::distance(path.begin(), it));
    step = new sf::CircleShape[path.size()];
    for (size_t i = 0; i < path.size(); i++)
    {
        row = path[i] / 100;
        col = path[i] % 100;
        step[i].setRadius(4.0f);
        step[i].setPosition(sf::Vector2f(UpperLeft.x + col * CellWidth, UpperLeft.y + row * CellWidth));
        step[i].setOrigin(-CellWidth / 2.0f, -CellWidth / 2.0f);
        step[i].setFillColor(sf::Color(sf::Color::Red));
    }
}

void Grid::clearCell(int row, int col)
{
    if (cell[row][col])
    {
        delete cell[row][col];
        cell[row][col] = nullptr;
    }
}


void Grid::print_path() const
{
    for (auto loc : path)
    {
        cout << "Grid::print_path() 258: " << '(' << loc / 100 << ',' << loc % 100 << ')' << endl;
    }
}

void Grid::draw_path(sf::RenderWindow& window)
{
    for (unsigned i = 0; i < path.size(); i++)
    {
        window.draw(step[i]);
    }
}

void Grid::drawCat(sf::RenderWindow& window)
{
    window.draw(*cat);
}

void Grid::drawPotion(sf::RenderWindow& window)
{
    window.draw(*potion);
}

void Grid::update_path(int row, int col)
{
    int newLoc = 100 * row + col;

    if (find(path.begin(), path.end(), newLoc) == path.end())
    {

        if (cell[row][col])
        {
            clearCell(row,col);
        }
        path.push_back(newLoc);
    }
}





bool Grid::locationIsInThePath(int row, int col) const
{
    return find(path.begin(), path.end(), 100 * row + col) != path.end();;
}

