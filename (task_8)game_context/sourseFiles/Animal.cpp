#include <algorithm>

#include "../headers/Animal.h"

Animal::Animal(size_t id, size_t hp, size_t friendly) : Unit(id, hp), mFriendly(friendly){}


size_t Animal::getFriendly() { return mFriendly; }

string Animal::getTypeName() const { return "Animal"; }


string Animal::makeNoise() const { return "Aaaahrr, something loud, I suppose"; }


void Animal::heal(size_t medicine) { Unit::heal(medicine + mFriendly / 4); }


void Animal::enrage() { --mFriendly; }

void Animal::obey() { ++mFriendly; }