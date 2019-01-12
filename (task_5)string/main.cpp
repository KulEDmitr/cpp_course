#include <iostream>
#include "String.h"

int main() {
    String a("Hello");
    String b(", world");
    String c(3, '!');

    std::cout << "(BLOCK 1):\n" << a << b << c << '\n';

    a.append(b).append(c);
    std::cout << "\n(BLOCK 2):\n" << a << '\n' << b << '\n' << c << '\n';

    a.append(a);
    std::cout << "\n(BLOCK 3):\n" << a << '\n';

    String d(c);
    c = a = b;

    std::cout << "\n(BLOCK 4):\n" << d << '\n' << b << '\n' << a << '\n' << c << '\n';

    String a1("aaaaaa");
    String a2("aaaaaaaaa");
    String a3("bocsd");
    String b1(a1);
    String b2("aaaaaa");

    std::cout << "\n(BLOCK 5):\n"
             << "Is \"" << a1 << "\" smaller than \"" << a2 << "\" ?    " << (a1 < a2) << '\n'
            << "Is \"" << a2 << "\" bigger than \"" << a3 << "\" ?      " << (a2 > a3) << '\n'
            << "Is \"" << a1 << "\" not bigger than \"" << a3 << "\" ?     " << (a1 <= a3) << '\n'
            << "Is \"" << b1 << "\" equal with \"" << a1 << "\" ?         " << (b1 == a1) << '\n'
            << "Is \"" << b1 << "\" not equal with \"" << b2 << "\" ?     " << (b1 != b2) << '\n';

    String Aa("Xoxo");
    std::cout << "\n(BLOCK 6):\nIt's Aa : \"" << Aa << "\"";
    Aa *= 2;
    std::cout << "\nIt's Aa X2 : \"" << Aa
              << "\"\nIt's Aa (X2)X3 : \"" << Aa * 3
              << "\"\nIt's (X2)X3 Aa : \"" << 3 * Aa
              << "\"\nIt's Aa X2 again : \"" << Aa << "\"\n";

    return 0;
}