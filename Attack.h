#ifndef ATTACK_H
#define ATTACK_H

#include <vector>
#include <string>

enum class AttackType {
    Fire,
    Poison,
    Water,
    Electric
};

class Attack {
public:
    Attack(int damage, const std::vector<int>& pattern, int width, int height, AttackType type);

    int getDamage() const;
    const std::vector<int>& getPattern() const;
    int getWidth() const;
    int getHeight() const;
    AttackType getType() const;

private:
    int damage;
    std::vector<int> pattern;
    int width, height;
    AttackType type;
};

#endif // ATTACK_H
