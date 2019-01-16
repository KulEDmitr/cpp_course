#include <iostream>
#include "../headers/Unit.h"

Unit::Unit(size_t id, size_t hp) : mId(id), mHealthPoint(hp), isAlive(mHealthPoint > 0){}


size_t Unit::getId() const { return mId; }

size_t Unit::getHealth() const { return mHealthPoint; }

bool Unit::aliveOrNotAlive() { return isAlive; }

size_t Unit::getDamage() const { return std::min(mHealthPoint - 100, mHealthPoint / 47); }

std::string Unit::getTypeName() const { return "Unit"; }


string Unit::makeNoise() const { return "Ooooohh"; }


void Unit::heal(size_t medicine) { mHealthPoint += medicine; }

void Unit::protection(size_t damage) {
    mHealthPoint -= damage;
    isAlive = mHealthPoint > 0;
}