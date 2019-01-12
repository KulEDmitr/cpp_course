#include <cmath>
#include "ComplexDigit.h"

//constructors
Complex::Complex(double re, double im) : mRe(re), mIm(im) {}
Complex::Complex(const Complex& c) : mRe(c.mRe), mIm(c.mIm) {}

//
void Complex::swap(Complex& other) {
    std::swap(mRe, other.mRe);
    std::swap(mIm, other.mIm);
}

Complex& Complex::operator=(const Complex& other) {
    if (this != &other) {
        Complex(other).swap(*this);
    }
    return *this;
}

//setters
void Complex::setReal(double re) { mRe = re; }
void Complex::setImaginary(double im) { mIm = im; }
void Complex::setAll(double re, double im) {
    mRe = re;
    mIm = im;
}

//getters
double Complex::getModule() const { return 2 * sqrt(mRe * mRe) + sqrt(mIm * mIm); }
double Complex::getReal() const { return mRe; }
double Complex::getImaginary() const { return mIm; }

//increments / decrements
const Complex& Complex::operator++() {
    mRe++;
    mIm++;
    return *this;
}

const Complex Complex::operator++(int) {
    Complex oldValue(mRe, mIm);
    ++(*this);
    return oldValue;
}

const Complex& Complex::operator--() {
    mRe--;
    mIm--;
    return *this;
}

const Complex Complex::operator--(int) {
    Complex oldValue(mRe, mIm);
    --(*this);
    return oldValue;
}

//unary operators
const Complex Complex::operator+() { return *this; }
const Complex Complex::operator-() { return Complex(-mRe, -mIm); }
const Complex Complex::operator~() { return Complex((~static_cast<int>(mRe)), ~static_cast<int>(mIm)); }

//arithmetic operators with keeping (double digits mode)
Complex& Complex::operator+=(double digit) { return *this += Complex(digit); }
Complex& Complex::operator-=(double digit) { return *this += (-digit); }
Complex& Complex::operator/=(double digit) { return *this /= Complex(digit); }
Complex& Complex::operator*=(double digit) { return *this *= Complex(digit); }
Complex& Complex::operator%=(double digit) { return *this %= Complex(digit); }

//arithmetic operators (double digits mode)
Complex Complex::operator+(double digit) { return *this + Complex(digit); }
Complex Complex::operator-(double digit) { return *this + (-digit); }
Complex Complex::operator/(double digit) { return *this / Complex(digit); }
Complex Complex::operator*(double digit) { return *this * Complex(digit); }
Complex Complex::operator%(double digit) { return *this % Complex(digit); }

//reverse arithmetic operators (double digits mode)
Complex operator+(double digit, const Complex& temporaryC) { return Complex(temporaryC.mRe + digit, temporaryC.mIm); }
Complex operator-(double digit, const Complex& temporaryC) { return -digit + temporaryC; }
Complex operator*(double digit, const Complex& temporaryC) { return Complex(temporaryC.mRe * digit, temporaryC.mIm * digit); }
Complex operator/(double digit, const Complex& temporaryC) { return Complex(temporaryC.mRe / digit, temporaryC.mIm / digit); }
Complex operator%(double digit, const Complex& temporaryC) { return Complex(fmod(temporaryC.mRe, digit), fmod(temporaryC.mIm, digit)); }

//functions for simplifying some other
Complex& Complex::universalOperation(Complex const& other, const std::function<double(double, double)> function) {
    mRe = function(mRe, other.mRe);
    mIm = function(mIm, other.mIm);
    return *this;
}

//arithmetic operators with keeping (complex digits mode)
Complex& Complex::operator+=(const Complex& other) {
    return universalOperation(other, [](double a, double b) { return a + b; });
}

Complex& Complex::operator-=(const Complex& other) {
    return universalOperation(other, [](double a, double b) { return a - b; });
}

Complex& Complex::operator*=(const Complex& other) {
    mRe = mRe * other.mRe - mIm * other.mIm;
    mIm = mRe * other.mIm + mIm * other.mRe;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double r = other.mRe * other.mRe + other.mIm * other.mIm;
    mRe = (mRe * other.mRe + mIm * other.mIm) / r;
    mIm = (mIm * other.mRe - mRe * other.mIm) / r;
    return *this;
}

Complex& Complex::operator%=(const Complex& other) {
    return universalOperation(other, [](double a, double b) { return fmod(a, b); });
}

//arithmetic operators (complex digits mode)
Complex Complex::operator+(const Complex& other) { return Complex(*this) += other; }
Complex Complex::operator-(const Complex& other) { return Complex(*this) -= other; }
Complex Complex::operator*(const Complex& other) { return Complex(*this) *= other; }
Complex Complex::operator/(const Complex& other) { return Complex(*this) /= other; }
Complex Complex::operator%(const Complex& other) { return Complex(*this) %= other; }

//comparison operators
bool operator==(const Complex& firstC, const Complex& second) { return ((firstC.mRe == second.mRe) && (firstC.mIm == second.mIm)); }
bool operator!=(const Complex& firstC, const Complex& second) { return !(firstC == second); }
bool operator<(const Complex& firstC, const Complex& second) { return (firstC.mRe < second.mRe && firstC.mIm < second.mIm); }
bool operator>(const Complex& firstC, const Complex& second) { return (second < firstC); }
bool operator<=(const Complex& firstC, const Complex& second) { return !(second < firstC); }
bool operator>=(const Complex& firstC, const Complex& second) { return !(firstC < second); }

