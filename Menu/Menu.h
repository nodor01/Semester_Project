#ifndef MENU_H
#define MENU_H
#include <vector>
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow& window);

    void handleInput(sf::Event& event);
    void update();
    void draw();

    bool isNewGameClicked() const;
    bool isloadGameClicked() const;
    bool isSettingsClicked() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    sf::Text newGameText;
    sf::Text loadGameText;
    sf::Text settingsText;

    bool newGameClicked;
    bool loadGameClicked;
    bool settingsClicked;

    std::vector<sf::Text*> partsOfMenu;
    sf::Vector2f pixelPosition;

    void initialize();
    void centerText(sf::Text& text, float offsetY);
};

#endif // MENU_H
