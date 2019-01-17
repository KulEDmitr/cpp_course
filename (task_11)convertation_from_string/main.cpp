#include <iostream>
#include <vector>

#include "fromString.h"

int main() {
    vector<string> dataVector = {"123", "12.3", "abc", "011110101", "100002456870998765", "i'm tired",
                                 "", " ", "4", "667", " 11", "11 ", "1 1", "5555555555555555555555555", "5x25"};

    int i = 0;
    for (auto& data : dataVector) {
        cout << "\n\n-----BLOCK " << (++i) << "-----\n(\"" << data << "\")\n\n convert to INTEGER:\n";
        try {
            cout << fromString<int>(data);
        } catch (badFromString &except) {
            cout << except.what();
        }

        cout << "\n\nconvert to DOUBLE:\n";
        try {
            cout << fromString<double>(data);
        } catch (badFromString &except) {
            cout << except.what();
        }

        cout << "\n\nconvert to LONG:\n";
        try {
            cout << fromString<long>(data);
        } catch (badFromString &except) {
            cout << except.what();
        }

        cout << "\n\nconvert to SHORT:\n";
        try {
            cout << fromString<short>(data);
        } catch (badFromString &except) {
            cout << except.what();
        }

        cout << "\n\nconvert to STRING:\n";
        try {
            cout << fromString<string>(data);
        } catch (badFromString &except) {
            cout << except.what();
        }

        cout << "\n\nconvert to CHAR*:\n";
        try {
            cout << fromString<char*>(data);
        } catch (badFromString &except) {
            cout << except.what();
        }

        cout << "\n\nconvert to BOOLEAN:\n";
        try {
            cout << fromString<bool>(data);
        } catch (badFromString &except) {
            cout << except.what();
        }
    }
    return 0;
}