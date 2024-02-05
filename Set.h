//
// Created by Hassan Attar on 2024-02-04.
//

#ifndef HASHING_SET_H
#define HASHING_SET_H
#include <bitset>
#include <functional>
#include <initializer_list>

enum PROBING {
    LINEAR = 1,
    QUADRATIC = 2,
    DOUBLE_HASHING = 4,
    CHAINING = 8
};

template<typename T, PROBING ProbingMethod = PROBING::LINEAR>
class Set {
private:
    T **hashTable;
    size_t size;
    size_t capacity;
    double loadingFactorThreshold;
    PROBING PROBING_METHOD;

    void rehash(bool increaseCap = false, size_t toCap = 0);
    size_t primaryHash(const T &value);
    size_t secondaryHash(const size_t& value);
    size_t findSpot(const T &value);
    size_t getNextIndex(int i, const size_t &hashIndex);
public:
    Set();
    explicit Set(size_t numOfElement);
    Set(const std::initializer_list<T> &list);

    static const double DEFAULT_LOADING_FACTOR_THRESHOLD;
    static const PROBING DEFAULT_PROBING_METHOD;
    static const size_t DEFAULT_CAPACITY;

    void insert(const T &value);
    bool remove(const T &value);
    bool contains(const T &value);
    void display();
    void reserve(int newCap);
    void shrink(int newCap);
    // getters
    inline constexpr double getLoadingFactor();
    inline constexpr size_t getSize();
    inline constexpr size_t getCapacity();
};


#endif //HASHING_SET_H
