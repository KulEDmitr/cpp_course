#pragma once

#include <iostream>
#include <string>
#include <algorithm>

using std::string;

class Unit {

    size_t mId, mHealthPoint;
    bool isAlive;

public:
    explicit Unit(size_t id, size_t hp = 100);

    size_t getId() const;
    size_t getHealth() const;
    bool aliveOrNotAlive();
    virtual size_t getDamage() const;
    virtual string getTypeName() const;

    virtual string makeNoise() const;

    virtual void heal(size_t medicine);
    virtual void protection(size_t damage);
};