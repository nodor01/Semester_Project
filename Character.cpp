#include "Character.h"

Character::Character(int x, int y) : position(x, y), pixelPosition(x * 22.0f, y * 22.0f) {}

void Character::draw(sf::RenderWindow& window) const {
    sf::RectangleShape character(sf::Vector2f(18, 18));
    character.setPosition(pixelPosition.x + 1, pixelPosition.y + 1);
    character.setFillColor(sf::Color::Red);

    sf::RectangleShape indicator(sf::Vector2f(6, 6));
    switch (direction) {
        case 0: indicator.setPosition(pixelPosition.x + 7, pixelPosition.y - 3); break; // Вверх
        case 1: indicator.setPosition(pixelPosition.x + 7, pixelPosition.y + 15); break; // Вниз
        case 2: indicator.setPosition(pixelPosition.x - 3, pixelPosition.y + 7); break; // Влево
        case 3: indicator.setPosition(pixelPosition.x + 15, pixelPosition.y + 7); break; // Вправо
    }
    indicator.setFillColor(sf::Color::Blue);

    window.draw(character);
    window.draw(indicator);
}

void Character::move(int dx, int dy, const Map& map) {
    sf::Vector2i newPos = position + sf::Vector2i(dx, dy);
    if (map.canMoveTo(newPos.x, newPos.y)) {
        position = newPos;
        if (dx == 0 && dy == -1) direction = 0;
        else if (dx == 0 && dy == 1) direction = 1;
        else if (dx == -1 && dy == 0) direction = 2;
        else if (dx == 1 && dy == 0) direction = 3;
    }
}

void Character::update(sf::Time deltaTime, const Map& map) {
    pixelPosition.x = position.x * 22.0f;
    pixelPosition.y = position.y * 22.0f;
}

void Character::attack(const Map& map) {
    // Пример атаки, которая будет удалять стены перед персонажем
    sf::Vector2i attackPos = position;
    switch (direction) {
        case 0: attackPos.y -= 1; break; // Вверх
        case 1: attackPos.y += 1; break; // Вниз
        case 2: attackPos.x -= 1; break; // Влево
        case 3: attackPos.x += 1; break; // Вправо
    }
    // Здесь вы можете добавить логику атаки в зависимости от типа атаки
}
