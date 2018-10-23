#ifndef MY_VECTOR_IMPL_H
#define MY_VECTOR_IMPL_H

#include <cstring>
#include <memory>
#include "my_vector.h"

template <typename T>
void my_vector<T>::assign(size_t const new_len, T const element) {
    size_of_object = new_len;
    if (new_len > SIZE) {
        new(&big_obj) std::shared_ptr<std::vector<T>>(new std::vector<T>(new_len, element));
        is_on_heap = true;
    } else {
        for (size_t i = 0; i < new_len; ++i) {
            small_obj[i] = element;
        }
        is_on_heap = false;
    }
}

template <typename T>
my_vector<T>::my_vector() : size_of_object(0), is_on_heap(false) {}

template <typename T>
my_vector<T>::my_vector(size_t const size) {
    this->assign(size, 0);
}

template<typename T>
my_vector<T>::my_vector(const my_vector<T> &other) :
        is_on_heap(other.is_on_heap), size_of_object(other.size_of_object) {
    if (is_on_heap) {
        big_obj = std::make_shared<std::vector<T>>(*other.big_obj);
    } else {
        for (size_t i = 0; i < size_of_object; ++i) {
            small_obj[i] = other.small_obj[i];
        }
    }
}

template <typename T>
void my_vector<T>::resize(size_t new_len) {
    if (is_on_heap && size_of_object > SIZE) {
        check_unique();
    }
    if (new_len <= SIZE) {
        if (is_on_heap) {
            for (size_t i = 0; i < new_len; ++i) {
                small_obj[i] = big_obj->operator[](i);
            }
            big_obj.reset();
        } else {
            for (size_t i = size_of_object; i < new_len; ++i) {
                small_obj[i] = 0;
            }
        }
        is_on_heap = false;
    } else {
        if (is_on_heap) {
            big_obj = std::make_shared<std::vector<T>>(*big_obj);
        } else {
            new(&big_obj) std::shared_ptr<std::vector<T>>(new std::vector<T>(1, small_obj[0]));
            for (size_t i = 1; i < new_len; ++i) {
                big_obj->push_back((i < size_of_object) ? small_obj[i] : 0);
            }
        }
        is_on_heap = true;
    }
    size_of_object = new_len;
}

template <class T>
void my_vector<T>::check_unique() {
    if (!big_obj.unique()) {
        big_obj = std::make_shared<std::vector<T>>(*big_obj);
    }
}

template <typename T>
my_vector<T>::~my_vector() {
    if (is_on_heap) {
        big_obj.reset();
    }
}

template <typename T>
size_t my_vector<T>::size() const {
    return size_of_object;
}

template <typename T>
T &my_vector<T>::back() {
    if (is_on_heap) {
        check_unique();
    }
    return this->operator[](size_of_object - 1);
}

template <typename T>
T my_vector<T>::back() const {
    return this->operator[](size_of_object - 1);
}

template <typename T>
void my_vector<T>::push_back(T element) {
    if (is_on_heap) {
        check_unique();
    }
    if (size_of_object < SIZE) {
        small_obj[size_of_object++] = element;
    } else {
        if (size_of_object == SIZE) {
            resize(size_of_object + 1);
            big_obj->operator[](size_of_object - 1) = element;
        } else {
            big_obj->push_back(element);
            ++size_of_object;
        }
    }
}

template <typename T>
void my_vector<T>::pop_back() {
    if (is_on_heap) {
        check_unique();
    }
    --size_of_object;
    if (size_of_object > SIZE) {
        big_obj->pop_back();
    } else if (is_on_heap) {
        resize(size_of_object);
    }
}

template <typename T>
T my_vector<T>::operator[](size_t id) const {
    if (is_on_heap) {
        return big_obj->operator[](id);
    }
    return small_obj[id];
}

template <typename T>
T &my_vector<T>::operator[](size_t id) {
    if (is_on_heap) {
        check_unique();
        return big_obj->operator[](id);
    }
    return small_obj[id];
}

template <typename T>
my_vector<T> &my_vector<T>::operator=(const my_vector<T> &other) {
    is_on_heap = other.is_on_heap;
    size_of_object = other.size_of_object;
    if (is_on_heap) {
        big_obj = std::make_shared<std::vector<T>>(*other.big_obj);
    } else {
        for (size_t i = 0; i < size_of_object; ++i) {
            small_obj[i] = other.small_obj[i];
        }
    }
    return *this;
}

template<typename T>
bool my_vector<T>::operator==(my_vector const &other) const {
    if (size() != other.size()) {
        return false;
    }
    if (is_on_heap) {
        return *big_obj == *other.big_obj;
    } else {
        for (size_t i = 0; i < size(); ++i) {
            if (small_obj[i] != other.small_obj[i]) {
                return false;
            }
        }
        return true;
    }
}

#endif