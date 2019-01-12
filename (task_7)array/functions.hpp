#include "functions.h"

template<class Num>
bool cmpLess(Num a, Num b) { return a < b; }

template<class Num>
bool cmpGreater::operator()(Num a, Num b) const { return b < a; }

template<class Num, class Comparator>
Num minimum(const Array<Num>& array, Comparator comp) {
    int indexMin = 0;
    for (int i = 1; i < array.size(); ++i) {
        if(comp(array[i], array[indexMin])) {
            indexMin = i;
        }
    }
    return array[indexMin];
}

template<class Num>
void flatten(const Num& element, std::ostream& out) {
    out << element << " ";
}

template<class Num>
void flatten(const Array<Num>& array, std::ostream& out) {
    for (int i = 0; i < array.size(); ++i) {
        flatten(array[i], out);
    }
    out << "\\--\\\n";
}