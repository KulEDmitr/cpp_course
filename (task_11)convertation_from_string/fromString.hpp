#include <sstream>
#include "fromString.h"

template<class Type>
Type fromString(const string& data) {
    if constexpr (is_same<char*, Type>()) { return const_cast<char*>(data.c_str()); }
    if constexpr (is_same<string, Type>()) { return data; }

    Type result;
    istringstream iStream(data);
    iStream >> noskipws >> result;
    bool failed = iStream.fail();
    iStream.get();
    if (failed || !iStream.eof()) {
        throw badFromString("Failed of convertation to variable of type "
                             + string(typeid(Type).name()) + " for an input string \"" + data + "\"");
    }
    return result;
}