//cast operators
Complex::operator int() const { return static_cast<int>(mRe); }
Complex::operator bool() const { return (mRe != 0 && mIm != 0); }
Complex::operator double() const { return getReal(); }

//binary operators with keeping (double digits mode)
Complex& Complex::operator<<=(double digit) { return *this <<= Complex(digit); }
Complex& Complex::operator>>=(double digit) { return *this >>= Complex(digit); }
Complex &Complex::operator&=(double digit) { return *this &= Complex(digit); }
Complex &Complex::operator|=(double digit) { return *this |= Complex(digit); }
Complex &Complex::operator^=(double digit) { return *this ^= Complex(digit); }

//binary operators (double digits mode)
Complex Complex::operator<<(double digit) { return *this << Complex(digit); }
Complex Complex::operator>>(double digit) { return *this >> Complex(digit); }
Complex Complex::operator&(double digit) { return *this & Complex(digit); }
Complex Complex::operator|(double digit) { return *this | Complex(digit); }
Complex Complex::operator^(double digit) { return *this ^ Complex(digit); }

//reverse binary operators (double digits mode)
Complex operator<<(double digit, const Complex& temporaryC) { return (Complex(digit) <<= temporaryC); }
Complex operator>>(double digit, const Complex& temporaryC) { return (Complex(digit) >>= temporaryC); }
Complex operator&(double digit, const Complex& temporaryC) { return (Complex(digit) &= temporaryC); }
Complex operator|(double digit, const Complex& temporaryC) { return (Complex(digit) |= temporaryC); }
Complex operator^(double digit, const Complex& temporaryC) { return (Complex(digit) ^= temporaryC); }

//binary operators with keeping (complex digits mode)
Complex& Complex::operator<<=(const Complex& other) { return universalOperation(other, [](int a, int b) { return a << b; }); }
Complex& Complex::operator>>=(const Complex& other) { return universalOperation(other, [](int a, int b) { return a >> b; }); }
Complex& Complex::operator&=(const Complex& other) { return universalOperation(other, [](int a, int b) { return a & b; }); }
Complex& Complex::operator|=(const Complex& other) { return universalOperation(other, [](int a, int b) { return a | b; }); }
Complex& Complex::operator^=(const Complex& other) { return universalOperation(other, [](int a, int b) { return a ^ b; }); }

//binary operators (complex digits mode)
Complex Complex::operator<<(const Complex& other) { return Complex(*this) <<= other; }
Complex Complex::operator>>(const Complex& other) { return Complex(*this) >>= other; }
Complex Complex::operator&(const Complex& other) { return Complex(*this) &= other; }
Complex Complex::operator|(const Complex& other) { return Complex(*this) |= other; }
Complex Complex::operator^(const Complex& other) { return Complex(*this) ^= other; }

//logic operators (double digits mode)
bool Complex::operator&&(double digit) { return *this && Complex(digit); }
bool Complex::operator||(double digit) { return *this || Complex(digit); }

//reverse logic operators (double digits mode)
bool operator&&(double digit, const Complex& temporaryC) { return temporaryC && Complex(digit); }
bool operator||(double digit, const Complex& temporaryC) { return temporaryC || Complex(digit); }

//logic operators (complex digits mode)
bool Complex::operator&&(const Complex& other) { return (bool) *this && (bool) other; }
bool Complex::operator||(const Complex& other) { return (bool) *this || (bool) other; }
bool Complex::operator!() { return !(bool) (*this); }

//operators for access to class member
Complex& Complex::operator*() { return *this; }
Complex* Complex::operator->() { return &Complex::operator*(); }
Complex* Complex::operator&() { return this; }
double Complex::operator->*(int element) { return this->operator[](element); }

double Complex::operator[](int index) {
    try {
        if (index < 2)
            switch (index) {
                case 0:
                    return mRe;
                case 1:
                    return mIm;
                default:
                    throw "Trouble: the index is less than zero!";
            }
    } catch (const char *str) {
        std::cout << str << std::endl;
        return index;
    }
    return 0;
}

const double Complex::operator[](int index) const {
    try {
        if (index < 2)
            switch (index) {
                case 0:
                    return mRe;
                case 1:
                    return mIm;
                default:
                    throw "Trouble: the index is less than zero!";
            }
    } catch (const char *str) {
        std::cout << str << std::endl;
        return index;
    }
    return 0;
}

Complex Complex::operator()(double add...) {
    double *p = &add;
    double ans = 0, count = 0;
    while (*p) {
        ans += (*p);
        ++p;
        ++count;
    }
    return Complex(mRe + ans, mIm + count);
}

Complex Complex::operator,(const Complex& other) {
    Complex tmp(*this);
    tmp *= other;
    tmp.mRe *= 2;
    return tmp;
}

//io operators
std::ostream& operator<<(std::ostream& out, const Complex& temporaryC) {
    if (temporaryC.mRe != 0) {
        out << temporaryC.mRe;
    } else if (temporaryC.mIm == 0) {
        out << 0;
    }
    if (temporaryC.mIm == 1) {
        out << " + i";
    } else if (temporaryC.mIm > 0) {
        out << " + " << temporaryC.mIm << "*i";
    } else if (temporaryC.mIm < 0) {
        out << " " << temporaryC.mIm << "*i";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Complex& temporaryC) {
    in >> temporaryC.mRe >> temporaryC.mIm;
    return in;
}