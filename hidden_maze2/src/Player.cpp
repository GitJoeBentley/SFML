#include "Player.h"
#include "Constants.h"
#include "Message.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <algorithm>
using namespace std;


Player::Player(const string& name_, Grid& grid_, Sounds& sounds_, sf::RenderWindow& win)
    : name(name_), location(sf::Vector2i(-1,0)), grid(grid_), sounds(sounds_), window(win), bruises(0), score(0), maxRow(0), maxCol(-1)
// Testing: : name(name_), location(sf::Vector2i(38,38)), grid(grid_), sounds(sounds_), bruises(0), score(0), maxRow(0), maxCol(-1)
{
    playerTexture.loadFromFile(PlayerImageFile);
    player.setTexture(playerTexture);
}


void Player::draw(sf::RenderWindow& window)
{
    player.setPosition(sf::Vector2f(WindowHorizontalOffset + location.x * CellWidth, WindowVerticalOffset + location.y * CellWidth));
    window.draw(player);
}

Wall::Type Player::move(Direction direction)
{
    if ((location.y == 0 && direction == Up) ||
            (location.x == 0 && direction == Left) ||
            (location.y == NumRows-1 && direction == Down) ||
            (location.x == NumRows-1 && location.y != NumRows-1 && direction == Right))
    {
        sounds.play(Sounds::Fart);
        return Wall::None;
    }
    sf::Vector2i newLocation(location);
    if (location.x == -1 && direction != Right) return Wall::None;
    switch (direction)
    {
    case Up:
        newLocation.y--;
        break;
    case Down:
        newLocation.y++;
        break;
    case Left:
        newLocation.x--;
        break;
    case Right:
        newLocation.x++;
    default:
        ;
    }
    return processMove(newLocation);
}

Wall::Type Player::processMove(const sf::Vector2i& newLocation)
{
    Wall::Type cellType;
    static int potionProtection = 0;

    Wall* ptrCell = grid.getCell(newLocation.x, newLocation.y);
    if (!ptrCell)
    {
        sounds.play(Sounds::Empty);
        location.x = newLocation.x;
        location.y = newLocation.y;
    }
    else
    {
        cellType = ptrCell->getType();
        // debugging: cout << "cellType=" << (int) cellType << endl;
        if (cellType == Wall::Rubber)
        {
            sounds.play(Sounds::Bounce);
            bounce();
            addToPath(100 * newLocation.x + newLocation.y);
            return cellType;
        }
        if (cellType == Wall::Cat)
        {
            //cerr << "Found the cat\n";
            if (!catVisited)
            {
                sounds.play(Sounds::Cat);
                Message msg("You found the cat\nThe clock is reset", Fonts::Arial, 36, MidWindow, sf::Color::Green);
                msg.draw(window);
                window.display();
                sf::sleep(sf::Time(sf::seconds(2.0f)));
                countdown = 60;
                catVisited = true;
            }

            addToPath(100 * newLocation.x + newLocation.y);
            location.x = newLocation.x;
            location.y = newLocation.y;
            return cellType;
        }
        else if (cellType == Wall::Potion)
        {
            //cerr << "Found the potion\n";
            if (!potionFound)
            {
                sounds.play(Sounds::Potion);
                Message msg("     You found the magic potion    \nYou will not feel the next 10 bruises", Fonts::Arial, 36, MidWindow, sf::Color::Green);
                potionProtection = 10;
                msg.draw(window);
                window.display();
                sf::sleep(sf::Time(sf::seconds(2.0f)));
                potionFound = true;
            }

            addToPath(100 * newLocation.x + newLocation.y);
            location.x = newLocation.x;
            location.y = newLocation.y;
            return cellType;
        }
        else
        {
            sounds.play(Sounds::Wall,static_cast<int>(cellType) * 15.0f);
            if (potionProtection) potionProtection--;
            else bruises++;
            --(*ptrCell);
            ptrCell->updateColor();
            if (ptrCell->getType() == Wall::None)
            {
                delete grid.getCell(newLocation.x, newLocation.y);
                grid.getCell(newLocation.x, newLocation.y) = nullptr;
                location.x = newLocation.x;
                location.y = newLocation.y;
            }
        }
    }
    updateScore();
    addToPath(100 * newLocation.x + newLocation.y);
    if (!ptrCell) return Wall::None;
    //print_path();
    return ptrCell->getType();
}

void Player::addToPath(int cell)
{
    std::vector<int>::iterator it;
    it = find (path.begin(), path.end(), cell);
    if (it == path.end()) path.push_back(cell);
}

void Player::updateScore()
{
    if (location.x > maxCol)
    {
        maxCol = location.x;
        score += 2;
    }
    else if (location.y > maxRow)
    {
        maxRow = location.y;
        score += 2;
    }
    else
    {
        int temp = 100 * location.x + location.y;
        std::vector<int>::iterator it;
        it = find(path.begin(), path.end(), temp);
        if (it == path.end()) score++;
    }
}

void Player::bounce()
{
    sf::Vector2i newLoc;
    bool locationOccupied = true;
    while (locationOccupied)
    {
        newLoc.x = rand() % (location.x + 1);
        newLoc.y = rand() % (location.y + 1);
        if (!grid.getCell(newLoc.x, newLoc.y))
            locationOccupied = false;
    }
    location = newLoc;
    addToPath(100 * newLoc.x + newLoc.y);
}


void Player::print_path() const
{
    for (auto loc : path)
    {
        std::cout << '(' << loc / 100 << ',' << loc % 100 << ')' << std::endl;
    }
}

void Player::draw_path(sf::RenderWindow& window) const
{
    static sf::RectangleShape empty(CellSize);
    empty.setFillColor(sf::Color(sf::Color::White));
    Wall* ptrCell;

    int x, y;

    for (unsigned i = 0; i < path.size(); i++)
    {
        x = path[i] / 100;
        y = path[i] % 100;
        ptrCell = grid.getCell(x,y);

        if (ptrCell) window.draw(*ptrCell);
        else
        {
            empty.setPosition(WindowHorizontalOffset + x * CellWidth, WindowVerticalOffset + y * CellWidth);
            window.draw(empty);
        }
    }
}

bool Player::bomb()
{
    Wall* wallPtr = nullptr;
    if (bombUsed)
    {
        sounds.play(Sounds::Fart);
        return false;
    }

    bombUsed = true;
    sounds.play(Sounds::Bomb);

    for (int x = location.x - 1; x <= location.x + 1; x++)
    {
        if (x < 0 || x >= NumRows) continue;
        for (int y = location.y - 1; y <= location.y + 1; y++)
        {
            if (y < 0 || y >= NumRows || (x == location.x && y == location.y)) continue;
            wallPtr = grid.getCell(x,y);
            if (wallPtr && wallPtr->getType() == Wall::Cat)
                if (!catVisited) grid.moveCat();
            grid.clearCell(x,y);
            addToPath(100 * x + y);
        }
    }
    countdown -= 3;
    score -= 2;
    bruises += 2;

    return true;
}

bool Player::light()
{
    if (lightUsed)
    {
        sounds.play(Sounds::Fart);
        return false;
    }
    lightUsed = true;
    sounds.play(Sounds::Light);
    for (int x = location.x - 1; x <= location.x + 1; x++)
    {
        if (x < 0 || x >= NumRows) continue;
        for (int y = location.y - 1; y <= location.y + 1; y++)
        {
            if (y < 0 || y >= NumRows) continue;
            addToPath(100 * x + y);
        }
    }
    countdown -= 2;
    score -= 1;
    bruises += 1;
    if (!catVisited) grid.moveCat();
    return true;
}
