//
// Created by Hassan Attar on 2024-02-26.
//

#ifndef HASHING_UNIVERSALHASHFUNCTION_H
#define HASHING_UNIVERSALHASHFUNCTION_H
#include <functional>

template<typename DataType>
struct DefaultDataToNumConverter {
    unsigned long operator()(const DataType& data) {
        static std::hash<DataType> hash; // Identity Hash for integral types
        return hash(data);
    }
};

template<typename DataType, class DataToNumConverter = DefaultDataToNumConverter<DataType>>
class UniversalHash {
private:
    static size_t getClosestPrime(size_t maximumUniverseValue);
    static bool isPrime(size_t val);
    static std::function<size_t(DataType)> genHashFunc(size_t prime);
    size_t a;
    size_t b;
    size_t prime;
public:
    const static size_t PRIME;
    UniversalHash();
    UniversalHash(const DataType &maximumUniverseValue);
    UniversalHash(size_t maximumUniverseHash);
    UniversalHash(const UniversalHash &rhs) = default;
    UniversalHash(UniversalHash &&rhs) = default;

    size_t operator()(const DataType &key);

    inline static std::function<size_t(DataType)> getHashFunction();
    inline static std::function<size_t(DataType)> getHashFunction(const DataType &maximumUniverseValue);
    inline static std::function<size_t(DataType)> getHashFunction(size_t maximumUniverseHash);
};


#include "UniversalHashFunction.tpp"

#endif //HASHING_UNIVERSALHASHFUNCTION_H
