#include "Map.h"
#include <cstdlib>

Tile::Tile() : type(WALL), isPassable(false) {
    shape.setSize(sf::Vector2f(18.0f, 18.0f));
    shape.setFillColor(sf::Color::White);
}

Map::Map(int width, int height) : width(width), height(height), tiles(height, std::vector<Tile>(width)) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            tiles[y][x].shape.setPosition(x * 20.0f + 2.0f, y * 20.0f + 2.0f);
        }
    }
}

void Map::draw(sf::RenderWindow& window) {
    for (auto& row : tiles) {
        for (auto& tile : row) {
            window.draw(tile.shape);
        }
    }
}

void Map::generateRooms(int numRooms) {
    // Генерация начальной комнаты
    generateRoom(width / 2, height / 2);

    // Генерация остальных комнат
    for (int i = 1; i < numRooms; ++i) {
        generateConnectedRoom();
    }
}

void Map::generateRoom(int startX, int startY) {
    int roomWidth = rand() % 5 + 5; // Ширина комнаты от 5 до 9 ячеек
    int roomHeight = rand() % 5 + 5; // Высота комнаты от 5 до 9 ячеек

    for (int y = startY; y < startY + roomHeight; ++y) {
        for (int x = startX; x < startX + roomWidth; ++x) {
            tiles[y][x].type = FLOOR;
            tiles[y][x].isPassable = true;
            tiles[y][x].shape.setFillColor(sf::Color::Blue); // Цвет пола
        }
    }

    // Добавление проходов на краю комнаты
    for (int y = startY; y < startY + roomHeight; ++y) {
        for (int x = startX; x < startX + roomWidth; ++x) {
            if (x == startX || x == startX + roomWidth - 1 || y == startY || y == startY + roomHeight - 1) {
                tiles[y][x].type = CORRIDOR;
                tiles[y][x].isPassable = true;
                tiles[y][x].shape.setFillColor(sf::Color::Green); // Цвет прохода
            }
        }
    }
}

void Map::generateConnectedRoom() {
    // Выбор случайного прохода в комнате
    int entranceX, entranceY;
    do {
        entranceX = rand() % width;
        entranceY = rand() % height;
    } while (tiles[entranceY][entranceX].type != CORRIDOR);

    // Рандомное направление для следующей комнаты
    int direction = rand() % 4;
    int startX, startY;

    // Выбор координат для следующей комнаты в зависимости от направления
    switch (direction) {
        case 0: // Вверх
            startX = entranceX;
            startY = entranceY - (rand() % 5 + 5);
            if (startY < 0) startY = 0;
            break;
        case 1: // Вправо
            startX = entranceX + (rand() % 5 + 5);
            if (startX >= width) startX = width - 1;
            startY = entranceY;
            break;
        case 2: // Вниз
            startX = entranceX;
            startY = entranceY + (rand() % 5 + 5);
            if (startY >= height) startY = height - 1;
            break;
        case 3: // Влево
            startX = entranceX - (rand() % 5 + 5);
            if (startX < 0) startX = 0;
            startY = entranceY;
            break;
    }

    generateRoom(startX, startY);
}

void Map::moveCharacter(sf::Vector2i& characterPos, sf::Vector2i newPos) {
    // Перемещение персонажа, если новая позиция проходима
    if (tiles[newPos.y][newPos.x].isPassable) {
        tiles[characterPos.y][characterPos.x].type = FLOOR;
        characterPos = newPos;
        tiles[characterPos.y][characterPos.x].type = WALL; // Персонаж находится на стене
    }
}
