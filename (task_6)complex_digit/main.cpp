#include <iostream>
#include "ComplexDigit.h"

using std::cout;

int main() {
    //Complex a1();
    Complex a2(45.7);
    Complex a3(12.8, -4);
    Complex a4(a2);
    Complex a5 = a2;
    Complex a6(1, 1);
    cout << "-BLOCK 1- (main constructors):\n" << a2 << '\n' << a2
         << '\n' << a3 << '\n' << a4 << '\n' << a5 << '\n' << a6 << '\n';
    a3.swap(a6);
    cout << "after swap " << a3 << '\n' << a6 << '\n';

    a2.setReal(8);
    a2.setImaginary(-2);
    a3.setAll(8, -2);
    cout << "\n-BLOCK 2- (setters):\n" << a2 << '\n' << a3 << '\n';

    cout << "\n-BLOCK 3- (getters):\nreal part of a2: " << a2.getReal()
         << " complex part of a2: " << a2.getImaginary()
         << "\nmodule of a2: " << a2.getModule() << '\n';

    Complex b(3, 0.8);
    Complex b1 = b;
    Complex b2 = b;
    Complex b3 = b;
    Complex b4 = b;
    cout << "\n-BLOCK 4- (increments / decrements):\n" << b
         << "\n++b: " << ++b1
         << "\n--b: " << --b2
         << "\nb++: " << b3++
         << "\nb--: " << b4-- << '\n';

    cout << "\n-BLOCK 5- (unary operators):\nIt's digit : (" << a2
         << ") \nIt's +digit : " << +a2
         << " \nIt's -digit : " << -a2
         << " \nIt's ~digit : " << ~a2 << '\n';

    Complex c(1, 1.6);
    Complex c1 = c;
    Complex c2 = c;
    Complex c3 = c;
    Complex c4 = c;
    cout << "\n-BLOCK 6- (arithmetic operators with keeping (double digits mode)):\n(" << c
         << ")\nc += 6.5 : " << (c1 += 6.5)
         << "\nc -= 6.5 : " << (c1 -= 13)
         << "\nc /= 2 : " << (c2 /= 2)
         << "\nc *= 2 : " << (c3 *= 2)
         << "\nc %= 5.5 : " << (c4 %= 5.5) << '\n';

    cout << "\n-BLOCK 7- (arithmetic operators (double digits mode)):\n" << c
         << "\nc + 6.5 : " << (c + 6.5)
         << "\nc - 6.5 : " << (c - 6.5)
         << "\nc / 2 : " << (c / 2)
         << "\nc * 2 : " << (c * 2)
         << "\nc % 5.5 :" << (c % 5.5) << "BLOCKS 6-7 return equal answeres)))\n";

    cout << "\n-BLOCK 8- (reverse arithmetic operators (double digits mode)):\n" << c
         << "\n6.5 + c : " << (6.5 + c)
         << "\n6.5 - c : " << (6.5 - c)
         << "\n2 / c : " << (2 / c)
         << "\n2 * c : " << (2 * c)
         << "\n5.5 % c : " << (5.5 % c) << '\n';

    c1.setAll(5567.0708, -7.007);
    c2.setAll(687.8, 76.09);
    c3 = c4 = c = c1;
    cout << "\n-BLOCK 9- (arithmetic operators with keeping (complex digits mode)):\n(" << c1 << ") (" << c2
         << ")\nc1 += c2 : " << (c1 += c2)
         << "\nc1 -= c2 : " << (c1 -= 2 * c2)
         << "\nc1 /= c2 : " << (c3 /= c2)
         << "\nc1 *= c2 : " << (c4 *= c2)
         << "\nc1 %= c2 : " << (c %= c2) << '\n';


    c1.setAll(5567.0708, -7.007);
    c2.setAll(687.8, 76.09);
    cout << "\n-BLOCK 10- (arithmetic operators(complex digits mode)):\n(" << c1 << ") (" << c2
         << ")\nc1 + c2 : " << (c1 + c2)
         << "\nc1 - c2 : " << (c1 - c2)
         << "\nc1 / c2 : " << (c1 / c2)
         << "\nc1 * c2 : " << (c1 * c2)
         << "\nc1 % c2 : " << (c1 % c2) << "\n\n BLOCKS 9-10 return equal answeres)))\n";

    Complex d1(9, 4);
    Complex d2(7.7, 7.7);
    Complex d3(d1);
    Complex d4(-7.6790, 8.098);
    cout << "\n-BLOCK 11- (comparison operators):\n"
         << "It's a(" << d1 << ") , b(" << d2 << ") , c(" << d3 << ") , d(" << d4
         << ")\nIs \"a\" smaller than \"b\"      ?    " << (d1 < d2)
         << "\nIs \"b\" bigger than \"c\"       ?    " << (d2 > d3)
         << "\nIs \"a\" not bigger than \"d\"   ?    " << (d1 <= d4)
         << "\nIs \"a\" equal with \"c\"        ?    " << (d1 == d3)
         << "\nIs \"a\" not equal with \"c\"    ?    " << (d1 != d3) << '\n';

    cout << "\n-BLOCK 12- (cast operators):\n"
         << "It's a(" << d4
         << ")\nIt's (int) a(" << (int) d4
         << ")\nIt's (double) a(" << (double) d4
         << ")\nIt's (bool) a(" << (bool) d4 << ")\n";


    c.setAll(1, 1.6);
    c1 = c2 = c3 = c4 = c;
    Complex c5(c);
    cout << "\n-BLOCK 13- (binary operators with keeping (double digits mode)):\n(" << c
         << ")\nc <<= 6.5 : " << (c1 <<= 6.5)
         << "\nc >>= 6.5 : " << (c2 >>= 6.5)
         << "\nc &= 2 : " << (c3 &= 2)
         << "\nc |= 2 : " << (c4 |= 2)
         << "\nc ^= 5.5 : " << (c5 ^= 5.5) << '\n';

    cout << "\n-BLOCK 14- (binary operators (double digits mode)):\n" << c
         << "\nc << 6.5 : " << (c << 6.5)
         << "\nc >> 6.5 : " << (c >> 6.5)
         << "\nc & 2 : " << (c & 2)
         << "\nc | 2 : " << (c | 2)
         << "\nc ^ 5.5 :" << (c ^ 5.5) << "BLOCKS 13-14 return equal answeres)))\n";

    cout << "\n-BLOCK 15- (reverse binary operators (double digits mode)):\n" << c
         << "\n6.5 << c : " << (6.5 << c)
         << "\n6.5 >> c : " << (6.5 >> c)
         << "\n2 & c : " << (2 & c)
         << "\n2 | c : " << (2 | c)
         << "\n5.5 ^ c : " << (5.5 ^ c) << '\n';

    c1.setAll(5567.0708, -7.007);
    c2.setAll(687.8, 76.09);
    c3 = c4 = c = c5 = c1;
    cout << "\n-BLOCK 16- (binary operators with keeping (complex digits mode)):\n(" << c1 << ") (" << c2
         << ")\nc1 <<= c2 : " << (c1 <<= c2)
         << "\nc1 >>= c2 : " << (c5 >>= c2)
         << "\nc1 &= c2 : " << (c3 &= c2)
         << "\nc1 |= c2 : " << (c4 |= c2)
         << "\nc1 ^= c2 : " << (c ^= c2) << '\n';


    c1.setAll(5567.0708, -7.007);
    cout << "\n-BLOCK 17- (binary operators(complex digits mode)):\n(" << c1 << ") (" << c2
         << ")\nc1 << c2 : " << (c1 << c2)
         << "\nc1 >> c2 : " << (c1 >> c2)
         << "\nc1 & c2 : " << (c1 & c2)
         << "\nc1 | c2 : " << (c1 | c2)
         << "\nc1 ^ c2 : " << (c1 ^ c2) << "\n\n BLOCKS 16-17 return equal answeres)))\n";


    c1.setAll(5567.0708, -7.007);
    c2.setAll(687.8, 76.09);
    cout << "\n-BLOCK 18- (logic operators (double digits mode)):\n(" << c1
         << ")\nc1 && 0 : " << (c1 && 0)
         << "\nc1 && 657.98 : " << (c1 && 657.98)
         << "\nc1 || 0 : " << (c1 || 0)
         << "\nc1 || 947323.8746 : " << (c1 || 947323.8746) << '\n';

    cout << "\n-BLOCK 19- (reverse logic operators (double digits mode)):\n(" << c1
         << ")\n0 && c1 : " << (0 && c1)
         << "\n657.98 && c1: " << (657.98 && c1)
         << "\n0 || c1: " << (0 || c1)
         << "\n947323.8746 || c1: " << (947323.8746 || c1)
         << "\n\n BLOCKS 18-19 return equal answeres)))\n";

    c1.setAll(5567.0708, -7.007);
    c2.setAll(687.8, 76.09);
    c3.setAll(0, 0);
    cout << "\n-BLOCK 20- logic operators (complex digits mode)):\n(" << c1 << ") (" << c2 << ") (" << c3
         << ")\nc1 && c2 : " << (c1 && c2)
         << "\nc1 && c3 : " << (c1 && c3)
         << "\nc1 || c2 : " << (c1 || c2)
         << "\nc1 || c3 : " << (c1 || c3)
         << "\n!c1 : " << (!c1)
         << "\n!c3 : " << (!c3) << '\n';

    cout << "\n-BLOCK 21- operators for access to class member:\n" << c1 << ") (" << c2 << ") (" << c3
         << ")\n*c1 : " << (*c1)
         << "\n&c1: " << (&c1)
         << "\nc1->*(1) : " << (c1->*1)
         << "\nc1[-34] : " << (c1[-34])
         << "\nc1[0] : " << (c1[0])
         << "\nc1(2, 4.985, 0, 1) : " << (c1(2, 4.985, 0, 1))
         << "\nc1(2) : " << (c1(2))
         << "\nc1(2, 4.985) : " << (c1(2, 4.985))
         << "\nc1, c2, c3 : " << (c1, c2, c3)
         << "\nc1, c2 : " << (c1, c2) << "\n\n\n---// it's all that i want //---";

    return 0;
}