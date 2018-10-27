#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <vector>
#include <memory>
#include <cstdint>

const int SIZE = 128;

struct my_vector {

    void assign(size_t new_len, uint32_t element);

    my_vector();
    explicit my_vector(size_t i);
    my_vector(my_vector const &other);

    size_t size() const;
    void resize(size_t new_len);
    void check_unique();

    ~my_vector();

    uint32_t &back();
    const uint32_t& back() const;
    void push_back(uint32_t element);
    void pop_back();

    const uint32_t &operator[](size_t id) const;
    uint32_t &operator[](size_t id);

    my_vector &operator=(my_vector const &other);

    bool operator==(my_vector const &other) const ;

private:
    size_t size_of_object;
    bool is_on_heap = false;

    uint32_t small_obj[SIZE];
    std::shared_ptr<std::vector<uint32_t>> big_obj;
};

#endif