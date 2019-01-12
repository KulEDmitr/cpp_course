#pragma once

#include "TestType.h"

template<typename Type>
TestType<Type>::TestType(Type el) {
    mData = new Type();
    *mData = el;
}

template<typename Type>
TestType<Type>::TestType(TestType const &other) {
    mData = new Type();
    *mData = *other.mData;
}

template<typename Type>
TestType<Type>::~TestType() { delete this->mData; }

