#include "character.hpp"

#include <algorithm>
#include <cmath>

Character::Character(std::string name, std::string spriteFile, int hp, int attack, int defense) :
    name(name), spriteFile(spriteFile), hp(hp), attack(attack), defense(defense)
{ }

Character::~Character() { }

bool Character::attackCharacter(Character& character)  {
    return character.takeDamage(std::clamp(this->attack - (character.getDefense()/2),0,9999999));
}

bool Character::takeDamage(int damage) {
    hp = std::max(hp - damage, 0);
    return hp == 0;
}

int Character::getAttack() const {
    return this->attack;
}

void Character::setAttack(int attack) {
    this->attack = attack;
}

int Character::getDefense() const {
    return this->defense;
}

int Character::getHP() const {
    return this->hp;
}

std::string Character::getName() const {
    return this->name;
}

std::string Character::getSpriteFile() const {
    return this->spriteFile;
}

void Character::setDefense(int defense) {
    this->defense = defense;
}

void Character::setHP(int hp) {
    this->hp = hp;
}

void Character::setName(std::string name) {
    this->name = name;
}

