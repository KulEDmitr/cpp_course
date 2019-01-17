#pragma once

#include <string>
#include <exception>

using namespace std;

class badFromString : public exception{
public:
    string mMessage;

    explicit badFromString(string message);
    const char* what() const noexcept override;
};