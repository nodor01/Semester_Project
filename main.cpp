#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Map Example");
    window.setFramerateLimit(60);

    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Map map;
    map.createRoomChain(5, window.getSize()); // Создаем карту с 5 неперекрывающимися комнатами, размер карты равен размеру окна

    // Получаем центр первой комнаты
    sf::Vector2i startPosition = map.getCenterOfFirstRoom();
    std::cout << "Character start position: (" << startPosition.x << ", " << startPosition.y << ")\n";

    // Начальная позиция персонажа в центре первой комнаты
    Character character(startPosition.x, startPosition.y); // Задаем начальные координаты персонажа

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                    switch (event.key.code) {
                        case sf::Keyboard::W:
                            character.rotate(Direction::Up);
                            break;
                        case sf::Keyboard::S:
                            character.rotate(Direction::Down);
                            break;
                        case sf::Keyboard::A:
                            character.rotate(Direction::Left);
                            break;
                        case sf::Keyboard::D:
                            character.rotate(Direction::Right);
                            break;
                    }
                } else {
                    switch (event.key.code) {
                        case sf::Keyboard::W:
                            character.move(0, -1, map);
                            break;
                        case sf::Keyboard::S:
                            character.move(0, 1, map);
                            break;
                        case sf::Keyboard::A:
                            character.move(-1, 0, map);
                            break;
                        case sf::Keyboard::D:
                            character.move(1, 0, map);
                            break;
                        case sf::Keyboard::Space:
                            character.attack(map);
                            break;
                    }
                }
            }
        }

        sf::Time deltaTime = clock.restart();
        character.update(deltaTime, map);

        window.clear();
        map.draw(window);
        character.draw(window);
        window.display();
    }

    return 0;
}
