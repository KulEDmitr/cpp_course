#pragma once

#include "Bear.h"
#include "Pig.h"
#include "Man.h"

const size_t PIG = 0, BEAR = 1, MAN = 2;

class ManBearPig : public Man, public Bear, public Pig {

    size_t mCurrentType;

public:
    explicit ManBearPig(size_t id, size_t hp = 300, size_t friendly = 0, size_t mass = 150,
            size_t power = 200, size_t gender = MALE, string name = "Iraan",
                    size_t age = 25, size_t loud = 50, size_t type = MAN);

    void transform(size_t type);

    size_t getDamage() const override;
    string getTypeName() const override;

    string makeNoise() const override;

    void heal(size_t medicine) override;
    void protection(size_t damage) override;
};