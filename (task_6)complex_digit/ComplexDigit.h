#pragma once

#include <iostream>
#include <functional>

class Complex {

    double mRe, mIm;

    //functions for simplifying some other
    Complex& universalOperation(Complex const &rhs, const std::function<double(double, double)> function);

public:

    // main constructors
    Complex() = default;
    explicit Complex(double re, double im = 0);
    Complex(const Complex& other);

    ~Complex() = default;

    void swap(Complex& other);
    Complex &operator=(const Complex& other);

    //setters
    void setReal(double re);
    void setImaginary(double im);
    void setAll(double re, double im);

    //getters
    double getModule() const;
    double getReal() const;
    double getImaginary() const;

    //increments / decrements
    const Complex& operator++();
    const Complex operator++(int);
    const Complex& operator--();
    const Complex operator--(int);

    //unary operators
    const Complex operator+();
    const Complex operator-();
    const Complex operator~();

    //arithmetic operators with keeping (double digits mode)
    Complex& operator+=(double digit);
    Complex& operator-=(double digit);
    Complex& operator/=(double digit);
    Complex& operator*=(double digit);
    Complex& operator%=(double digit);

    //arithmetic operators (double digits mode)
    Complex operator+(double digit);
    Complex operator-(double digit);
    Complex operator/(double digit);
    Complex operator*(double digit);
    Complex operator%(double digit);

    //reverse arithmetic operators (double digits mode)
    friend Complex operator+(double digit, const Complex& other);
    friend Complex operator-(double digit, const Complex& other);
    friend Complex operator*(double digit, const Complex& other);
    friend Complex operator/(double digit, const Complex& other);
    friend Complex operator%(double digit, const Complex& other);

    //arithmetic operators with keeping (complex digits mode)
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);
    Complex& operator%=(const Complex& other);

    //arithmetic operators (complex digits mode)
    Complex operator+(const Complex& other);
    Complex operator-(const Complex& other);
    Complex operator*(const Complex& other);
    Complex operator/(const Complex& other);
    Complex operator%(const Complex& other);

    //comparison operators
    friend bool operator==(const Complex& firstC, const Complex& secondC);
    friend bool operator!=(const Complex& firstC, const Complex& secondC);
    friend bool operator<(const Complex& firstC, const Complex& secondC);
    friend bool operator>(const Complex& firstC, const Complex& secondC);
    friend bool operator<=(const Complex& firstC, const Complex& secondC);
    friend bool operator>=(const Complex& firstC, const Complex& secondC);

    //cast operators
    explicit operator bool() const;
    explicit operator int() const;
    explicit operator double() const;

    //binary operators with keeping (double digits mode)
    Complex& operator<<=(double digit);
    Complex& operator>>=(double digit);
    Complex& operator&=(double digit);
    Complex& operator|=(double digit);
    Complex& operator^=(double digit);

    //binary operators (double digits mode)
    Complex operator<<(double digit);
    Complex operator>>(double digit);
    Complex operator&(double digit);
    Complex operator|(double digit);
    Complex operator^(double digit);

    //reverse binary operators (double digits mode)
    friend Complex operator<<(double digit, const Complex& temporaryC);
    friend Complex operator>>(double digit, const Complex& temporaryC);
    friend Complex operator&(double digit, const Complex& temporaryC);
    friend Complex operator|(double digit, const Complex& temporaryC);
    friend Complex operator^(double digit, const Complex& temporaryC);

    //binary operators with keeping (complex digits mode)
    Complex& operator<<=(const Complex& other);
    Complex& operator>>=(const Complex& other);
    Complex& operator&=(const Complex& other);
    Complex& operator|=(const Complex& other);
    Complex& operator^=(const Complex& other);

    //binary operators (complex digits mode)
    Complex operator<<(const Complex& other);
    Complex operator>>(const Complex& other);
    Complex operator&(const Complex& other);
    Complex operator|(const Complex& other);
    Complex operator^(const Complex& other);

    //logic operators (double digits mode)
    bool operator&&(double digit);
    bool operator||(double digit);

    //reverse logic operators (double digits mode)
    friend bool operator&&(double digit, const Complex& temporaryC);
    friend bool operator||(double digit, const Complex& temporaryC);

    //logic operators (complex digits mode)
    bool operator&&(const Complex& other);
    bool operator||(const Complex& other);
    bool operator!();

    //operators for access to class member
    Complex& operator*();
    Complex* operator->();
    Complex* operator&();
    double operator->*(int element);

    double operator[](int index);
    const double operator[](int index) const;
    Complex operator()(double add...);
    Complex operator,(const Complex& other);

    //io operators
    friend std::ostream& operator<<(std::ostream& out, const Complex& temporaryC);
    friend std::istream& operator>>(std::istream& in, Complex& temporaryC);

};

std::ostream& operator<<(std::ostream& out, const Complex& temporaryC);
std::istream& operator>>(std::istream& in, Complex& temporaryC);

Complex operator+(double digit, const Complex& temporaryC);
Complex operator-(double digit, const Complex& temporaryC);