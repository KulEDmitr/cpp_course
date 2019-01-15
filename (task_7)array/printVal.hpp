#include "printVal.h"

template<typename T>
void print_values(T first) {
    std::cout << typeid(first).name() << ": " << first << std::endl;
}

template<typename FirstT, typename... Ts>
void print_values(FirstT first, Ts... other) {
    std::cout << typeid(first).name() << ": " << first << std::endl;
    print_values(other...);
}

template<size_t FirstPos, size_t SecPos, typename... Ts>
std::pair<nth_element<FirstPos, Ts...>, nth_element<SecPos, Ts...>> makePair(std::tuple<Ts...> const& t) {
    return std::make_pair(std::get<FirstPos>(t), std::get<SecPos>(t));
}