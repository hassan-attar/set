//
// Created by Hassan Attar on 2024-02-05.
//

#ifndef HASHING_MAP_H
#define HASHING_MAP_H
#include "iostream"
//
//
//enum PROBING {
//    LINEAR = 1,
//    QUADRATIC = 2,
//    DOUBLE_HASHING = 4
//};
//
//template<typename KeyType, typename ValueType, PROBING ProbingMethod = PROBING::LINEAR>
//class Map {
//private:
//    std::pair<KeyType, ValueType> **hashTable;
//    size_t size;
//    size_t capacity;
//    double loadingFactorThreshold;
//    PROBING PROBING_METHOD;
//    void rehash(bool increaseCap = false, size_t toCap = 0);
//    size_t primaryHash(const KeyType &key);
//    size_t secondaryHash(const size_t &value);
//    size_t findSpot(const KeyType &key);
//    size_t getNextIndex(int i, const size_t &hashIndex);
//public:
//    Map();
//    explicit Map(size_t numOfElement);
//    Map(const std::initializer_list<std::pair<KeyType, ValueType>> &list);
//
//    static const double DEFAULT_LOADING_FACTOR_THRESHOLD;
//    static const PROBING DEFAULT_PROBING_METHOD;
//    static const size_t DEFAULT_CAPACITY;
//
//    void insert(const std::pair<KeyType, ValueType> &pair);
//    void insert(const KeyType &key, const ValueType &value);
//    bool remove(const KeyType &key);
//    bool contains(const std::pair<KeyType, ValueType> &pair);
//    bool contains(const KeyType &key);
//    void display();
//    void reserve(int newCap);
//    void shrink(int newCap);
//    // getters
//    inline constexpr double getLoadingFactor();
//    inline constexpr size_t getSize();
//    inline constexpr size_t getCapacity();
//};


#endif //HASHING_MAP_H
