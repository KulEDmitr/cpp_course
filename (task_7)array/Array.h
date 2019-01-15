#pragma once

#include <cstddef>
#include <ostream>
#include <utility>


template<class Type>
class Array {

    uint8_t* mData;
    size_t mSize;

    void swap(Array& other);

public:
    Array();
    explicit Array(size_t size, const Type& value = Type());
    Array(const Array& other);
    Array(Array&& other);

    ~Array();

    Array& operator=(const Array& other);
    Array& operator=(Array&& other);

    Type& operator[](size_t i);
    const Type& operator[](size_t i) const;

    size_t size()const;
};

#include "Array.hpp"