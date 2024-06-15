#include <SFML/Graphics.hpp>
#include "Menu/Menu.h"
#include "Map/Map.h"
#include "Character/Character.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Map Example");
    window.setFramerateLimit(60);

    // Инициализация меню и игровых объектов
    Menu mainMenu(window);
    bool inMainMenu = true;

    Map map;
    map.createRoomChain(10, window.getSize());

    sf::Vector2i startPosition = map.getCenterOfFirstRoom();
    Character character(startPosition.x, startPosition.y);

    sf::Clock clock;

    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Обработка событий в зависимости от того, находится ли игрок в главном меню или в игре
            if (inMainMenu) {
                mainMenu.handleInput(event);

                if (mainMenu.isNewGameClicked()) {
                    inMainMenu = false;
                    continue;
                }
                if (mainMenu.isSettingsClicked()) {
                    // Реализация функционала настроек здесь
                }
                if (mainMenu.isloadGameClicked()) {

                }
            } else {
                if (event.type == sf::Event::KeyPressed) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                        switch (event.key.code) {
                            case sf::Keyboard::W:
                                character.rotate(Up);
                                break;
                            case sf::Keyboard::S:
                                character.rotate(Down);
                                break;
                            case sf::Keyboard::A:
                                character.rotate(Left);
                                break;
                            case sf::Keyboard::D:
                                character.rotate(Right);
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

                // Обновление персонажа по времени
                sf::Time deltaTime = clock.restart();
                character.update(deltaTime, map);
            }
        }

        // Очистка и отрисовка
        window.clear();

        if (inMainMenu) {
            mainMenu.draw();
        } else {
            map.draw(window);
            character.draw(window);
        }

        window.display();
    }

    return 0;
}
