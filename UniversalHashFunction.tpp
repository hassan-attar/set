//
// Created by Hassan Attar on 2024-02-26.
//

#include "UniversalHashFunction.h"
#include <random>



template<typename DataType, class DataToNumConverter>
const size_t UniversalHash<DataType, DataToNumConverter>::PRIME = 999983UL;
// This universal hash function is capable of generating p(p-1) = 999,965,000,306 Unique hash function

template<typename DataType, class DataToNumConverter>
UniversalHash<DataType, DataToNumConverter>::UniversalHash(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> a_generator(1, prime - 1);
    std::uniform_int_distribution<size_t> b_generator(0, prime - 1);

    a = a_generator(gen);
    b = b_generator(gen);
    prime = PRIME;
}
template<typename DataType, class DataToNumConverter>
UniversalHash<DataType, DataToNumConverter>::UniversalHash(const DataType &maximumUniverseValue) {
    prime = getClosestPrime(DataToNumConverter(maximumUniverseValue));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> a_generator(1, prime - 1);
    std::uniform_int_distribution<size_t> b_generator(0, prime - 1);

    a = a_generator(gen);
    b = b_generator(gen);
}
template<typename DataType, class DataToNumConverter>
UniversalHash<DataType, DataToNumConverter>::UniversalHash(size_t maximumUniverseHash) {
    prime = getClosestPrime(maximumUniverseHash);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> a_generator(1, prime - 1);
    std::uniform_int_distribution<size_t> b_generator(0, prime - 1);

    a = a_generator(gen);
    b = b_generator(gen);
}


template<typename DataType, class DataToNumConverter>
size_t UniversalHash<DataType, DataToNumConverter>::operator()(const DataType &key) {
    static DataToNumConverter dataToNumConverter;
    return ((a * (dataToNumConverter(key))) + b) % prime;
}

template<typename DataType, class DataToNumConverter>
std::function<size_t(DataType)> UniversalHash<DataType, DataToNumConverter>::genHashFunc(
        size_t prime) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> a_generator(1, prime - 1);
    std::uniform_int_distribution<size_t> b_generator(0, prime - 1);

    size_t a = a_generator(gen);
    size_t b = b_generator(gen);
    return [a, b, prime](const DataType &key){
        static DataToNumConverter dataToNumConverter;
        return ((a * (dataToNumConverter(key))) + b) % prime;
    };
}

template<typename DataType, class DataToNumConverter>
std::function<size_t(DataType)> UniversalHash<DataType, DataToNumConverter>::getHashFunction() {
    return genHashFunc(PRIME);
}

template<typename DataType, class DataToNumConverter>
bool UniversalHash<DataType, DataToNumConverter>::isPrime(size_t n) {
    if(n == 1 || n == 0) return false;
    size_t squareRoot = static_cast<size_t>(std::sqrt(n));
    for(int i = 2; i <= squareRoot; i++){
        if(n % i == 0) return false;
    }
    return true;
}

template<typename DataType, class DataToNumConverter>
size_t UniversalHash<DataType, DataToNumConverter>::getClosestPrime(size_t maximumUniverseHash) {
    while(!isPrime(++maximumUniverseHash));
    return maximumUniverseHash;
}


template<typename DataType, class DataToNumConverter>
std::function<size_t(DataType)>
UniversalHash<DataType, DataToNumConverter>::getHashFunction(size_t maximumUniverseHash) {
    return genHashFunc(getClosestPrime(maximumUniverseHash));
}

template<typename DataType, class DataToNumConverter>
std::function<size_t(DataType)>
UniversalHash<DataType, DataToNumConverter>::getHashFunction(const DataType& maximumUniverseValue) {
    return genHashFunc(getClosestPrime(DataToNumConverter(maximumUniverseValue)));
}