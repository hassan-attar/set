#include <iostream>
#include "Set.cpp"
#include "functional"
int main() {
    Set<int, PROBING::LINEAR> sl;
    sl.insert(7);
    sl.insert(7 + 16);
    sl.insert(7 + 32);
    sl.insert(7 + 48);
    sl.display();
    Set<int, PROBING::QUADRATIC> sq;
    sq.insert(7);
    sq.insert(7 + 16);
    sq.insert(7 + 32);
    sq.insert(7 + 48);
    sq.display();
    Set<int, PROBING::DOUBLE_HASHING> sd;
    sd.insert(7);
    sd.insert(7 + 16);
    sd.insert(7 + 32);
    sd.insert(7 + 48);
    sd.display();
}
