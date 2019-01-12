#pragma once

#include <cstddef>
#include "Array.h"

template<typename Type>
struct TestType {

    TestType() = delete;
    TestType& operator=(TestType const& other) = delete;

    friend std::ostream& operator<<(std::ostream& s, const TestType& obj) {
        s << *(obj.mData);
        return s;
    }

    friend bool operator<(const TestType& firstC, const TestType& secondC) {
        return firstC.mData < secondC.mData;
    }

    friend bool operator>(const TestType& firstC, const TestType& secondC) {
        return secondC < firstC;
    }

    explicit TestType(Type el);
    TestType(TestType const& other);

    ~TestType();

private:
    Type* mData;
};

#include "TestType.hpp"