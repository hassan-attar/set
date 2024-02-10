//
// Created by Hassan Attar on 2024-02-04.
//

#include "Set.h"
#include <functional>
#include <iostream>
#include <cmath>
#include <iomanip>

template<typename T, PROBING ProbingMethod, typename hashStruct>
const double Set<T, ProbingMethod, hashStruct>::OPEN_ADDRESSING_DEFAULT_MAX_LOADING_FACTOR_THRESHOLD = 0.70;

template<typename T, PROBING ProbingMethod, typename hashStruct>
const double Set<T, ProbingMethod, hashStruct>::OPEN_ADDRESSING_DEFAULT_MIN_LOADING_FACTOR_THRESHOLD = 0.40;

template<typename T, PROBING ProbingMethod, typename hashStruct>
const double Set<T, ProbingMethod, hashStruct>::SEPARATE_CHAINING_DEFAULT_MAX_LOADING_FACTOR_THRESHOLD = 5; // 5 items in each bucket max

template<typename T, PROBING ProbingMethod, typename hashStruct>
const double Set<T, ProbingMethod, hashStruct>::SEPARATE_CHAINING_DEFAULT_MIN_LOADING_FACTOR_THRESHOLD = 2.5;

template<typename T, PROBING ProbingMethod, typename hashStruct>
const size_t Set<T, ProbingMethod, hashStruct>::SEPARATE_CHAINING_DEFAULT_MAX_CHAIN_SIZE = 10; // max 10 items in each chain

template<typename T, PROBING ProbingMethod, typename hashStruct>
const PROBING Set<T, ProbingMethod, hashStruct>::DEFAULT_PROBING_METHOD = PROBING::LINEAR;

template<typename T, PROBING ProbingMethod, typename hashStruct>
const size_t Set<T, ProbingMethod, hashStruct>::OPEN_ADDRESSING_DEFAULT_CAPACITY = 16;

template<typename T, PROBING ProbingMethod, typename hashStruct>
const size_t Set<T, ProbingMethod, hashStruct>::SEPARATE_CHAINING_DEFAULT_CAPACITY = 7;


// CONSTRUCTORS
template<typename T, PROBING ProbingMethod, typename hashStruct>
Set<T, ProbingMethod, hashStruct>::Set():Set((size_t)OPEN_ADDRESSING_DEFAULT_CAPACITY / 2){}

// Main Constructor
template<typename T, PROBING ProbingMethod, typename hashStruct>
Set<T, ProbingMethod, hashStruct>::Set(size_t numOfElementToExpect)
: hashTable{nullptr},
size{0}, capacity{numOfElementToExpect * 2},
loadingFactorThreshold{OPEN_ADDRESSING_DEFAULT_MAX_LOADING_FACTOR_THRESHOLD}, PROBING_METHOD{ProbingMethod} {
    if constexpr (ProbingMethod & PROBING::CHAINING){
        SkipList<T>::setDefaultObjectMaxLevel(3);
        hashTable = new SkipList<T>[SEPARATE_CHAINING_DEFAULT_CAPACITY];
        capacity = SEPARATE_CHAINING_DEFAULT_CAPACITY;
        loadingFactorThreshold = SEPARATE_CHAINING_DEFAULT_MAX_LOADING_FACTOR_THRESHOLD;
    } else {
        hashTable = new T*[numOfElementToExpect * 2];
        for(int i = 0; i < capacity; i++){
            hashTable[i] = nullptr;
        }
    }

}

template<typename T, PROBING ProbingMethod, typename hashStruct>
Set<T, ProbingMethod, hashStruct>::Set(const std::initializer_list<T> &list): Set(list.size()) {
    for(const T& x: list){
        insert(x);
    }
}

// Copy Constructor / Assignment
template<typename T, PROBING ProbingMethod, typename hashStruct>
Set<T, ProbingMethod, hashStruct>::Set(const Set<T, ProbingMethod, hashStruct> &rhs)
: hashTable{nullptr},
size{rhs.size}, capacity{rhs.capacity},
loadingFactorThreshold{rhs.loadingFactorThreshold}, PROBING_METHOD{ProbingMethod}{
    if constexpr (ProbingMethod & PROBING::CHAINING){
        SkipList<T>::setDefaultObjectMaxLevel(3);
        hashTable = new SkipList<T>[rhs.capacity];
        for(int i = 0; i < capacity; i++){
            hashTable[i] = rhs.hashTable[i]; // copy assignment operator
        }
        loadingFactorThreshold = rhs.loadingFactorThreshold;
    } else {
        hashTable = new T*[rhs.capacity];
        for(int i = 0; i < capacity; i++){
            hashTable[i] = *(rhs.hashTable[i]);
        }
    }
}
template<typename T, PROBING ProbingMethod, typename hashStruct>
Set<T, ProbingMethod, hashStruct> &Set<T, ProbingMethod, hashStruct>::operator=(const Set<T, ProbingMethod, hashStruct> &rhs) {
    if(this != &rhs) {
        if constexpr (ProbingMethod & PROBING::CHAINING) {
            clear();
            SkipList<T>::setDefaultObjectMaxLevel(3);
            hashTable = new SkipList<T>[rhs.capacity];
            for (int i = 0; i < capacity; i++) {
                hashTable[i] = rhs.hashTable[i]; // copy assignment operator
            }
            loadingFactorThreshold = rhs.loadingFactorThreshold;
            capacity = rhs.capacity;
            size = rhs.size;
        } else {
            hashTable = new T *[rhs.capacity];
            for (int i = 0; i < capacity; i++) {
                hashTable[i] = *(rhs.hashTable[i]);
            }
            loadingFactorThreshold = rhs.loadingFactorThreshold;
            capacity = rhs.capacity;
            size = rhs.size;
        }
    }
    return *this;
}

