#pragma once

/////TASK 2
typedef int*(*resultFunction)(char const*);
typedef int(*otherFunction)(double);
typedef resultFunction (*complexFunction)(int, otherFunction);

/////TASK 3
template<class T, class R>
bool compare(const T& first, const T& second, R (T::*temporaryFunction)() const) {
    return ((first.*temporaryFunction)() < (second.*temporaryFunction)());
}

/////TASK 4
template<class T>
bool isSameObject(T const* firstObject, T const* secondObject){
    return (dynamic_cast<const void*>(firstObject)) == (dynamic_cast<const void*>(secondObject));
}