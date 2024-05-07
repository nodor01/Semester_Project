#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // Для генерации случайных чисел

enum TileType {
    WALL,
    FLOOR,
    CORRIDOR,
    ENTRANCE,
    EXIT
};

struct Tile {
    TileType type;
    sf::RectangleShape shape;
    bool isPassable;

    Tile() : type(WALL), isPassable(false) {
        shape.setSize(sf::Vector2f(18.0f, 18.0f)); // Размер тайла с учетом промежутков
        shape.setFillColor(sf::Color::White); // Цвет белых границ
    }
};

class Map {
public:
    Map(int width, int height) : width(width), height(height), tiles(height, std::vector<Tile>(width)) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                tiles[y][x].shape.setPosition(x * 20.0f + 2.0f, y * 20.0f + 2.0f); // Установка позиции тайла с учетом промежутков
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (auto& row : tiles) {
            for (auto& tile : row) {
                window.draw(tile.shape);
            }
        }
    }

    void generateRooms(int numRooms) {
        for (int i = 0; i < numRooms; ++i) {
            generateRoom();
        }
    }

    void generateRoom() {
        int roomWidth = rand() % 5 + 5; // Ширина комнаты от 5 до 9 ячеек
        int roomHeight = rand() % 5 + 5; // Высота комнаты от 5 до 9 ячеек

        int startX = rand() % (width - roomWidth - 1) + 1; // Стартовая позиция X комнаты
        int startY = rand() % (height - roomHeight - 1) + 1; // Стартовая позиция Y комнаты

        for (int y = startY; y < startY + roomHeight; ++y) {
            for (int x = startX; x < startX + roomWidth; ++x) {
                tiles[y][x].type = FLOOR;
                tiles[y][x].isPassable = true;
                tiles[y][x].shape.setFillColor(sf::Color::Blue); // Цвет пола
            }
        }

        // Генерация проходов
        int numEntrances = rand() % 4 + 1; // Количество проходов от 1 до 4
        for (int i = 0; i < numEntrances; ++i) {
            generateEntrance(startX, startY, roomWidth, roomHeight);
        }
    }

    void generateEntrance(int startX, int startY, int roomWidth, int roomHeight) {
        int side = rand() % 4; // Случайная сторона комнаты

        int x, y;
        switch (side) {
            case 0: // Верхняя сторона
                x = startX + rand() % roomWidth;
                y = startY;
                break;
            case 1: // Правая сторона
                x = startX + roomWidth - 1;
                y = startY + rand() % roomHeight;
                break;
            case 2: // Нижняя сторона
                x = startX + rand() % roomWidth;
                y = startY + roomHeight - 1;
                break;
            case 3: // Левая сторона
                x = startX;
                y = startY + rand() % roomHeight;
                break;
        }

        tiles[y][x].type = CORRIDOR;
        tiles[y][x].isPassable = true;
        tiles[y][x].shape.setFillColor(sf::Color::Green); // Цвет прохода
    }

    void createCorridor(int startX, int startY, int corridorWidth, int corridorHeight) {
        for (int y = startY; y < startY + corridorHeight; ++y) {
            for (int x = startX; x < startX + corridorWidth; ++x) {
                tiles[y][x].type = CORRIDOR;
                tiles[y][x].isPassable = true;
                tiles[y][x].shape.setFillColor(sf::Color::Green); // Цвет прохода
            }
        }
    }

    void moveCharacter(sf::Vector2i& characterPos, sf::Vector2i newPos) {
        // Перемещение персонажа, если новая позиция проходима
        if (tiles[newPos.y][newPos.x].isPassable) {
            tiles[characterPos.y][characterPos.x].type = FLOOR;
            characterPos = newPos;
            tiles[characterPos.y][characterPos.x].type = WALL; // Персонаж находится на стене
        }
    }

private:
    int width, height;
    std::vector<std::vector<Tile>> tiles;
};

class Character {
public:
    Character(sf::Vector2i startPos) : position(startPos) {
        shape.setRadius(8.0f); // Уменьшаем размер персонажа
        shape.setFillColor(sf::Color::Yellow); // Цвет персонажа
        shape.setOrigin(8.0f, 8.0f); // Устанавливаем центр в центр спрайта
    }

    void moveUp() { position.y--; }
    void moveDown() { position.y++; }
    void moveLeft() { position.x--; }
    void moveRight() { position.x++; }

    sf::Vector2i getPosition() const { return position; }

