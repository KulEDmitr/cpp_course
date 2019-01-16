#pragma once

#include "Animal.h"

class Pig: public Animal {

    size_t mMass;

public:
    explicit Pig(size_t id, size_t hp = 110, size_t friendly = 10, size_t mass = 100);

    size_t fallToSomebody();

    size_t getDamage() const override;
    string getTypeName() const override;

    string makeNoise() const override;

    void protection(size_t damage) override;

    void grow(size_t amount);
};