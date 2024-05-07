#include "Character.h"

Character::Character(sf::Vector2i startPos) : position(startPos) {
    shape.setRadius(8.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(8.0f, 8.0f);
}

void Character::moveUp() { position.y--; }
void Character::moveDown() { position.y++; }
void Character::moveLeft() { position.x--; }
void Character::moveRight() { position.x++; }

sf::Vector2i Character::getPosition() const { return position; }

void Character::draw(sf::RenderWindow& window) {
    shape.setPosition(position.x * 20.0f + 10.0f, position.y * 20.0f + 10.0f);
    window.draw(shape);
}
