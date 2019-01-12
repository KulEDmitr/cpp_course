#include "SquareMatrix.h"

SquareMatrix::SquareMatrix() : mSize(9){
    mData.assign(mSize, 0);
}

SquareMatrix::SquareMatrix(SquareMatrix const &other) : mSize(other.mSize) {
    mData = other.mData;
}

SquareMatrix::SquareMatrix(int degree) : SquareMatrix(){
    for (int i = 0; i < 9; ++i) {
        mData[9 * i + 1] = degree;
    }
}

SquareMatrix SquareMatrix::operator+(int other) const {
    SquareMatrix ans(*this);
    for (int i = 0; i < 3; ++i) {
        ans.mData[i * 4] += other;
    }
    return ans;
}

SquareMatrix SquareMatrix::operator-(int other) const {
    SquareMatrix ans(*this);
    return ans + other;
}

SquareMatrix SquareMatrix::operator*(int other) const {
    SquareMatrix ans(*this);
    for (int i = 0; i < 9; ++i) {
        ans.mData[i] *= other;
    }
    return ans;
}

SquareMatrix SquareMatrix::operator/(int other) const {
    SquareMatrix ans(*this);
    for (int i = 0; i < 9; ++i) {
        ans.mData[i] /= other;
    }
    return ans;
}

SquareMatrix SquareMatrix::operator%(int other) const {
    SquareMatrix add(mSize, other);
    SquareMatrix ans(mSize);
    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++ j) {
            ans.mData[i * mSize + j] = mData[i * mSize + j] % add.mData[i * mSize + j];
        }
    }
    return ans;
}

SquareMatrix &SquareMatrix::operator+=(int other) {
    for (int i = 0; i < 9; ++i) {
        mData[i] += other;
    }
    return *this;
}
