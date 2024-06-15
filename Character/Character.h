#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "../Map/Map.h"
enum Direction { Up, Down, Left, Right };

class Character {
public:
    Character(int x, int y);
    void draw(sf::RenderWindow& window);
    void move(int dx, int dy, const Map& map);
    void update(sf::Time deltaTime, const Map& map);
    void attack(Map& map);
    void rotate(Direction direction);

private:
    sf::Vector2i position;
    sf::Vector2f pixelPosition;
    Direction direction;
    sf::RectangleShape shape;
    sf::RectangleShape head;

    void updatePixelPosition();
};

#endif // CHARACTER_H
