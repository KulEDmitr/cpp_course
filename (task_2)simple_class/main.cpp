#include <iostream>
#include "Student.h"

int main() {
    Student a;
    a.setData(123, "Nikolas", 2.3, 4, 45);
    a.showData();
    return 0;
}