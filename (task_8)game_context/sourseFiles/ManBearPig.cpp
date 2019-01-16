#include "../headers/ManBearPig.h"
#include <utility>

ManBearPig::ManBearPig(size_t id, size_t hp, size_t friendly, size_t mass, size_t power, size_t gender,
                       string name, size_t age, size_t loud, size_t type) :
        Unit(id, hp),
        Pig(id, hp, friendly, mass),
        Bear(id, hp, friendly, power),
        Man(id, hp, gender, std::move(name), age, loud) { transform(type); }


void ManBearPig::transform(size_t type) {
    switch (type) {
        case 0:
            mCurrentType = PIG;
            break;
        case 1:
            mCurrentType = BEAR;
            break;
        default:
            mCurrentType = MAN;
            break;
    }
}



size_t ManBearPig::getDamage() const {
    return Bear::getDamage();
}

string ManBearPig::getTypeName() const {
    string answer("ManBearPig transformed to ");
    switch (mCurrentType) {
        case PIG:
            answer += Pig::getTypeName();
            break;
        case BEAR:
            answer += Bear::getTypeName();
            break;
        default:
            answer += "Man";
            break;
    }
    return answer;
}


string ManBearPig::makeNoise() const {
    switch (mCurrentType) {
        case PIG:
            return Pig::makeNoise();
        case BEAR:
            return Bear::makeNoise();
        default:
            return Man::killerSong();
    }
}


void ManBearPig::heal(size_t medicine) {
    switch (mCurrentType) {
        case PIG:
            return Pig::heal(medicine + 3);
        case BEAR:
            return Bear::heal(medicine + 6 + getPower());
        default:
            return Man::heal(medicine + 9 + getPower());
    }
}

void ManBearPig::protection(size_t damage) {
    switch (mCurrentType) {
        case PIG:
            Pig::protection(std::max(damage - Pig::fallToSomebody(), static_cast<size_t>(4)));
            Pig::grow(damage / 136);
            break;
        case BEAR:
            Bear::protection(std::max(damage - getPower(), static_cast<size_t>(2)));
            Bear::strengthen(damage / 103);
            break;
        default:
            Man::protection(std::max(damage - getPower() - getLoudLevel(), static_cast<size_t>(1)));
            Man::grow();
            break;
    }
}