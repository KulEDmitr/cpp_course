#pragma once

#include <vector>
#include <string>
#include <iostream>

class String {

    char* mData;
    size_t mSize = 0;

    void somethingStrange(char const* other = "");

public:

    explicit String(char const* other = "");
    String(String const& other);
    explicit String(size_t size, char element = ' ');
    ~String();

    String& append(String& other);

    String& operator=(String const& other);

    String& operator*=(size_t repeater);

    friend bool operator==(String const& a, String const& b);
    friend bool operator!=(String const& a, String const& b);
    friend bool operator<(String const& a, String const& b);
    friend bool operator>(String const& a, String const& b);
    friend bool operator<=(String const& a, String const& b);
    friend bool operator>=(String const& a, String const& b);

    friend std::ostream& operator<<(std::ostream& is, String const& other);
};

String& operator*(String a, size_t repeater);
String& operator*(size_t repeater, String a);

bool operator==(String const& a, String const& b);
bool operator!=(String const& a, String const& b);
bool operator<(String const& a, String const& b);
bool operator>(String const& a, String const& b);
bool operator<=(String const& a, String const& b);
bool operator>=(String const& a, String const& b);