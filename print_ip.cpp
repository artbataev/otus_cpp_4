#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <tuple>

#include "ip2string.h"

/**
 * Template function to print ip address: uses ip2string converter
 */
template<typename T>
void print_ip(T ip) {
    std::cout << ip2string(ip) << std::endl;
}

/**
 * Main function
 */
int main() {
    using namespace std::string_literals;

    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));

    std::cout << "string: ";
    print_ip("just-string"s);

    std::vector<char> ip_vector{'v', 'e', 'c', 't', 'o', 'r', 'o', 'f', 'c', 'h', 'a', 'r'};
    std::cout << "vector: ";
    print_ip(ip_vector);

    std::list<int> ip_list{1, 2, 3, 2, 5};
    std::cout << "list: ";
    print_ip(ip_list);

    std::cout << "tuple of char: ";
    print_ip(std::make_tuple('t', 'u', 'p', 'l', 'e', 'o', 'f', 'c', 'h', 'a', 'r'));

    std::cout << "tuple of strings: ";
    print_ip(std::make_tuple("tuple"s, "of"s, "strings"s));

    return 0;
}
