#include "../headers/Bear.h"

Bear::Bear(size_t id, size_t hp, size_t friendly, size_t power) :
        Unit(id, hp), Animal(id, hp, friendly), mPower(power) {}


size_t Bear::getDamage() const { return Unit::getDamage() + mPower; }

string Bear::getTypeName() const { return "Bear"; }


string Bear::makeNoise() const { return "Rrrroooooaaaarrrr"; }


void Bear::protection(size_t damage) {
    Unit::protection(std::max(damage - mPower, static_cast<size_t>(1)));
    mPower += 2;
}


void Bear::strengthen(size_t amount) { mPower += amount; }