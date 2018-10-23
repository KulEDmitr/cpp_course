#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <vector>
#include <memory>
#include <cstdint>

const int SIZE = 256;

template<typename T>
struct my_vector {

    void assign(size_t new_len, T element);

    my_vector();
    explicit my_vector(size_t i);
    my_vector(my_vector<T> const &other);

    size_t size() const;
    void resize(size_t new_len);
    void check_unique();

    ~my_vector();

    T &back();
    T back() const;
    void push_back(T element);
    void pop_back();

    T operator[](size_t id) const;
    T &operator[](size_t id);

    my_vector<T> &operator=(my_vector<T> const &other);

    bool operator==(my_vector const &other) const ;

private:
    size_t size_of_object;
    bool is_on_heap;

    T small_obj[SIZE];
    std::shared_ptr<std::vector<T>> big_obj;

};

#include "my_vector_impl.h"
#endif