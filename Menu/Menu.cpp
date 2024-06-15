#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window), newGameClicked(false), settingsClicked(false),loadGameClicked(false) {
    if (!font.loadFromFile("C:\\Users\\shatr\\CLionProjects\\Semester_Project\\fonts\\light-arial.ttf")) {
    }
    initialize();
}

void Menu::centerText(sf::Text& text, float offsetY) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    text.setPosition(pixelPosition.x, pixelPosition.y + offsetY);
}

//Reference to buttons: https://gamedev.stackexchange.com/questions/142308/how-to-create-a-button-in-sfml
//Centre of buutons: https://stackoverflow.com/questions/67523148/centering-text-on-top-of-buttons-in-sfml
void Menu::initialize() {
    titleText.setFont(font);
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("Main Menu");


    newGameText.setFont(font);
    newGameText.setCharacterSize(60);
    newGameText.setFillColor(sf::Color::White);
    newGameText.setString("New Game");

    loadGameText.setFont(font);
    loadGameText.setCharacterSize(60);
    loadGameText.setFillColor(sf::Color::White);
    loadGameText.setString("Load Game");


    settingsText.setFont(font);
    settingsText.setCharacterSize(60);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setString("Settings");

    partsOfMenu = { &titleText, &newGameText, &loadGameText, &settingsText };

    pixelPosition = { window.getSize().x / 2.f, window.getSize().y / 2.f - 100.f };

    float offsetY = 0.f;

    for (auto part : partsOfMenu) {
        centerText(*part, offsetY);
        offsetY += part->getCharacterSize() + 20.f;  // Add some space between lines
    }
}

void Menu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (newGameText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            newGameClicked = true;
        } else if (loadGameText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            loadGameClicked = true;
        } else if (settingsText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            settingsClicked = true;
        }
    }
}

void Menu::update() {
    // No update logic needed for now in menu
}

void Menu::draw() {
    window.draw(titleText);
    window.draw(newGameText);
    window.draw(loadGameText);
    window.draw(settingsText);
}

bool Menu::isNewGameClicked() const {
    return newGameClicked;
}

bool Menu::isloadGameClicked() const {
    return loadGameClicked;
}

bool Menu::isSettingsClicked() const {
    return settingsClicked;
}