    void draw(sf::RenderWindow& window) {
        shape.setPosition(position.x * 20.0f + 10.0f, position.y * 20.0f + 10.0f); // Позиция персонажа
        window.draw(shape);
    }

private:
    sf::Vector2i position; // Позиция персонажа в комнате
    sf::CircleShape shape; // Фигура персонажа
};

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Room Example with SFML", sf::Style::Fullscreen);

    int tileSize = 20; // Размер тайла
    int mapWidth = desktop.width / tileSize;
    int mapHeight = desktop.height / tileSize;

    Map map(mapWidth, mapHeight); // Создание карты
    map.generateRooms(4); // Генерация 4 комнат

    // Создание коридоров между комнатами
    for (int i = 0; i < 3; ++i) {
        int corridorWidth = 3; // Ширина коридора
        int corridorHeight = 3; // Высота коридора

        // Генерация случайной позиции для коридора
        int startX = rand() % (mapWidth - corridorWidth - 1) + 1;
        int startY = rand() % (mapHeight - corridorHeight - 1) + 1;

        map.createCorridor(startX, startY, corridorWidth, corridorHeight);
    }

    Character character(sf::Vector2i(mapWidth / 2, mapHeight / 2)); // Создание персонажа
    sf::Vector2i characterPos = character.getPosition();

    while (window.isOpen()) {
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // Для генерации случайных чисел

        enum TileType {
            WALL,
            FLOOR,
            CORRIDOR,
            ENTRANCE,
            EXIT
        };

        struct Tile {
            TileType type;
            sf::RectangleShape shape;
            bool isPassable;

            Tile() : type(WALL), isPassable(false) {
                shape.setSize(sf::Vector2f(18.0f, 18.0f)); // Размер тайла с учетом промежутков
                shape.setFillColor(sf::Color::White); // Цвет белых границ
            }
        };

        class Map {
        public:
            Map(int width, int height) : width(width), height(height), tiles(height, std::vector<Tile>(width)) {
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        tiles[y][x].shape.setPosition(x * 20.0f + 2.0f, y * 20.0f + 2.0f); // Установка позиции тайла с учетом промежутков
                    }
                }
            }

            void draw(sf::RenderWindow& window) {
                for (auto& row : tiles) {
                    for (auto& tile : row) {
                        window.draw(tile.shape);
                    }
                }
            }

            void generateRooms(int numRooms) {
                // Генерация начальной комнаты
                generateRoom(width / 2, height / 2);

                // Генерация остальных комнат
                for (int i = 1; i < numRooms; ++i) {
                    generateConnectedRoom();
                }
            }

            void generateRoom(int startX, int startY) {
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

            void generateConnectedRoom() {
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

            void moveCharacter(sf::Vector2i& characterPos, sf::Vector2i newPos) {
                // Перемещение персонажа, если новая позиция проходима
                if (tiles[newPos.y][newPos.x].isPassable) {
                    tiles[characterPos.y][characterPos.x].type = FLOOR;
                    characterPos = newPos;
                    tiles[characterPos.y][characterPos.x].type = WALL; // Персонаж находится на стене
                }
            }

        private:
            int width, height;
            std::vector<std::vector<Tile>> tiles;
        };

        class Character {
        public:
            Character(sf::Vector2i startPos) : position(startPos) {
                shape.setRadius(8.0f); // Уменьшаем размер персонажа
                shape.setFillColor(sf::Color::Yellow); // Цвет персонажа
                shape.setOrigin(8.0f, 8.0f); // Устанавливаем центр в центр спрайта
            }

            void moveUp() { position.y--; }
            void moveDown() { position.y++; }
            void moveLeft() { position.x--; }
            void moveRight() { position.x++; }

            sf::Vector2i getPosition() const { return position; }

            void draw(sf::RenderWindow& window) {
                shape.setPosition(position.x * 20.0f + 10.0f, position.y * 20.0f + 10.0f); // Позиция персонажа
                window.draw(shape);
            }

        private:
            sf::Vector2i position; // Позиция персонажа в комнате
            sf::CircleShape shape; // Фигура персонажа
        };

        int main() {
            sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
            sf::RenderWindow window(desktop, "Room Example with SFML", sf::Style::Fullscreen);

            int tileSize = 20; // Размер тайла
            int mapWidth = desktop.width / tileSize;
            int mapHeight = desktop.height / tileSize;

            Map map(mapWidth, mapHeight); // Создание карты
            map.generateRooms(10); // Генерация 10 комнат

            Character character(sf::Vector2i(mapWidth / 2, mapHeight / 2)); // Создание персонажа
            sf::Vector2i characterPos = character.getPosition();

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::W)
                            character.moveUp();
                        else if (event.key.code == sf::Keyboard::S)
                            character.moveDown();
                        else if (event.key.code == sf::Keyboard::A)
                            character.moveLeft();
                        else if (event.key.code == sf::Keyboard::D)
                            character.moveRight();
                    }
                }

                sf::Vector2i newCharacterPos = character.getPosition();
                map.moveCharacter(characterPos, newCharacterPos);

                window.clear();
                map.draw(window);
                character.draw(window); // Отрисовка персонажа
                window.display();
            }

            return 0;
        }
    }

    return 0;
}
