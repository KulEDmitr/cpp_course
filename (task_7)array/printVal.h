#pragma once

#include <iostream>
#include <utility>
#include <tuple>

template<typename T>
void print_values(T first);

template<class FirstT, class ...Ts>
void print_values(FirstT first, Ts... other);

template<std::size_t I, class T, class ...Ts>
struct nth_element_impl {
    using type = typename nth_element_impl<I - 1, Ts...>::type;
};

template<class T, class ...Ts>
struct nth_element_impl<0, T, Ts...> {
    using type = T;
};

template<std::size_t I, class ...Ts>
using nth_element = typename nth_element_impl<I, Ts...>::type;

template<size_t FirstPos, size_t SecPos, class ... Ts>
std::pair<nth_element<FirstPos, Ts...>, nth_element<SecPos, Ts...>> makePair(std::tuple<Ts...> const& t);

//todo ostream operator for random pair

#include "printVal.hpp"