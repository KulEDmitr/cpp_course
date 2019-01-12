#include <iostream>
#include "functions.h"
#include "TestType.h"

using namespace std;
int main() {
    {
        cout << "-----BLOCK 1----- (operator=)\ntemporary array: ";
        Array<char> ar(size_t(5), '0');
        Array<char> x(size_t(4), '4');
        Array<char> x1(size_t(8), '8');
        flatten(ar, cout);
        cout << "\n(chars)\n";
        ar = x;
        flatten(ar, cout);
        ar = x1;
        flatten(ar, cout);

        cout << "(strings)\n";
        Array<string> br(size_t(5), "0");
        Array<string> x3(size_t(4), "4");
        Array<string> x4(size_t(8), "8");
        br = x3;
        flatten(br, cout);
        br = x4;
        flatten(br, cout);

        cout << "(other strings)\n";
        Array<string> cr(size_t(100), "Str0");
        Array<string> x5(size_t(0), "Str1");
        Array<string> x6(size_t(2), "Str3");
        cr = x6;
        flatten(cr, cout);
        cr = x5;
        flatten(cr, cout);

        cout << "(integers)\n";
        Array<int> dr(size_t(5), 0);
        Array<int> x7(size_t(4), 4);
        Array<int> x8(size_t(8), 8);
        dr = x7;
        flatten(dr, cout);
        dr = x8;
        flatten(dr, cout);

        cout << "(doubles)\n";
        Array<double> er(size_t(5), 0.5);
        Array<double> x9(size_t(4), 4.5);
        Array<double> x10(size_t(8), 6.8);
        er = x9;
        flatten(dr, cout);
        er = x10;
        flatten(dr, cout);

        cout << "(clean array)\n";
        Array<char> fr(size_t(100), '0');
        Array<char> x11(size_t(0), '1');
        fr = x11;
        flatten(fr, cout);
    }

    {
        cout << "\n-----BLOCK 2----- (copy-constructor)\n(chars)\n";
        Array<char> x(size_t(3), '3');
        Array<char> ar(x);
        flatten(ar, cout);

        cout << "(strings)\n";
        Array<string> x1(size_t(3), "333afg3");
        Array<string> br(x1);
        flatten(br, cout);
    }

    {
        cout << "\n-----BLOCK 3----- (operator[])\n(in array)\n";
        Array<char> ar(size_t(4), '0');
        try {
            cout << ar[3] << endl;
        } catch (const char *e) {
            cout << e << endl;
        }

        cout << "\n(out range)\n";
        Array<char> br(size_t(4), '0');
        try {
            cout << br[-10] << endl;
        } catch (const char *e) {
            cout << e << endl;
        }
    }

    {
        cout << "\n-----BLOCK 4----- (minimum)\n(chars)\n";
        Array<int> ar(5, -1);
        ar[0] = 2;
        ar[1] = 5;
        ar[2] = 4;
        ar[3] = 1;
        ar[4] = 3;
        cout << minimum(ar, cmpLess<int>) << endl;
        cout << minimum(ar, cmpGreater()) << endl;

        cout << "\n(integers)\n";
        Array<int> br(3);
        br[0] = 10;
        br[1] = 2;
        br[2] = 15;
        cout << minimum(br, cmpLess<int>) << endl;
        cout << minimum(br, cmpGreater()) << endl;

        cout << "\n(TestType<double>)\n";
        TestType<double> x(2.3);
        Array<TestType<double>> cr(7, x);
        flatten(minimum(cr, cmpLess<TestType<double>>), cout);
        cout << '\n';
        flatten(minimum(cr, cmpGreater()), cout);
        cout << '\n';

        cout << "\n(TestType<string>)\n";
        TestType<string> y("gghjf");
        Array<TestType<string>> dr(7, y);
        flatten(minimum(dr, cmpLess<TestType<string>>), cout);
        cout << '\n';
        flatten(minimum(dr, cmpGreater()), cout);
        cout << '\n';
    }

    {
        cout << "\n-----BLOCK 5----- (flatten)\n";
        Array<int> ar((size_t) 4);
        for (int i = 0; i < 4; ++i) {
            ar[i] = 3 * i + 7;
        }
        Array<Array<int>> br(3, ar);
        Array<Array<Array<int>>> cr(2, br);
        Array<Array<Array<Array<int>>>> dr(4, cr);
        flatten(dr, cout);
    }
    return 0;
}