#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map();

    void draw(sf::RenderWindow& window) const;
    bool canMoveTo(int x, int y) const;

    void createRoomChain(int roomCount, const sf::Vector2u& windowSize);

private:
    int width, height;
    std::vector<int> tiles;
    sf::VertexArray vertices;
    std::vector<std::vector<bool>> roomGrid; // Сетка занятых комнат

    void updateVertices();
    bool placeRoom(const std::vector<int>& pattern, int startX, int startY, int roomWidth, int roomHeight);
    void connectRooms(int startX1, int startY1, int startX2, int startY2);
    void loadRoomPattern(const std::vector<int>& pattern, int startX, int startY, int roomWidth, int roomHeight);

    static const std::vector<std::vector<int>> roomPatterns;
};

#endif // MAP_H
