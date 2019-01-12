#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {

    int mAdministrativeNumber;
    std::string mSurname;
    float mEng = 0, mMath = 0, mScience = 0, mTotal = 0;

    float computeTotal();

public:

    void setData(int admno, std::string const &sname, float eng, float math, float science);
    void showData();

};

#endif