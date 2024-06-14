#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Map.h"
enum Direction{
    Up,
    Down,
    Left,
    Right
};
class Character {
public:
    Character(int startX, int startY);

    void draw(sf::RenderWindow& window);
    void move(int dx, int dy, const Map& map);
    void update(sf::Time deltaTime, const Map& map);
    void attack(Map& map);
    void rotate(Direction direction); // Новый метод для поворота персонажа

private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float speed;
    Direction direction;
};

#endif // CHARACTER_H
