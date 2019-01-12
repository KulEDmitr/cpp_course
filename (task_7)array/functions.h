#pragma once

#include <ostream>
#include "Array.h"

template<class Num>
bool cmpLess(Num a, Num b);

struct cmpGreater {
    template<class Num>
    bool operator()(Num a, Num b) const;
};

template<class Num, class Comparator>
Num minimum(const Array<Num>& array, Comparator comp);

template<class Num>
void flatten(const Num& element, std::ostream &out);

template<class Num>
void flatten(const Array<Num>& array, std::ostream &out);

#include "functions.hpp"