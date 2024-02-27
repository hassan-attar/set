//
// Created by Hassan Attar on 2024-02-04.
//

#ifndef HASHING_SET_H
#define HASHING_SET_H
#include <functional>
#include <initializer_list>
#include "./skiplist/SkipList.h"
#include "UniversalHashFunction.h"

enum PROBING {
    LINEAR = 1,
    QUADRATIC = 2,
    DOUBLE_HASHING = 4,
    CHAINING = 8
};

template<typename T, PROBING ProbingMethod = PROBING::DOUBLE_HASHING,
        typename PrimaryHashStruct = UniversalHash<T>, typename SecondaryHashStruct = UniversalHash<T>>
class Set {
private:
    typename std::conditional<ProbingMethod == PROBING::CHAINING, SkipList<T>*, T**>::type hashTable;
    size_t size;
    size_t capacity;
    double loadingFactorThreshold;
    PROBING PROBING_METHOD;

    void rehash(bool increaseCap = false, size_t toCap = 0);
    size_t primaryHash(const T &value);
    size_t secondaryHash(const T& value);
    size_t findSpot(const T &value);
    size_t getNextIndex(int i, const size_t &hashIndex, const T &value);
public:
    Set();
    explicit Set(size_t numOfElement);
    Set(const std::initializer_list<T> &list);
    Set(const Set &rhs);
    Set(Set &&rhs) noexcept;
    Set &operator=(const Set &rhs);
    Set &operator=(Set &&rhs) noexcept;
    ~Set();

    // Static constants
    static const double OPEN_ADDRESSING_DEFAULT_MAX_LOADING_FACTOR_THRESHOLD;
    static const double OPEN_ADDRESSING_DEFAULT_MIN_LOADING_FACTOR_THRESHOLD;
    static const double SEPARATE_CHAINING_DEFAULT_MAX_LOADING_FACTOR_THRESHOLD;
    static const double SEPARATE_CHAINING_DEFAULT_MIN_LOADING_FACTOR_THRESHOLD;
    static const PROBING DEFAULT_PROBING_METHOD;
    static const size_t OPEN_ADDRESSING_DEFAULT_CAPACITY;
    static const size_t SEPARATE_CHAINING_DEFAULT_CAPACITY;
    static const size_t SEPARATE_CHAINING_DEFAULT_MAX_CHAIN_SIZE;

    bool insert(const T &value);
    bool remove(const T &value);
    bool contains(const T &value);
    void display();
    void clear();
    // getters
    inline constexpr double getLoadingFactorThreshold();
    inline constexpr double getCurrentLoadingFactor();
    inline constexpr size_t getSize();
    inline constexpr size_t getCapacity();

    // setter
    void setLoadingFactorThreshold(double val);

};

#include "Set.tpp"

#endif //HASHING_SET_H
