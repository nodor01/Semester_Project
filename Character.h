#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Attack.h"

class Character {
public:
    Character(int x, int y);

    void draw(sf::RenderWindow& window) const;
    void move(int dx, int dy, const Map& map);
    void update(sf::Time deltaTime, const Map& map);
    void attack(const Map& map);

private:
    sf::Vector2i position;
    sf::Vector2f pixelPosition;
    float speed = 100.0f; // Пикселей в секунду
    int direction = 0; // 0 - вверх, 1 - вниз, 2 - влево, 3 - вправо
};

#endif // CHARACTER_H
