#pragma once

#include "TestType.h"

template<class Type>
TestType<Type>::TestType(Type el) {
    mData = new Type();
    *mData = el;
}

template<class Type>
TestType<Type>::TestType(TestType const &other) {
    mData = new Type();
    *mData = *other.mData;
}

template<class Type>
TestType<Type>::~TestType() { delete mData; }