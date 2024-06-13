#include "Attack.h"

Attack::Attack(int damage, const std::vector<int>& pattern, int width, int height, const std::string& type)
        : damage(damage), pattern(pattern), width(width), height(height), type(type) {}

int Attack::getDamage() const {
    return damage;
}

const std::vector<int>& Attack::getPattern() const {
    return pattern;
}

int Attack::getWidth() const {
    return width;
}

int Attack::getHeight() const {
    return height;
}

const std::string& Attack::getType() const {
    return type;
}
