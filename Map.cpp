#include "Map.h"
#include <cstdlib>
#include <ctime>

// Пример паттернов комнат
const std::vector<std::vector<int>> Map::roomPatterns = {
        {
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1,
                1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
                1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1,
                1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
                1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,
                1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
                1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1,
                1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
                1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1,
                1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
                1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        }
};

Map::Map() : width(0), height(0) {}

void Map::loadRoomPattern(const std::vector<int>& pattern, int startX, int startY, int roomWidth, int roomHeight) {
    for (int y = 0; y < roomHeight; ++y) {
        for (int x = 0; x < roomWidth; ++x) {
            tiles[(startY + y) * width + startX + x] = pattern[y * roomWidth + x];
        }
    }
}

bool Map::placeRoom(const std::vector<int>& pattern, int startX, int startY, int roomWidth, int roomHeight) {
    if (startX < 0 || startX + roomWidth > width || startY < 0 || startY + roomHeight > height) {
        return false;
    }
    for (int y = 0; y < roomHeight; ++y) {
        for (int x = 0; x < roomWidth; ++x) {
            if (tiles[(startY + y) * width + startX + x] != 0) {
                return false; // Если место занято, возвращаем false
            }
        }
    }
    loadRoomPattern(pattern, startX, startY, roomWidth, roomHeight);
    return true;
}

void Map::connectRooms(int startX1, int startY1, int startX2, int startY2) {
    int x1 = startX1 + 5; // Центр первой комнаты
    int y1 = startY1 + 5;
    int x2 = startX2 + 5; // Центр второй комнаты
    int y2 = startY2 + 5;

    while (x1 != x2) {
        tiles[y1 * width + x1] = 0; // Создаем проход
        if (x1 < x2) x1++;
        else x1--;
    }
    while (y1 != y2) {
        tiles[y1 * width + x1] = 0; // Создаем проход
        if (y1 < x2) y1++;
        else y1--;
    }
}

void Map::createRoomChain(int roomCount, const sf::Vector2u& windowSize) {
    // Размер ячейки
    int tileSize = 22;

    // Размер карты в ячейках
    width = windowSize.x / tileSize;
    height = windowSize.y / tileSize;

    // Инициализация карты пустыми полями
    tiles.resize(width * height, 0);
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4);

    // Очищаем позиции комнат
    roomPositions.clear();

    // Размер одной комнаты
    int roomWidth = 11;
    int roomHeight = 11;

    // Начальная позиция первой комнаты
    int startX = (width - roomWidth) / 2;
    int startY = (height - roomHeight) / 2;

    roomPositions.emplace_back(startX, startY);
    int randomIndex = std::rand() % roomPatterns.size();
    const std::vector<int>& selectedPattern = roomPatterns[randomIndex];
    placeRoom(selectedPattern, startX, startY, roomWidth, roomHeight);

    for (int i = 1; i < roomCount; ++i) {
        bool roomPlaced = false;
        for (int attempt = 0; attempt < 4; ++attempt) {
            int prevRoomIndex = std::rand() % roomPositions.size();
            int prevRoomX = roomPositions[prevRoomIndex].first;
            int prevRoomY = roomPositions[prevRoomIndex].second;

            int dir = std::rand() % 4;
            switch (dir) {
                case 0: // Вверх
                    startX = prevRoomX;
                    startY = prevRoomY - roomHeight - 1;
                    break;
                case 1: // Вниз
                    startX = prevRoomX;
                    startY = prevRoomY + roomHeight + 1;
                    break;
                case 2: // Влево
                    startX = prevRoomX - roomWidth - 1;
                    startY = prevRoomY;
                    break;
                case 3: // Вправо
                    startX = prevRoomX + roomWidth + 1;
                    startY = prevRoomY;
                    break;
            }

            if (placeRoom(selectedPattern, startX, startY, roomWidth, roomHeight)) {
                roomPlaced = true;
                connectRooms(prevRoomX, prevRoomY, startX, startY);
                roomPositions.emplace_back(startX, startY);
                break;
            }
        }
        if (!roomPlaced) {
            break; // Не удалось разместить комнату после нескольких попыток
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tileNumber = tiles[y * width + x];

            sf::Vertex* quad = &vertices[(y * width + x) * 4];

            quad[0].position = sf::Vector2f(x * tileSize, y * tileSize);
            quad[1].position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
            quad[2].position = sf::Vector2f((x + 1) * tileSize, (y + 1) * tileSize);
            quad[3].position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);

            if (tileNumber == 0) {
                quad[0].color = sf::Color::White;
                quad[1].color = sf::Color::White;
                quad[2].color = sf::Color::White;
                quad[3].color = sf::Color::White;
            } else {
                quad[0].color = sf::Color::Black;
                quad[1].color = sf::Color::Black;
                quad[2].color = sf::Color::Black;
                quad[3].color = sf::Color::Black;
            }
        }
    }
}

sf::Vector2i Map::getCenterOfFirstRoom() const {
    if (roomPositions.empty()) {
        return sf::Vector2i(0, 0);
    }
    int centerX = roomPositions[0].first + 5;
    int centerY = roomPositions[0].second + 5;
    return sf::Vector2i(centerX, centerY);
}

void Map::draw(sf::RenderWindow& window) const {
    window.draw(vertices);
}

bool Map::canMoveTo(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return tiles[y * width + x] == 0;
}
