#include "../headers/Man.h"
#include <utility>

Man::Man(size_t id, size_t hp, size_t gender, string name, size_t age, size_t loud)
        : Unit(id, hp), mGender(gender), mName(std::move(name)), mAge(age), mLoud(loud) {
    mGender = (gender == FEMALE) ? FEMALE : MALE;
}


size_t Man::getAge() const { return mAge; }

string Man::getName() const { return mName; }

size_t Man::getGender() const { return mGender; }

size_t Man::getLoudLevel() const { return mLoud; }

size_t Man::getPower() const { return mPower; }


size_t Man::getDamage() const { return mAge * mGender + mLoud * 2; }

string Man::getTypeName() const { return "Man"; }


string Man::makeNoise() const {
    return "Aaaaaaaaaaaaaaaaaaaa";
}

string Man::killerSong() const { return "AND THE PERESTROIKA IS STILL GOING AND GOING ACCORDING TO PLAN!!!"; }


void Man::heal(size_t medicine) { Unit::heal(medicine + mPower); }

void Man::protection(size_t damage) {
    Unit::protection(std::max(damage - mPower, static_cast<size_t>(0)));
    mPower += mLoud / 3;
    ++mLoud;
}


void Man::grow() { ++mAge; }