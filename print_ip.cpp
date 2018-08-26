#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <tuple>

#include "ip2string.h"


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

    std::cout << "tuple of char: ";
    print_ip(std::make_tuple<char, char, char>(122, 123, 124));

    std::cout << "tuple of strings: ";
    print_ip(std::make_tuple("one"s, "two"s));

    return 0;
}
