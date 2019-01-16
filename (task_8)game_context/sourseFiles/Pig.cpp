#include "../headers/Pig.h"

Pig::Pig(size_t id, size_t hp, size_t friendly, size_t mass) : Unit(id, hp), Animal(id, hp, friendly), mMass(mass) {}


size_t Pig::fallToSomebody() { return mMass; }


size_t Pig::getDamage() const { return Unit::getDamage() + mMass / 2; }

string Pig::getTypeName() const { return "Pig"; }


string Pig::makeNoise() const { return "Ccgggwweeeeeeeeee"; }


void Pig::protection(size_t damage) { Unit::protection(damage - mMass / 13); }


void Pig::grow(size_t amount) { mMass += amount; }
