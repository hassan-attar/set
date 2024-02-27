#include <iostream>
#include "Set.h"
#include "algorithm"
#include "UniversalHashFunction.h"
#include <vector>
/*
Sample Problem that we can solve efficiently using a Set (HashTable):
Given a string, write a function that returns true, if the string has repeated characters, false otherwise.
Solution 1> O(n^2) brute-force algorithm
Solution 2> O(nlog(n)) more efficient algorithm
Solution 3> O(n) as efficient as it gets.
*/
//bool hasRepeatedCharactersBruteForce(const std::string &str){  // Time: O(N^2) ; Space: O(1)
//    size_t size = str.size(), i, j;
//    for(i = 0; i < size; i++){ // O(N)
//        for(j = i + 1; j < size; j++){ // O(N)
//            if(str[i] == str[j]) return true;
//        }
//    }
//    return false;
//    //space O(1)
//}
//bool hasRepeatedCharactersUsingSorting(const std::string &str){ // Time: O(N*Log(N)) ; Space: O(N)
//    std::string cp = str; // O(N)
//    std::sort(cp.begin(), cp.end()); // O(N*Log(N))
//    return std::adjacent_find(cp.begin(), cp.end()) != cp.end(); // O(N)
//    // space O(N)
//}
//bool hasRepeatedCharactersUsingSet(const std::string &str){ // Time: O(N) ; Space: O(N)
//    Set<char, PROBING::QUADRATIC> set(str.size()); // O(1)
//    for(const char &c : str){ // O(N)
//        if(!set.insert(c)){ // O(1)
//            return true;
//        }
//    }
//    return false;
//    // space O(N), taking 2N space here, which is still linear
//}
//
//template<PROBING ProbingMethod, typename hashStruct>
//void insertValueWithCollision(Set<int, ProbingMethod, hashStruct> &set, int count){
//    int val = 10;
//    for(int i = 0; i < count; i++){
//        set.insert(val + (i * set.getCapacity()));
//    }
//}

//int main() {
//
//    Set<int, PROBING::LINEAR> sl;
//    insertValueWithCollision(sl, 5);
//    sl.display();
//    Set<int, PROBING::QUADRATIC> sq;
//    insertValueWithCollision(sq, 5);
//    sq.display();
//    Set<int, PROBING::DOUBLE_HASHING> sd;
//    insertValueWithCollision(sd, 5);
//    sd.display();
//
//    Set<int, PROBING::CHAINING> sc;
//    insertValueWithCollision(sc, 5);
//    sc.display();
//
//    std::string s("Hello World");
//    std::cout << "Find Duplicate char in: " << s << std::endl;
//    std::cout << "Brute Force: " << hasRepeatedCharactersBruteForce(s) << std::endl; // Time: O(N^2) ; Space: O(1)
//    std::cout << "Using Sorting: " << hasRepeatedCharactersUsingSorting(s) << std::endl; // Time: O(N*Log(N)) ; Space: O(N)
//    std::cout << "Using Set: " << hasRepeatedCharactersUsingSet(s) << std::endl; // Time: O(N) ; Space: O(N)
//    return 0;
//}

#include <iostream>
#include "Set.h"

//template<PROBING ProbingMethod, typename hashStruct>
//void insertValueWithCollision(Set<int, ProbingMethod, hashStruct> &set, int count){
//    int val = 7;
//    for(int i = 0; i < count; i++){
//        set.insert(val + (i * set.getCapacity()));
//    }
//}
//int main() {
//    Set<int, PROBING::LINEAR> sl;
//    insertValueWithCollision(sl, 5);
//    sl.display();
//    Set<int, PROBING::QUADRATIC> sq;
//    insertValueWithCollision(sq, 5);
//    sq.display();
//    Set<int, PROBING::DOUBLE_HASHING> sd;
//    insertValueWithCollision(sd, 5);
//    sd.display();
//    Set<int, PROBING::CHAINING> sc;
//    insertValueWithCollision(sc, 5);
//    sc.display();
//    return 0;
//}
//
//

#include <iostream>
#include "Set.h"
template<PROBING ProbingMethod, typename hashStruct>
void insertValueWithCollision(Set<int, ProbingMethod, hashStruct> &set, int count){
    int val = 7;
    for(int i = 0; i < count; i++){
        set.insert(val + (i * set.getCapacity()));
    }
}
struct MyHash{
    size_t operator()(int data) {
        static auto f = UniversalHash<int>::getHashFunction();
        return f(data);
    }
};

int main() {
//    UniversalHash<int, [](const int &val)-> unsigned long{
//        return 100UL;
//    }>s;
//    UniversalHashFunction<int>::getHashFunction();
//    std::vector<int, MyHash> f;

    Set<int, PROBING::QUADRATIC> sl;
    Set<int, PROBING::LINEAR> sl2;
    insertValueWithCollision(sl, 5);
    insertValueWithCollision(sl2, 5);
    MyHash m;
    std::cout << m(1000) <<std::endl;
    std::cout << m(2000) <<std::endl;
    std::cout << m(3000) <<std::endl;
    std::cout << m(1000) <<std::endl;
    sl.display();
//    sl2.display();
    return 0;
}