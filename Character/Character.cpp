#include "Character.h"

Character::Character(int x, int y) : position(x, y), direction(Up) {
    pixelPosition = sf::Vector2f(position.x * 22.0f + 10.0f, position.y * 22.0f + 10.0f);

    shape.setSize(sf::Vector2f(18, 18));
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(9, 9);
    shape.setPosition(pixelPosition);

    head.setSize(sf::Vector2f(6, 6));
    head.setFillColor(sf::Color::Blue);
    head.setPosition(pixelPosition);
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(head);
}

void Character::move(int dx, int dy, const Map& map) {
    sf::Vector2i newPosition = position + sf::Vector2i(dx, dy);

    if (map.canMoveTo(newPosition.x, newPosition.y)) {
        position = newPosition;
        updatePixelPosition();

        if (dx == 0 && dy == -1) direction = Up;
        else if (dx == 0 && dy == 1) direction = Down;
        else if (dx == -1 && dy == 0) direction = Left;
        else if (dx == 1 && dy == 0) direction = Right;

        rotate(direction);
    }
}

void Character::updatePixelPosition() {
    pixelPosition = sf::Vector2f(position.x * 22.0f + 10.0f, position.y * 22.0f + 10.0f);
    shape.setPosition(pixelPosition);
    head.setPosition(pixelPosition);
}

void Character::update(sf::Time deltaTime, const Map& map) {
    // Обновление состояния персонажа
}

void Character::attack(Map& map) {
    // Реализация атаки
}

void Character::rotate(Direction dir) {
    this->direction = dir;

    switch (direction) {
        case Up:
            shape.setRotation(0);
            head.setRotation(0);
            head.setPosition(pixelPosition.x, pixelPosition.y - 11);
            break;
        case Right:
            shape.setRotation(90);
            head.setPosition(pixelPosition.x + 11, pixelPosition.y);
            break;
        case Down:
            shape.setRotation(180);
            head.setPosition(pixelPosition.x, pixelPosition.y + 11);
            break;
        case Left:
            shape.setRotation(-90);
            head.setPosition(pixelPosition.x - 11, pixelPosition.y);
            break;
    }
}
