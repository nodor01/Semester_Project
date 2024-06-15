#include "Map.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

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
                1, 0, 2, 2, 0, 0, 0, 2, 2, 0, 1,
                1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1,
                1, 0, 0, 0, 2, 0, 2, 0, 0, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 0, 0, 2, 0, 2, 0, 0, 0, 1,
                1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1,
                1, 0, 2, 2, 0, 0, 0, 2, 2, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1,
                1, 0, 2, 0, 2, 2, 2, 2, 2, 0, 1,
                1, 0, 2, 0, 2, 0, 0, 0, 2, 0, 1,
                1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1,
                1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1,
                1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1,
                1, 0, 2, 0, 0, 0, 2, 0, 2, 0, 1,
                1, 0, 2, 2, 2, 2, 2, 0, 2, 0, 1,
                1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
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
    int center1X = startX1 + 5; // Центр первой комнаты
    int center1Y = startY1 + 5;
    int center2X = startX2 + 5; // Центр второй комнаты
    int center2Y = startY2 + 5;
    int changed_walls = 0;

    // Определяем направление соединения
    if (center1X == center2X) { // Вертикальное соединение
        int startY = std::min(center1Y, center2Y);
        int endY = std::max(center1Y, center2Y);
        int connectX = center1X;

        // Находим крайнюю стену для замены
        for (int y = startY; y <= endY; ++y) {
            if (tiles[y * width + connectX] == 1) {
                tiles[y * width + connectX] = 0;
                changed_walls += 1;
                if (changed_walls == 2) break;
            }
        }
    } else if (center1Y == center2Y) { // Горизонтальное соединение
        int startX = std::min(center1X, center2X);
        int endX = std::max(center1X, center2X);
        int connectY = center1Y;

        // Находим крайнюю стену для замены
        for (int x = startX; x <= endX; ++x) {
            if (tiles[connectY * width + x] == 1) {
                tiles[connectY * width + x] = 0; // Заменяем стену на пол
                changed_walls += 1;
                if (changed_walls == 2) {
                    break;
                }
            }
        }
    }
}


void Map::createRoomChain(int roomCount, const sf::Vector2u& windowSize) {
    // Map size in tile
    int tileSize = 22;

    // Map size in tile
    width = windowSize.x / tileSize;
    height = windowSize.y / tileSize;

    // Initialising the map with empty fields
    tiles.resize(width * height, 0);
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4);

    // Clear room positions
    roomPositions.clear();

    // Size room
    int roomWidth = 11;
    int roomHeight = 11;

    // Position first room
    int startX = (width - roomWidth) / 2;
    int startY = (height - roomHeight) / 2;

    roomPositions.emplace_back(startX, startY);
    int randomIndex = std::rand() % roomPatterns.size();
    auto& selectedPattern = roomPatterns[randomIndex];
    placeRoom(selectedPattern, startX, startY, roomWidth, roomHeight);

    // Place left rooms
    for (int i = 1; i < roomCount; ++i) {
        bool roomPlaced = false;

        for (int attempt = 0; attempt < 8; ++attempt) {
            int prevRoomIndex = std::rand() % roomPositions.size();
            int prevRoomX = roomPositions[prevRoomIndex].first;
            int prevRoomY = roomPositions[prevRoomIndex].second;
            randomIndex = std::rand() % roomPatterns.size();
            const std::vector<int>& selectedPattern = roomPatterns[randomIndex];

            int direction = std::rand() % 4;
            switch (direction) {
                case 0: // Up
                    startX = prevRoomX;
                    startY = prevRoomY - roomHeight;
                    break;
                case 1: // Down
                    startX = prevRoomX;
                    startY = prevRoomY + roomHeight;
                    break;
                case 2: // Left
                    startX = prevRoomX - roomWidth;
                    startY = prevRoomY;
                    break;
                case 3: // Right
                    startX = prevRoomX + roomWidth;
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
            break; // Impossible to place room after couple tries
        }
    }

    updateVertices();
}

void Map::updateVertices() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tileIndex = y * width + x;
            int tileType = tiles[tileIndex];

            sf::Color color;
            switch (tileType) {
                case 1:
                    color = sf::Color::Black;
                    break;// Wall
                case 0:
                    color = sf::Color::White;
                    break;// Floor
                case 2:
                    color = sf::Color::Transparent;
                    break;//Column
            }

            float posX = x * 22.0f; // Размер ячейки + контур
            float posY = y * 22.0f; // Размер ячейки + контур

            vertices[tileIndex * 4].position = sf::Vector2f(posX, posY);
            vertices[tileIndex * 4].color = color;
            vertices[tileIndex * 4 + 1].position = sf::Vector2f(posX + 20.0f, posY);
            vertices[tileIndex * 4 + 1].color = color;
            vertices[tileIndex * 4 + 2].position = sf::Vector2f(posX + 20.0f, posY + 20.0f);
            vertices[tileIndex * 4 + 2].color = color;
            vertices[tileIndex * 4 + 3].position = sf::Vector2f(posX, posY + 20.0f);
            vertices[tileIndex * 4 + 3].color = color;
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