// Move Constructor / Assignment
template<typename T, PROBING ProbingMethod, typename hashStruct>
Set<T, ProbingMethod, hashStruct>::Set(Set<T, ProbingMethod, hashStruct> &&rhs) noexcept
:hashTable{nullptr},
 size{rhs.size}, capacity{rhs.capacity},
 loadingFactorThreshold{rhs.loadingFactorThreshold}, PROBING_METHOD{ProbingMethod}{
    if constexpr (ProbingMethod & PROBING::CHAINING){
        SkipList<T>::setDefaultObjectMaxLevel(3);
        hashTable = rhs.hashTable;
        rhs.hashTable = nullptr;
        loadingFactorThreshold = rhs.loadingFactorThreshold;
        rhs.capacity = 0;
        size = rhs.size;
        rhs.size = 0;
    } else {
        hashTable = new T*[rhs.capacity];
        for(int i = 0; i < capacity; i++){
            hashTable[i] = rhs.hashTable[i];
            rhs.hashTable[i] = nullptr;
        }
    }
}
template<typename T, PROBING ProbingMethod, typename hashStruct>
Set<T, ProbingMethod, hashStruct> &Set<T, ProbingMethod, hashStruct>::operator=(Set<T, ProbingMethod, hashStruct> &&rhs) noexcept{
    if constexpr (ProbingMethod & PROBING::CHAINING){
        clear();
        SkipList<T>::setDefaultObjectMaxLevel(3);
        hashTable = rhs.hashTable;
        rhs.hashTable = nullptr;
        loadingFactorThreshold = rhs.loadingFactorThreshold;
        capacity = rhs.capacity;
        rhs.capacity = 0;
        size = rhs.size;
        rhs.size = 0;
    } else {
        clear();
        hashTable = new T*[rhs.capacity];
        for(int i = 0; i < capacity; i++){
            hashTable[i] = rhs.hashTable[i];
            rhs.hashTable[i] = nullptr;
        }
        loadingFactorThreshold = rhs.loadingFactorThreshold;
        capacity = rhs.capacity;
        rhs.capacity = 0;
        size = rhs.size;
        rhs.size = 0;
    }
    return *this;
}

// Destructor / Clear
template<typename T, PROBING ProbingMethod, typename hashStruct>
Set<T, ProbingMethod, hashStruct>::~Set(){
    clear();
}
template<typename T, PROBING ProbingMethod, typename hashStruct>
void Set<T, ProbingMethod, hashStruct>::clear() {
    if constexpr (ProbingMethod & PROBING::CHAINING){
        delete [] hashTable;
        hashTable = nullptr;
        capacity = 0;
        size = 0;
    } else {
        for(int i = 0; i < capacity; ++i){
            delete hashTable[i];
        }
        delete [] hashTable;
        hashTable = nullptr;
        capacity = 0;
        size = 0;
    }
}


// Hash Functions
template<typename T, PROBING ProbingMethod, typename hashStruct>
size_t Set<T, ProbingMethod, hashStruct>::primaryHash(const T &value) {
    static hashStruct hashFunc; // using built-in hash function
    return hashFunc(value) % capacity;
}
template<typename T, PROBING ProbingMethod, typename hashStruct>
size_t Set<T, ProbingMethod, hashStruct>::secondaryHash(const size_t &value) {
    static std::hash<size_t> doubleHashFunc; // using built-in hash function
    return 37 + (doubleHashFunc(value) * 7); // prime numbers are chosen on purpose.
}

/**
 * Inserts value in the hash table, based on the probing method chosen.
 * @param value
 * @return true if insert was successful, false if element already exist in the hashTable
 */
