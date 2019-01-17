#include "badFromString.h"

badFromString::badFromString(string message) : mMessage(move(message)){}

const char* badFromString::what() const noexcept { return mMessage.c_str(); }