#include <iostream>
#include "Set.h"
#include "functional"
int main() {
    Set<int, PROBING::CHAINING> s;
    s.insert(2);
    s.insert(6);
    s.insert(42);
    s.insert(4);
    s.insert(843);
    s.insert(782);
    s.insert(-32);
    s.insert(24);
    s.insert(-1231);
    s.insert(12345);
    s.insert(122);
    s.insert(984);
    s.display();
    std::cout << "LOADING_FACTOR: " << s.getLoadingFactor() << std::endl;
    std::cout << "S" << std::endl;
    s.display();
    Set<int, PROBING::CHAINING> m(std::move(s));
    std::cout << "S AFTER" << std::endl;
    s.display();
    std::cout << "MOVE" << std::endl;
    m.display();
    std::cout << "S AFTER INSERT" << std::endl;
    s.insert(12345);
    s.insert(122);
    s.display();

    s = std::move(m);

    std::cout << "m AFTER MOVE" << std::endl;
    m.display();
    std::cout << "S AFTER" << std::endl;
    s.display();
}



/*
Sample Problem that we can solve efficiently using a Set (HashTable):
Given a string, write a function that returns true, if the string has repeated characters, false otherwise.
Solution 1> O(n^2) brute-force algorithm
Solution 2> O(nlog(n)) more efficient algorithm
Solution 3> O(n) as efficient as it gets.
*/