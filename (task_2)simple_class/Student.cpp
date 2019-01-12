#include <iostream>
#include "Student.h"

float Student::computeTotal() {
    return mEng + mScience + mMath;
}

void Student::setData(int admno, std::string const &sname, float eng, float math, float science) {
    mAdministrativeNumber = admno;
    if (sname.size() <= 20) {
        mSurname = std::string(sname);
        mScience = science;
        mEng = eng;
        mMath = math;
        mTotal = computeTotal();
    } else {
        mSurname = "error! too long name";
    }
}

void Student::showData() {
    std::cout << "Administrative number: " << mAdministrativeNumber
              << "\nName: " << mSurname
              << "\nTotal grade: " << mTotal
              << "\n\tmath: " << mMath
              << "\n\teng: " << mEng
              << "\n\tscience: " << mScience;
}