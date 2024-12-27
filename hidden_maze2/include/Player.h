#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include "Sounds.h"
#include <vector>
#include <string>

class Player : public sf::RectangleShape
{
    public:
        enum Direction {Up, Down, Left, Right};

        Player(const std::string& name, Grid& grid, Sounds& sounds_, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        Wall::Type move(Direction);
        std::string getName() const { return name; }
        int getBruises() const { return bruises; }
        int getScore() const { return score; }
        sf::Vector2i getLocation() const { return location; }
        void bounce();
        const std::vector<int>& getPath() const { return path; }
        void print_path() const;
        void draw_path(sf::RenderWindow& window) const;
        bool locationIsInThePath(int x, int y);
        int getCol() const { return location.x; }
        sf::Sprite& getPlayer() { return player; }
        void incrementBruises() { bruises++; }
        void decrementScore() { score--; }
        void decrementCountdown(int count = 1) { countdown -= count; }
        int getCountdown() const { return countdown; }
        bool bomb();
        bool light();
        bool flashed() const { return flashUsed; }
        bool jumped() const { return jumpUsed; }
        void setJumped() { jumpUsed = true; }
        void setFlashed() { flashUsed = true; }
        Wall::Type processMove(const sf::Vector2i& newLocation);
        void addToPath(int cell);
        bool catIsVisited() const { return catVisited; }

    private:
        std::string name;
        sf::Vector2i location;
        Grid& grid;
        Sounds& sounds;
        sf::RenderWindow& window;
        sf::Texture playerTexture;
        sf::Sprite player;
        int bruises;
        int score;
        int countdown = 60;
        bool bombUsed = false;
        bool lightUsed = false;
        bool jumpUsed = false;
        bool flashUsed = false;
        bool catVisited = false;
        int maxRow;
        int maxCol;
        std::vector<int> path;

        void updateScore();
};

#endif // PLAYER_H
