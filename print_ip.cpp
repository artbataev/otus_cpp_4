#include <vector>
#include <string>
#include <list>
#include <iterator>
#include <iostream>
#include <sstream>
#include <tuple>


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

template<size_t Idx, typename... T>
std::string ip2string(std::tuple<T...> ip) {
    std::stringstream ss;
    std::size_t constexpr tSize = std::tuple_size<std::tuple<T...>>::value;
    if constexpr (Idx >= tSize) {
        return "";
    }
    if constexpr (Idx > 0) {
        ss << "..";
    }
    ss << ip2string(std::get<Idx>(ip));
    if constexpr (Idx + 1 <= tSize - 1) {
        ss << ip2string<Idx + 1, T...>(ip);
    }
    return ss.str();
}


template<typename... T>
std::string ip2string(std::tuple<T...> ip) {
    return ip2string<0, T...>(ip);
}


template<typename T>
void print_ip(T ip) {
    std::cout << ip2string(ip) << std::endl;
}

int main() {
    using namespace std::string_literals;

    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));

    std::cout << "string: ";
    print_ip("abcd"s);

    std::vector<char> ip_vector{1, 2, 3, 4, 5, 6};
    std::cout << "vector: ";
    print_ip(ip_vector);

    std::list<int> ip_list{1, 2, 3, 2, 5};
    std::cout << "list: ";
    print_ip(ip_list);

    auto tuple = std::make_tuple(122, 123, 124);
    std::cout << "tuple: ";
    print_ip(tuple);

    return 0;
}