template<typename T, PROBING ProbingMethod, typename hashStruct>
bool Set<T, ProbingMethod, hashStruct>::insert(const T &value) {
    if constexpr (ProbingMethod & PROBING::CHAINING){
        if(!hashTable){ // initialize hashTable if it's cleared before
            SkipList<T>::setDefaultObjectMaxLevel(3);
            hashTable = new SkipList<T>[SEPARATE_CHAINING_DEFAULT_CAPACITY];
            loadingFactorThreshold = SEPARATE_CHAINING_DEFAULT_MAX_LOADING_FACTOR_THRESHOLD;
            capacity = SEPARATE_CHAINING_DEFAULT_CAPACITY;
        };
        bool r;
        size_t index = findSpot(value); // find the index to insert the item
        if(hashTable[index].getSize() > SEPARATE_CHAINING_DEFAULT_MAX_CHAIN_SIZE || (((double)(size + 1)) / capacity > loadingFactorThreshold)){
            // check if rehashing is needed after insertion to maintain loadingFactor or max chain size
            rehash(true, capacity * 2);
            // rehash before inserting the element
            r = hashTable[findSpot(value)].insert(value);
        } else {
            r = hashTable[index].insert(value);
        }
        size++;
        return r;
    } else {
        size_t index = findSpot(value);// find the index to insert the item
        if(hashTable[index]) return false;// if the element already exists (place is full) return
        if(((double)(size + 1)) / capacity > loadingFactorThreshold){
            // check if insertion will need rehashing to maintain loadingFactor below the threshold
            rehash(true, capacity * 2);
            hashTable[findSpot(value)] = new T(value); // find a new spot after rehashing.
        } else {
            // or just insert the value
            hashTable[index] = new T(value);
        }
        size++;
        return true;
    }
}

/**
 * @param value to search for in the Set
 * @return true if value exits in the Set, false otherwise.
 */
template<typename T, PROBING ProbingMethod, typename hashStruct>
bool Set<T, ProbingMethod, hashStruct>::contains(const T &value) {
    if constexpr (ProbingMethod & PROBING::CHAINING){
        if(!hashTable) return false;
        size_t index = findSpot(value);
        return hashTable[index].find(value) != hashTable[index].end();
    } else {
        return hashTable[findSpot(value)] != nullptr;
    }
}

// The following 2 methods are the whole logic behind Hash Tables:
// - How to find an item
// - How to probe in case of a collision.
/**
 * Find the next place for the element, if it's index is occupied.
 * Basically, this method dose the job of probing and finding the next empty spot for the element.
 * @param i this is the counter, number of time this method is called upon a value.
 * @param hashIndex the hashIndex that was calculated on the first step. (initial hashIndex that cause the collision)
 * @return the next index, in which value can be inserted, based on ProbingMethod (LINEAR, QUADRATIC, DOUBLE_HASHING)
 */
template<typename T, PROBING ProbingMethod, typename hashStruct>
size_t Set<T, ProbingMethod, hashStruct>::getNextIndex(int i, const size_t &hashIndex) {
    size_t MaxProbeCountBeforeRehash = 2 * capacity;
    if(i > MaxProbeCountBeforeRehash){
        rehash(true, capacity * 1.5);
    }
    if constexpr (ProbingMethod & PROBING::LINEAR){
        return (hashIndex + i) % capacity;
    } else if constexpr (ProbingMethod & PROBING::QUADRATIC){
        return (hashIndex + i * i) % capacity;
    } else {
        return (hashIndex + i * secondaryHash(hashIndex)) % capacity;
    }
}

/**
 * Find index for the value.
 * in Chaining, it is simple.
 * in other Probing methods, if we don't find the value on the first try,
 * we need to go to the next possible indexes of a value (based on probing method)
 * util we find the value or an empty spot.
 * @param value
 * @return the index in which the element should be (that index either has the element or is empty)
 */
template<typename T, PROBING ProbingMethod, typename hashStruct>
size_t Set<T, ProbingMethod, hashStruct>::findSpot(const T &value) {
    if constexpr (ProbingMethod & PROBING::CHAINING){
        return primaryHash(value);
    } else {
        size_t hashIndex, index, i{1};
        index = hashIndex = primaryHash(value);
        while(hashTable[index] && (*hashTable[index]) != value){
            index = getNextIndex(i, hashIndex);
            i++;
        }
        return index;
    }
}

// GETTERS
template<typename T, PROBING ProbingMethod, typename hashStruct>
inline constexpr double Set<T, ProbingMethod, hashStruct>::getLoadingFactorThreshold() {
    return ((double) size / capacity);
}
template<typename T, PROBING ProbingMethod, typename hashStruct>
inline constexpr size_t Set<T, ProbingMethod, hashStruct>::getSize() {
    return size;
}
template<typename T, PROBING ProbingMethod, typename hashStruct>
inline constexpr size_t Set<T, ProbingMethod, hashStruct>::getCapacity() {
    return capacity;
}
template<typename T, PROBING ProbingMethod, typename hashStruct>
void Set<T, ProbingMethod, hashStruct>::setLoadingFactorThreshold(double val) {
    if constexpr (ProbingMethod & PROBING::CHAINING){
        if(val > 0)
            loadingFactorThreshold = val;
    } else {
        if(val > 0.0 && val < 1.0)
            loadingFactorThreshold = val;
    }
}

