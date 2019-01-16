#pragma once

#include <string>
#include "Unit.h"

class Animal : virtual public Unit {

    size_t mFriendly;

public:
    Animal(size_t id, size_t hp = 110, size_t friendly = 1);

    size_t getFriendly();
    string getTypeName() const override;

    string makeNoise() const override;

    void heal(size_t medicine) override;

    void enrage();
    void obey();
};