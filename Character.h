#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character {
public:
    Character(sf::Vector2i startPos);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    sf::Vector2i getPosition() const;

    void draw(sf::RenderWindow& window);

private:
    sf::Vector2i position;
    sf::CircleShape shape;
};

#endif // CHARACTER_H
