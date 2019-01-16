#pragma once

#include "Animal.h"

class Bear : public Animal{

    size_t mPower;

public:
    explicit Bear(size_t id, size_t hp = 200, size_t friendly = 0, size_t power = 100);

    size_t getDamage() const override;
    string getTypeName() const override;

    string makeNoise() const override;

    void protection(size_t damage) override;

    void strengthen(size_t amount);
};