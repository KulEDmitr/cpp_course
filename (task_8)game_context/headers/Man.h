#pragma once

#include "Unit.h"

const size_t MALE = 0, FEMALE = 1;

class Man : virtual public Unit {

    string mName;
    size_t mAge, mGender, mLoud, mPower;

public:
    explicit Man(size_t id, size_t hp = 170, size_t gender = MALE,
            string name = "Slava", size_t age = 15, size_t loud = 10);

    size_t getAge() const;
    string getName() const;
    size_t getGender() const;
    size_t getLoudLevel() const;
    size_t getPower() const;

    size_t getDamage() const override;
    string getTypeName() const override;

    string makeNoise() const override;
    string killerSong() const;

    void heal(size_t medicine) override;
    void protection(size_t damage) override;

    void grow();
};