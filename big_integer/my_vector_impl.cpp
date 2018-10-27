#include <cstring>
#include <memory>
#include "my_vector.h"

typedef std::vector<uint32_t> vec_u32;

void my_vector::assign(size_t const new_len, uint32_t const element) {
    if (is_on_heap) {
        check_unique();
    }
    size_of_object = new_len;
    if (new_len > SIZE) {
        new(&big_obj) std::shared_ptr<vec_u32>(new vec_u32(new_len, element));
        is_on_heap = true;
    } else {
        for (size_t i = 0; i < new_len; ++i) {
            small_obj[i] = element;
        }
        is_on_heap = false;
    }
}

my_vector::my_vector() : size_of_object(0), is_on_heap(false) {}

my_vector::my_vector(size_t const size) {
    this->assign(size, 0);
}

my_vector::my_vector(const my_vector &other) :
        is_on_heap(other.is_on_heap), size_of_object(other.size_of_object) {
    if (is_on_heap) {
        big_obj = std::make_shared<vec_u32>(*other.big_obj);
    } else {
        for (size_t i = 0; i < size_of_object; ++i) {
            small_obj[i] = other.small_obj[i];
        }
    }
}

void my_vector::resize(size_t new_len) {
    if (is_on_heap) {
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
            big_obj = std::make_shared<vec_u32>(*big_obj);
        } else {
            new(&big_obj) std::shared_ptr<vec_u32>(new vec_u32(1, small_obj[0]));
            for (size_t i = 1; i < new_len; ++i) {
                big_obj->push_back((i < size_of_object) ? small_obj[i] : 0);
            }
        }
        is_on_heap = true;
    }
    size_of_object = new_len;
}

void my_vector::check_unique() {
    if (!big_obj.unique()) {
        big_obj = std::make_shared<vec_u32>(*big_obj);
    }
}

my_vector::~my_vector() {
    if (is_on_heap) {
        big_obj.reset();
    }
}

size_t my_vector::size() const {
    return size_of_object;
}

uint32_t &my_vector::back() {
    if (is_on_heap) {
        check_unique();
    }
    return this->operator[](size_of_object - 1);
}

const uint32_t &my_vector::back() const {
    return this->operator[](size_of_object - 1);
}

void my_vector::push_back(uint32_t element) {
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

void my_vector::pop_back() {
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

const uint32_t &my_vector::operator[](size_t id) const {
    if (is_on_heap) {
        return big_obj->operator[](id);
    }
    return small_obj[id];
}

uint32_t &my_vector::operator[](size_t id) {
    if (is_on_heap) {
        check_unique();
        return big_obj->operator[](id);
    }
    return small_obj[id];
}

my_vector &my_vector::operator=(const my_vector &other) {
    is_on_heap = other.is_on_heap;
    size_of_object = other.size_of_object;
    if (is_on_heap) {
        big_obj = std::make_shared<vec_u32>(*other.big_obj);
    } else {
        for (size_t i = 0; i < size_of_object; ++i) {
            small_obj[i] = other.small_obj[i];
        }
    }
    return *this;
}

bool my_vector::operator==(my_vector const &other) const {
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