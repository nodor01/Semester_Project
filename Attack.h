#ifndef ATTACK_H
#define ATTACK_H

#include <vector>
#include <string>

class Attack {
public:
    Attack(int damage, const std::vector<int>& pattern, int width, int height, const std::string& type);

    int getDamage() const;
    const std::vector<int>& getPattern() const;
    int getWidth() const;
    int getHeight() const;
    const std::string& getType() const;

private:
    int damage;
    std::vector<int> pattern;
    int width, height;
    std::string type;
};

#endif // ATTACK_H
