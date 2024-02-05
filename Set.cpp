//
// Created by Hassan Attar on 2024-02-04.
//

#include "Set.h"
#include <functional>
#include <iostream>
#include <cmath>
#include <iomanip>

template<typename T, PROBING ProbingMethod>
const double Set<T, ProbingMethod>::DEFAULT_LOADING_FACTOR_THRESHOLD = 0.70;

template<typename T, PROBING ProbingMethod>
const PROBING Set<T, ProbingMethod>::DEFAULT_PROBING_METHOD = PROBING::LINEAR;

template<typename T, PROBING ProbingMethod>
const size_t Set<T, ProbingMethod>::DEFAULT_CAPACITY = 16;

template<typename T, PROBING ProbingMethod>
Set<T, ProbingMethod>::Set() : Set((size_t)DEFAULT_CAPACITY / 2){}

template<typename T, PROBING ProbingMethod>
Set<T, ProbingMethod>::Set(size_t numOfElement)
: hashTable{new T*[numOfElement * 2]}, size{0}, capacity{numOfElement * 2},
loadingFactorThreshold{DEFAULT_LOADING_FACTOR_THRESHOLD}, PROBING_METHOD{ProbingMethod} {
    for(int i = 0; i < capacity; i++){
        hashTable[i] = nullptr;
    }
}

template<typename T, PROBING ProbingMethod>
Set<T, ProbingMethod>::Set(const std::initializer_list<T> &list): Set(list.size()) {
    for(const T& x: list){
        insert(x);
    }
}

template<typename T, PROBING ProbingMethod>
size_t Set<T, ProbingMethod>::primaryHash(const T &value) {
    static std::hash<T> hashFunc;
    return hashFunc(value) % capacity;
}
template<typename T, PROBING ProbingMethod>
size_t Set<T, ProbingMethod>::secondaryHash(const size_t &value) {
    static std::hash<size_t> doubleHashFunc;
    static const size_t prime = 37;
    return (37 + doubleHashFunc(value)) % 37;
}

template<typename T, PROBING ProbingMethod>
void Set<T, ProbingMethod>::insert(const T &value) {
    size_t index = findSpot(value);
    if(hashTable[index]) return;
    if(((double)(size + 1)) / capacity > loadingFactorThreshold){
        rehash(true, capacity * 2);
        hashTable[findSpot(value)] = new T(value);
    } else {
        hashTable[index] = new T(value);
    }
    size++;
}

template<typename T, PROBING ProbingMethod>
bool Set<T, ProbingMethod>::contains(const T &value) {
    return hashTable[findSpot(value)] != nullptr;
}

template<typename T, PROBING ProbingMethod>
size_t Set<T, ProbingMethod>::getNextIndex(int i, const size_t &hashIndex) {
    if(PROBING_METHOD & PROBING::LINEAR){
        return (hashIndex + i) % capacity;
    } else if(PROBING_METHOD & PROBING::QUADRATIC){
        return (hashIndex + (int)std::round(std::pow(i, 2))) % capacity;
    } else {
        return (hashIndex + i * secondaryHash(hashIndex)) % capacity;
    }
}

template<typename T, PROBING ProbingMethod>
size_t Set<T, ProbingMethod>::findSpot(const T &value) {
    size_t hashIndex, index, i{1};
    index = hashIndex = primaryHash(value);
    while(hashTable[index] && (*hashTable[index]) != value){
        index = getNextIndex(i, hashIndex);
        i++;
    }
    return index;
}

template<typename T, PROBING ProbingMethod>
inline constexpr double Set<T, ProbingMethod>::getLoadingFactor() {
    return ((double) size / capacity);
}
template<typename T, PROBING ProbingMethod>
inline constexpr size_t Set<T, ProbingMethod>::getSize() {
    return size;
}
template<typename T, PROBING ProbingMethod>
inline constexpr size_t Set<T, ProbingMethod>::getCapacity() {
    return capacity;
}


template<typename T, PROBING ProbingMethod>
bool Set<T, ProbingMethod>::remove(const T &value) {
    size_t index = findSpot(value);
    if(!hashTable[index]){
        return false;
    }
    delete hashTable[index];
    hashTable[index] = nullptr;
    rehash();
    size--;
    return true;
}

template<typename T, PROBING ProbingMethod>
void Set<T, ProbingMethod>::rehash(bool increaseCap, size_t toCap) {
    T **tempHashTable = hashTable;
    size_t oldCap = capacity;
    if(increaseCap) capacity = toCap ? toCap : capacity * 2;
    hashTable = new T*[capacity];

    for (size_t i = 0; i < capacity;i++){
        hashTable[i] = nullptr;
    }

    for(size_t i = 0; i < oldCap; i++){
        if(tempHashTable[i]){
            hashTable[findSpot(*tempHashTable[i])] = tempHashTable[i];
        }
    }
}
template<typename T, PROBING ProbingMethod>
void Set<T, ProbingMethod>::display() {
    std::cout << "HASH TABLE : ";
    if(PROBING_METHOD & PROBING::LINEAR){
        std::cout << "LINEAR PROBING";
    } else if (PROBING_METHOD & PROBING::QUADRATIC){
        std::cout << "QUADRATIC PROBING";
    } else {
        std::cout << "DOUBLE HASHING";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < capacity; i++){
        std::cout << std::setw(3) << i << " [";
        if(hashTable[i]){
            std::cout << std::setw(6) << *hashTable[i];
        }else {
            std::cout << "------";
        }
        std::cout << "]\n";
    }
    std::cout << std::endl;
}

template<typename T, PROBING ProbingMethod>
void Set<T, ProbingMethod>::reserve(int newCap) {
    if(newCap <= capacity) return;
    rehash(true, newCap);
}
template<typename T, PROBING ProbingMethod>
void Set<T, ProbingMethod>::shrink(int newCap){
    if(((double) size / newCap) > loadingFactorThreshold) return;
    rehash(true, newCap);
}