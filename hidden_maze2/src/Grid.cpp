#include "Grid.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;


Grid::Grid() : step(nullptr)
{
    for (int r = 0; r < NumRows; r++)
        for (int c = 0; c < NumCols; c++)
            cell[r][c] = nullptr;
    int row, col;
            Wall::Type walltype;

    for (int i = 0; i < 749; i++)
    {
        row = rand() % 40;
        col = rand() % 40;
        if ((row == 0 and col == 0) or  (row == 0 and col == 0)) continue;
        if (cell[col][row]) continue;
        walltype = randomWall();
        if (walltype != Wall::None) cell[col][row] = new Wall(walltype, col, row);
    }
    generate_path();
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
    for (int r = 0; r < NumRows; r++)
    {
        for (int c = 0; c < NumCols; c++)
        {
            if (cell[r][c])
            {
                window.draw(*(cell[r][c]));
            }
        }
    }
}

void Grid::generate_path()
{
    update_path(0,0);
    int move, last_move = -1;
    int x = 0, y = 0;
    while (!(x == NumRows-1 and y == NumRows-1))
    {
        move = rand() % 6;
        switch (move)
        {
        case 0:
            if (x < NumRows-1 && last_move != 4)
            {
                x++;
                update_path(x, y);
            }
            else move = last_move;
            break;
        case 1:
            if (x < NumRows-2 && last_move != 4)
            {
                x++;
                update_path(x, y);
                x++;
                update_path(x, y);
            }
            else move = last_move;
            break;
        case 2:
            if (y < NumRows-1 && last_move != 5)
            {
                y++;
                update_path(x, y);
            }
            else move = last_move;
            break;
        case 3:
            if (y < NumRows-2 && last_move != 5)
            {
                y++;
                update_path(x, y);
                y++;
                update_path(x, y);
            }
            else move = last_move;

            break;
        case 4:
            if (x > 0 && last_move != 0 && last_move != 1)
            {
                x--;
                update_path(x, y);
            }
            else move = last_move;

            break;
        case 5:
            if (y > 0 && last_move != 2 && last_move != 3)
            {
                y--;
                update_path(x, y);
            }
            else move = last_move;

            break;
        default:
            ;
        }
        last_move = move;
    }
    sort(path.begin(), path.end());
    std::vector<int>::iterator it = std::unique(path.begin(), path.end());
    path.resize(std::distance(path.begin(), it));
    step = new sf::CircleShape[path.size()];

    for (unsigned i = 0; i < path.size(); i++)
    {
        x = path[i] / 100;
        y = path[i] % 100;
        step[i].setRadius(4.0f);
        step[i].setPosition(sf::Vector2f(WindowHorizontalOffset + x * CellWidth, WindowVerticalOffset + y * CellWidth));
        step[i].setOrigin(-CellWidth / 2.0f, -CellWidth / 2.0f);
        step[i].setFillColor(sf::Color(sf::Color::Red));
    }
}

void Grid::clearCell(int x, int y)
{
    if (cell[x][y])
    {
        delete cell[x][y];
        cell[x][y] = nullptr;
    }
}


void Grid::print_path() const
{
    for (auto loc : path)
    {
        cout << '(' << loc / 100 << ',' << loc % 100 << ')' << endl;
    }
}

void Grid::draw_path(sf::RenderWindow& window)
{
    for (unsigned i = 0; i < path.size(); i++)
    {
        window.draw(step[i]);
    }
}

void Grid::update_path(int x, int y)
{
    int newLoc = 100 * x + y;
    if (find(path.begin(), path.end(), newLoc) == path.end())
    {
        if (cell[x][y])
        {
            clearCell(x,y);
        }
        path.push_back(newLoc);
    }
}

bool Grid::locationIsInThePath(int x, int y) const
{
    return find(path.begin(), path.end(), 100 * x + y) != path.end();;
}

