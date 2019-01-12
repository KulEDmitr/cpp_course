#include <cstring>
#include "String.h"

String::String(size_t size, char element) : mSize(size) {
    mData = new char[mSize + 1];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = element;
    }
    mData[mSize] = '\0';
}

void String::somethingStrange(char const* other) {
    mSize = strlen(other);
    mData = new char[mSize + 1];
    strcpy(mData, other);
}

String::String(char const* other) { somethingStrange(other); }

String::String(String const& other) { somethingStrange(other.mData); }

String& String::operator=(String const& other) {
    if (this != &other) {
        delete[] mData;
        somethingStrange(other.mData);
    }
    return *this;
}

bool operator==(String const& a, String const& b) {
    return !strcmp(a.mData, b.mData);
}

bool operator!=(String const& a, String const& b) {
    return !(a == b);
}

bool operator<(String const& a, String const& b) {
    if (a.mSize == b.mSize) {
        return strcmp(a.mData, b.mData) < 0;
    }
    size_t i = 0;
    bool answer = true;
    while (answer && i < a.mSize && i < b.mSize) {
        answer = a.mData[i] <= b.mData[i];
        ++i;
    }
    if (answer) {
        return a.mSize < b.mSize;
    }
    return answer;
}

bool operator>(String const& a, String const& b) { return b < a; }

bool operator<=(String const& a, String const& b) { return !(a > b); }

bool operator>=(String const& a, String const& b) { return !(a < b); }

String& String::operator*=(size_t repeater) {
    String temporary(mSize * repeater);
    if (repeater) {
        strcpy(temporary.mData, mData);
        while (--repeater) {
            strcat(temporary.mData, mData);
        }
    }
    temporary.mData[temporary.mSize] = '\0';
    return this->operator=(temporary);
}

String& operator*(String a, size_t repeater) { return a *= repeater; }

String& operator*(size_t repeater, String a) { return a *= repeater; }

std::ostream &operator<<(std::ostream& os, String const& other) {
    os << other.mData;
    return os;
}

String::~String() {
    delete[] mData;
}

String &String::append(String& other) {
    String temporary(mSize + other.mSize);
    strcpy(temporary.mData, mData);
    strcat(temporary.mData, other.mData);
    return this->operator=(temporary);
}