/**
 * Removes an element from the Set
 * @param value to be removed
 * @return true if operation was successful, false otherwise (element was not there)
 */
template<typename T, PROBING ProbingMethod, typename hashStruct>
bool Set<T, ProbingMethod, hashStruct>::remove(const T &value) {
    if constexpr (ProbingMethod & PROBING::CHAINING){
        if(!hashTable) return false; // removing from empty hashTable
        size_t index = findSpot(value); // find the chain where the value shoud be in
        if(hashTable[index].remove(value)){ // remove it
            // success
            size--;
            return true;
        } else {
            // element wasn't there
            return false;
        }
    } else {
        size_t index = findSpot(value); // it either returns an empty spot, or a spot with the element inside.
        if(!hashTable[index]){ // if it's an empty spot, the element is not in the hashTable
            return false;
        }
        delete hashTable[index];
        hashTable[index] = nullptr;
        // rehashing is necessary; since because of that index being filled with that element,
        // some elements might have probed to other empty spaces,
        // if we just remove it without rehashing, those other elements will be unreachable.
        rehash();
        size--;
        return true;
    }
}

/**
 * updates the hashTable to a new capacity
 * @param increaseCap Whether we want to increase the cap, or just re-insert the existing elements
 * @param toCap to What capacity are we going to increase it
 */
template<typename T, PROBING ProbingMethod, typename hashStruct>
void Set<T, ProbingMethod, hashStruct>::rehash(bool increaseCap, size_t toCap) {
    if constexpr (ProbingMethod & PROBING::CHAINING){
        // if(!increaseCap) return; this will be a dummy idea to rehash a hashTable in chaining method without increasing the cap.
        SkipList<T> *tempHashTable = hashTable;
        size_t oldCap = capacity;
        // increase the cap
        if(increaseCap) capacity = toCap ? toCap : capacity * 2;
        hashTable = new SkipList<T>[capacity];

        // insert elements into the chains again.
        for(size_t i = 0; i < oldCap; i++){
            auto it = tempHashTable[i].begin();
            auto it_end = tempHashTable[i].end();
            for(; it != it_end; ++it){
                hashTable[findSpot(*it)].insert(*it);
            }
        }
        delete [] tempHashTable;
    } else {
        T **tempHashTable = hashTable;
        size_t oldCap = capacity;
        // increase the cap
        if(increaseCap) capacity = toCap ? toCap : capacity * 2;
        hashTable = new T*[capacity];

        for (size_t i = 0; i < capacity;i++){
            hashTable[i] = nullptr;
        }
        // insert elements at their spot (we need to find the spot again)
        for(size_t i = 0; i < oldCap; i++){
            if(tempHashTable[i]){
                hashTable[findSpot(*tempHashTable[i])] = tempHashTable[i];
            }
        }
        delete [] tempHashTable;
    }
}


/**
 * displays the HashTable
 */
template<typename T, PROBING ProbingMethod, typename hashStruct>
void Set<T, ProbingMethod, hashStruct>::display() {
    std::cout << "HASH TABLE : ";
    if constexpr (ProbingMethod & PROBING::LINEAR){
        std::cout << "LINEAR PROBING"<< std::endl;
    } else if constexpr (ProbingMethod & PROBING::QUADRATIC){
        std::cout << "QUADRATIC PROBING"<< std::endl;
    } else if constexpr (ProbingMethod & PROBING::DOUBLE_HASHING){
        std::cout << "DOUBLE HASHING"<< std::endl;
    }else {
        std::cout << "CHAINING"<< std::endl;
    }
    if constexpr (ProbingMethod & PROBING::CHAINING){
        if(!hashTable){
            std::cout << "-EMPTY" << std::endl;
            return;
        }
        for(size_t i = 0; i < capacity; i++){
            std::cout << std::setw(3) << i << " [";
            if(hashTable[i].getSize() > 0){
                auto it = hashTable[i].begin();
                auto it_end = hashTable[i].end();
                std::cout << "* -> ";
                for(; it != it_end; ++it){
                    std::cout << *it << " -> ";
                }
                std::cout << "*]";
            }else {
                std::cout << "EMPTY]";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    } else {
        for(size_t i = 0; i < capacity; i++){
            std::cout << std::setw(3) << i << " [";
            if(hashTable[i]){
                std::cout << *hashTable[i];
            }else {
                std::cout << "-";
            }
            std::cout << "]\n";
        }
        std::cout << std::endl;
    }

}