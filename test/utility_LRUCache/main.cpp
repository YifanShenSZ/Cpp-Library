#include <iostream>

#include <CppLibrary/utility/LRUCache.hpp>

void case1() {
    CL::utility::LRUCache<int, int> cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(3, 3);
    std::cout << cache.get(3) - 3 << ' ';
    cache.put(4, 4);
    std::cout << cache.get(3) - 3 << ' ';
    std::cout << cache.get(4) - 4 << ' ';
}

void case2() {
    CL::utility::LRUCache<int, int> cache(3);
    cache.put(2, 2);
    cache.put(1, 1);
    cache.put(3, 3);
    cache.get(1);
    cache.get(2);
    cache.put(4, 4);
    std::cout << cache.get(2) - 2 << ' ';
    std::cout << cache.get(4) - 4 << ' ';
    std::cout << cache.get(1) - 1 << ' ';
}

int main() {
    case1();
    std::cout << '\n';

    case2();
    std::cout << '\n';
}