#include <iostream>
#include "headers/Unit.h"
#include "headers/ManBearPig.h"
#include "headers/functions.h"

using std::cout;
int main() {

    {
        cout << "\n-----BLOCK 1----- (complex function):\n";
        complexFunction complex = [](int x, otherFunction f) -> resultFunction {
            cout << "In complex " << f(x);
            resultFunction result = [](char const * x) -> int* {
                cout << "\nPtr to result function: ";
                return const_cast<int*>(reinterpret_cast<const int*>(x));
            };
            return result;
        };
        otherFunction other = [](double x) -> int {
            cout << "\nIn parameter: ";
            return (int)x;
        };
        cout << (complex(3, other))("8");
    }

    {
        string first("Elf");
        string second("Archer");
        cout << "\n\n-----BLOCK 2----- (comparison):\n"
             << "It's a(" << first << ") , b(" << second;
        bool r1 = compare(first, second, &std::string::size); // true
        bool r2 = compare(first, first, &std::string::size); // false
        cout << ")\nResult of compare \"a\" and \"b\" is    " << r1
             << "\nResult of compare \"a\" and \"a\" is    " << r2;
    }

    {
        auto firstUnit = ManBearPig(1, 300, 50, 15);
        auto secondUnit = ManBearPig(1, 300, 50, 15);
        auto bear = Bear(1, 300, 50, 15);
        auto* bearCast = dynamic_cast<Bear*>(&firstUnit);

        cout << "\n\n-----BLOCK 3----- (same object):\n"
             << "It's first(" << firstUnit.getTypeName() << ", " << firstUnit.getId()
             << ") , second(" << secondUnit.getTypeName() << ", " << secondUnit.getId()
             << ") , third(" << bear.getTypeName() << ", " << bear.getId()
             << ") , fourth(" << bearCast->getTypeName() << ", " << bearCast->getId()

             << ")\nfirst is second: "
             << (isSameObject(&firstUnit, &secondUnit) ? "true" : "false")
             << "\nfirst is first: "
             << (isSameObject(&firstUnit, &firstUnit) ? "true" : "false")
             << "\nthird is fourth: "
             << (isSameObject(&bear, bearCast) ? "true" : "false")
             << '\n';
    }

    {
        cout << "\n\n-----BLOCK 4----- (game):\n";
        size_t i = 0;
        auto m2 = ManBearPig(++i);
        cout << "Units type : " << m2.getTypeName()
             << "\nnoise : " << m2.makeNoise()
             << "\nAfter transformation\n";

        m2.transform(PIG);

        cout << "\nUnits type : " << m2.getTypeName()
             << "\nnoise : " << m2.makeNoise();
        auto m1 = Man(++i);
        cout << "\n\nUnits type : " << m1.getTypeName()
             << "\nnoise : " << m1.makeNoise();
        auto b = Bear(++i);
        cout << "\n\nUnits type : " << b.getTypeName()
             << "\nnoise : " << b.makeNoise();

        auto p = Pig(++i, 100, 1, 667);
        cout << "\n\npigs weight gained by experience is: " << p.fallToSomebody();
        p.grow(9876);
        cout << "\nweight after good diner is: " << p.fallToSomebody()
             <<"\nYes, he likes to fall to somebody)";
    }
    return 0;
}