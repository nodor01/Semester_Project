#include "Character.h"
#include <iostream>

Character::Character(int startX, int startY) : position(startX * 22, startY * 22), speed(200.0f), direction(Up) {
    shape.setSize(sf::Vector2f(22, 22));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
    std::cout << "Character created at position: (" << position.x << ", " << position.y << ")\n";
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Character::move(int dx, int dy, const Map& map) {
    sf::Vector2f newPosition = position + sf::Vector2f(dx * 22, dy * 22);
    int newX = static_cast<int>(newPosition.x / 22);
    int newY = static_cast<int>(newPosition.y / 22);

    if (map.canMoveTo(newX, newY)) {
        position = newPosition;
        shape.setPosition(position);
        std::cout << "Character moved to position: (" << position.x << ", " << position.y << ")\n";
    }
}

void Character::update(sf::Time deltaTime, const Map& map) {
    // Обновление состояния персонажа (если нужно)
}

void Character::attack(Map& map) {
    // Реализация атаки (если нужно)
}

void Character::rotate(Direction direction) {
    direction = direction;

    switch (direction) {
        case Up:
            shape.setRotation(0);
            break;
        case Right:
            shape.setRotation(90);
            break;
        case Down:
            shape.setRotation(180);
            break;
        case Left:
            shape.setRotation(-90);
            break;
    }
    std::cout << "Character rotated to direction: " << direction << "\n";
}
