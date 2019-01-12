#pragma once

#include <vector>
#include <cstddef>
#include <iostream>
#include <memory>

typedef std::vector<int> vec;

class SquareMatrix {

    std::vector<int> mData;
    size_t mSize;

    int calculateDeterminant();

public:

    // main constructors
    SquareMatrix();
    SquareMatrix(SquareMatrix const &other);
    ~SquareMatrix() = default;

    SquareMatrix(int degree);
//    int getNext();
//    void add(int element);
//    int getMin() const;
//    void removeMin();

    // this block of operations use unitMatrix which is multiplied by OTHER
    SquareMatrix operator+(int other) const;
    SquareMatrix operator-(int other) const;
    SquareMatrix operator*(int other) const;
    SquareMatrix operator/(int other) const;
    SquareMatrix operator%(int other) const;

    SquareMatrix &operator+=(int other);
    SquareMatrix &operator-=(int other);
    SquareMatrix &operator*=(int other);
    SquareMatrix &operator/=(int other);
    SquareMatrix &operator%=(int other);

    // ---//--- use unitMatrix which is multiplied by 1 or -1
    SquareMatrix &operator++();
    SquareMatrix operator++(int);
    SquareMatrix &operator--();
    SquareMatrix operator--(int);


    // element by element actions
    SquareMatrix &operator=(const SquareMatrix &other);

    SquareMatrix operator+(SquareMatrix const &other);
    SquareMatrix operator-(SquareMatrix const &other);

    SquareMatrix operator~() const;
    SquareMatrix operator&(int other) const;
    SquareMatrix operator|(int other) const;
    SquareMatrix operator<<(int other) const;
    SquareMatrix operator>>(int other) const;

    SquareMatrix &operator&=(int other);
    SquareMatrix &operator|=(int other);
    SquareMatrix &operator<<=(int other);
    SquareMatrix &operator>>=(int other);


    // comparison operators use determinant
    bool operator<(SquareMatrix const &other) const;
    bool operator>(SquareMatrix const &other) const;
    bool operator==(SquareMatrix const &other) const;
    bool operator!=(SquareMatrix const &other) const;
    bool operator>=(SquareMatrix const &other) const;
    bool operator<=(SquareMatrix const &other) const;


    //
    int operator[](int ind) const;
    operator int();
    operator bool();
    SquareMatrix operator,(const SquareMatrix &other);
    SquareMatrix *operator->();
    void operator->*(int element);

    friend std::ostream &operator<<(std::ostream &stream, SquareMatrix const &heap);
    friend std::istream &operator>>(std::istream &stream, SquareMatrix &heap);

};