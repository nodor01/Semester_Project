#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

enum TileType {
    WALL,
    FLOOR,
    CORRIDOR,
    ENTRANCE,
    EXIT
};

struct Tile {
    TileType type;
    sf::RectangleShape shape;
    bool isPassable;

    Tile();
};

class Map {
public:
    Map(int width, int height);

    void draw(sf::RenderWindow& window);
    void generateRooms(int numRooms);
    void moveCharacter(sf::Vector2i& characterPos, sf::Vector2i newPos);

private:
    int width, height;
    std::vector<std::vector<Tile>> tiles;

    void generateRoom(int startX, int startY);
    void generateConnectedRoom();
};

#endif // MAP_H
