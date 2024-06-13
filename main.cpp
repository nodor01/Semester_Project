#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"
#include <ctime>
#include <cstdlib>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Map Example");
    window.setFramerateLimit(60);

    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Map map;
    map.createRoomChain(5, window.getSize()); // Создаем карту с 5 неперекрывающимися комнатами, размер карты равен размеру окна

    // Начальная позиция персонажа в центре первой комнаты
    Character character(21, 21); // Задаем начальные координаты персонажа

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W)
                    character.move(0, -1, map);
                else if (event.key.code == sf::Keyboard::S)
                    character.move(0, 1, map);
                else if (event.key.code == sf::Keyboard::A)
                    character.move(-1, 0, map);
                else if (event.key.code == sf::Keyboard::D)
                    character.move(1, 0, map);
                else if (event.key.code == sf::Keyboard::Space)
                    character.attack(map);
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
