#pragma once

#include <sstream>
#include <iterator>
#include <type_traits>
#include <tuple>


/**
 * ip2string convertor for integral types (e.g. int, char, etc.)
 */
template<typename T,
        typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
std::string ip2string(const T& ip) {
    int num_bytes = sizeof(ip);
    static const int mask = (2 << 7) - 1;
    std::stringstream ss;

    for (int i = num_bytes - 1; i >= 0; i--) {
        ss << (ip >> (i * 8) & mask);
        if (i > 0)
            ss << ".";
    }
    return ss.str();
}


/**
 * ip2string convertor for iterable containers, e.g. vector, list
 */
template<typename Container,
        typename = decltype(std::declval<Container>().cbegin()),
        typename = decltype(std::declval<Container>().cend())>
std::string ip2string(const Container& ip) {
    std::stringstream ss;
    for (auto item_pointer = ip.cbegin(); item_pointer != ip.cend(); item_pointer++) {
        if (item_pointer != ip.cbegin())
            ss << "..";
        ss << ip2string(*item_pointer);
    }
    return ss.str();
}


/**
 * ip2string convertor for string: just returning same string
 */
std::string ip2string(std::string ip) {
    return ip;
}


/**
 * helper function for ip2string: recursively parse tuple using indices
 */
template<size_t Idx, typename... T>
std::string ip2string(std::tuple<T...> ip) {
    std::stringstream ss;
    std::size_t constexpr tSize = std::tuple_size<std::tuple<T...>>::value;
    if constexpr (Idx > 0) {
        ss << "..";
    }
    ss << ip2string(std::get<Idx>(ip));
    if constexpr (Idx + 1 <= tSize - 1) {
        ss << ip2string<Idx + 1, T...>(ip);
    }
    return ss.str();
}

/**
 * ip2string convertor for tuple: use parsing from index 0
 */
template<typename... T>
std::string ip2string(std::tuple<T...> ip) {
    return ip2string<0, T...>(ip);
}
