# Set Class

The Set class provides an implementation of a set data structure, a collection of unique elements. It supports various probing methods for handling collisions, such as linear probing, quadratic probing, double hashing, and separate chaining. This class allows efficient insertion, removal, and lookup operations on elements.

## Table of Contents
- [Usage](#usage)
- [Constructor](#constructor)
- [Methods](#methods)
- [Choosing Probing Methods & Hash Function](#probing-methods)
- [Examples](#examples)
- [Visuals (for Educational purposes)](#visuals)

## <a id="usage">Usage</a>

Include the "Set.h" header file in your project to use the Set class. The class is templated, allowing you to specify the type of elements stored in the set. You don't need to compile Set.tpp; Please make sure you compile RandomCoinFlip.cpp since the SkipList class is using it.
```cpp
#include "Set.h"
```

## <a id="constructor">Constructor</a>
The Set class provides several constructors:
- **Default Constructor:** Creates an empty set with default parameters.
- **Parameterized Constructor:** Creates a set based on the expected number of elements to be inserted.
- **Initializer List Constructor:** Initializes the set with elements from an initializer list.

## <a id="methods">Methods</a>
The Set class provides the following methods:
- **insert**: Inserts an element into the set.
- **remove**: Removes an element from the set.
- **contains**: Checks if a given element is present in the set.
- **display**: Displays the hash table of the set.
- **clear**: Removes all elements from the set.
- **getLoadingFactorThreshold**: Returns the loading factor threshold of the Set.
- **getCurrentLoadingFactor**: Returns the current loading factor of the Set.
- **getSize**: Returns the current number of elements in the set.
- **getCapacity**: Returns the current capacity of the set.
- **setLoadingFactorThreshold**: Sets the loading factor threshold for 

## <a id="probing-methods">Choosing Probing Methods & Hash Function</a>
The Set class supports various probing methods for handling collisions:
- **Linear Probing**
- **Quadratic Probing**
- **Double Hashing**
- **Separate Chaining**
You can specify the probing method using the template parameter `PROBING`. By default, Double Hashing is used. Example:
```cpp
Set<int, PROBING::QUADRATIC> mySet; // PROBING is an enum
```
You can also build your hashStruct to generate hashCodes for your data of type T. It defaults to std::hash. Example:
```cpp
Set<int, PROBING::Linear, MyHashStruct> mySet; // MyHashStruct is a struct with overloaded operator()
```

## <a id="examples">Examples</a>
### Basic Usage
```cpp
#include "Set.h"
#include <iostream>

int main() {
    Set<int> mySet;
    
    // Insert elements
    mySet.insert(10);
    mySet.insert(20);
    mySet.insert(30);
    
    // Display set contents
    mySet.display();
    
    // Remove element
    mySet.remove(20);
    
    // Check if element exists
    if (mySet.contains(10)) {
        std::cout << "Element 10 is present." << std::endl;
    }
    
    return 0;
}

```
### Using Custom Probing Method and Custom HashStruct
```cpp
#include <iostream>
#include "Set.h"

struct MyHash{
    size_t operator()(int data){
        size_t hashValue = data;
        hashValue ^= (hashValue << 13);
        hashValue ^= (hashValue >> 17);
        hashValue ^= (hashValue << 5);
        return hashValue;
    }
};

int main() {
    // Use quadratic probing
    Set<int, PROBING::QUADRATIC> mySet1;
    Set<int, PROBING::CHAINING, MyHash> mySet2; // using custom HashStruct to generate hash for the data
    
    // Insert elements
    mySet.insert(10);
    mySet.insert(20);
    
    // Display set contents
    mySet.display();
    
    return 0;
}

```
### Sample Problem Solved Efficiently Using Set:
Given a string, write a function that returns true, if the string has repeated characters, false otherwise.
- Solution 1: O(n^2) brute-force algorithm
- Solution 2: O(n*log(n)) more efficient algorithm
- Solution 3: O(n) as efficient as it gets.
```cpp
#include <iostream>
#include "Set.h"
#include "algorithm"
bool hasRepeatedCharactersBruteForce(const std::string &str){  // Time: O(N^2) ; Space: O(1)
    size_t size = str.size(), i, j;
    for(i = 0; i < size; i++){ // O(N)
        for(j = i + 1; j < size; j++){ // O(N)
            if(str[i] == str[j]) return true;
        }
    }
    return false;
}
bool hasRepeatedCharactersUsingSorting(const std::string &str){ // Time: O(N*Log(N)) ; Space: O(N) 
    std::string cp = str; // O(N)
    std::sort(cp.begin(), cp.end()); // O(N*Log(N))
    return std::adjacent_find(cp.begin(), cp.end()) != cp.end(); // O(N)
}
bool hasRepeatedCharactersUsingSet(const std::string &str){ // Time: O(N) ; Space: O(N) taking 2N space here, which is still linear
    Set<char, PROBING::QUADRATIC> set(str.size()); // O(1)
    for(const char &c : str){ // O(N)
        if(!set.insert(c)){ // O(1)
            return true;
        }
    }
    return false;
}
```

## <a id="visuals">Visuals (for Educational purposes)</a>
The display method shows the hash table behind the set. It is great for observing how different probing methods (or possibly different hash functions) deal with collisions.
### Different Probing Methods and Collisions: 
This example shows how choosing a different method of probing can reduce the possibility of forming clusters in the hash table. in all these examples, the same hash function is used.
```cpp
#include <iostream>
#include "Set.h"

template<PROBING ProbingMethod, typename hashStruct>
void insertValueWithCollision(Set<int, ProbingMethod, hashStruct> &set, int count){
    int val = 7;
    for(int i = 0; i < count; i++){
        set.insert(val + (i * set.getCapacity()));
    }
}
int main() {
    Set<int, PROBING::LINEAR> sl;
    insertValueWithCollision(sl, 5);
    sl.display();
    Set<int, PROBING::QUADRATIC> sq;
    insertValueWithCollision(sq, 5);
    sq.display();
    Set<int, PROBING::DOUBLE_HASHING> sd;
    insertValueWithCollision(sd, 5);
    sd.display();
    Set<int, PROBING::CHAINING> sc;
    insertValueWithCollision(sc, 5);
    sc.display();
    return 0;
}
```
#### **Output:**
<pre>
HASH TABLE : LINEAR PROBING
  0 [-]
  1 [-]
  2 [-]
  3 [-]
  4 [-]
  5 [-]
  6 [-]
  7 [7]
  8 [23]
  9 [39]
 10 [55]
 11 [71]
 12 [-]
 13 [-]
 14 [-]
 15 [-]

HASH TABLE : QUADRATIC PROBING
  0 [-]
  1 [-]
  2 [-]
  3 [-]
  4 [-]
  5 [-]
  6 [-]
  7 [55]
  8 [7]
  9 [-]
 10 [-]
 11 [-]
 12 [-]
 13 [-]
 14 [-]
 15 [39]
 16 [71]
 17 [-]
 18 [-]
 19 [-]
 20 [-]
 21 [-]
 22 [-]
 23 [23]

HASH TABLE : DOUBLE HASHING
  0 [-]
  1 [-]
  2 [-]
  3 [39]
  4 [-]
  5 [-]
  6 [-]
  7 [7]
  8 [-]
  9 [55]
 10 [-]
 11 [-]
 12 [-]
 13 [23]
 14 [-]
 15 [71]

HASH TABLE : CHAINING
  0 [* -> 7 -> 14 -> 21 -> 28 -> 35 -> *]
  1 [EMPTY]
  2 [EMPTY]
  3 [EMPTY]
  4 [EMPTY]
  5 [EMPTY]
  6 [EMPTY]
</pre>
### Custom Hash Function and Collisions: 
This example shows how choosing a suitable hash function for your data, can reduce the possibility of introducing clusters in the hash table.
```cpp
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
        size_t hashValue = static_cast<size_t>(data);
        // Multiplication by a prime number
        hashValue *= 2654435761;
        hashValue ^= (hashValue >> 17);
        hashValue *= 2654435761;
        hashValue ^= (hashValue >> 17);
        return hashValue;
    }
};

int main() {
    Set<int, PROBING::LINEAR, MyHash> sl;
    Set<int, PROBING::LINEAR> sl2;
    insertValueWithCollision(sl, 5);
    insertValueWithCollision(sl2, 5);
    sl.display();
    sl2.display();
    return 0;
}
```
#### **Output:**
<pre>
Custom Hash Function
HASH TABLE : LINEAR PROBING
  0 [-]
  1 [-]
  2 [23]
  3 [-]
  4 [-]
  5 [-]
  6 [-]
  7 [39]
  8 [-]
  9 [55]
 10 [-]
 11 [-]
 12 [-]
 13 [7]
 14 [71]
 15 [-]

Built in std::hash for int which is identity hash. (3 -> 3)
HASH TABLE : LINEAR PROBING
  0 [-]
  1 [-]
  2 [-]
  3 [-]
  4 [-]
  5 [-]
  6 [-]
  7 [7]
  8 [23]
  9 [39]
 10 [55]
 11 [71]
 12 [-]
 13 [-]
 14 [-]
 15 [-]
</pre>

