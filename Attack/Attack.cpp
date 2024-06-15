#include "Attack.h"

Attack::Attack(int damage, const std::vector<int>& pattern, int width, int height, AttackType type)
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

AttackType Attack::getType() const {
    return type;
}
