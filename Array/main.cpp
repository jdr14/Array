//
//  main.cpp
//  Array
//
//  Created by Joseph Rodgers on 12/5/23.
//

#include <iostream>
#include <cassert>
#include "array.hpp"
#include "utility.hpp"
#include <assert.h>

#define ENABLE_TIME_TEST (0)
#define ENABLE_FIB_TEST  (0)
#define ENABLE_SORT_DEBUG (0)

// Test functions for Array functionality
void testConstructors(void);
void testDisplayArray(void);
static void testAppendAndGet(void);

// Test functions for Array sorting techniques
void fillArrayWithRandomNumbers(Array *arr, uint32_t size, uint32_t low, uint32_t high);
void testGenericSortMethod(void (Array::*pFunc)(void));
void testBubbleSort(void);
void testInsertionSort(void);
void testSelectionSort(void);

int main(int argc, const char * argv[]) {
    
#if ENABLE_TIME_TEST
    timeFib();
#endif // ENABLE_TIME_TEST
    
#if ENABLE_FIB_TEST
    uint32_t * arr = new uint32_t[RECURSION_LIMIT];
    fillArrayWithFibNumbers(arr, RECURSION_LIMIT);
#endif // ENABLE_FIB_TEST
    
    testConstructors();
    testDisplayArray();
    testAppendAndGet();
    
    testBubbleSort();
    testInsertionSort();
    testSelectionSort();
    
    return 0;
}


void testConstructors(void) {
    std::cout << "\nTesting constructors:" << std::endl;
    Array a;
    assert(a.getSize() == DEFAULT_ARRAY_SIZE);
    assert(a.getLength() == 0); // no items in the array
    std::cout << "\tPassed: Default Constructor Array(void):" << std::endl;
    
    Array b(20);
    assert(b.getSize() == 20);
    assert(b.getLength() == 0);
    std::cout << "\tPassed: Array(size):" << std::endl;
    
    uint32_t size = 8, length = 4;
    uint32_t * buf = new uint32_t[size];
    for (uint32_t i = 0; i < length; ++i) {
        buf[i] = i;
    }
    Array c(buf, size, length);
    assert(c.getSize() == size);
    assert(c.getLength() == length);
    for (uint32_t i = 0; i < length; ++i) {
        assert(c.get(i) == i);
    }
    std::cout << "\tPassed: Array(buf, size, length):" << std::endl;
    delete []buf;
    buf = nullptr;
}

void testDisplayArray(void) {
    std::cout << "\nTesting displayArray():" << std::endl;
    Array a(10);
    for (int i = 0; i < 10; ++i) {
        a.append(i);
    }
    a.displayArray();
    std::cout << "\tPassed: Array Display:" << std::endl;
}

static void testAppendAndGet(void) {
    std::cout << "\nTesting append(value) and get(index):" << std::endl;
    uint32_t size = 10, length = 4;
    Array a(size);
    uint32_t i = 0;
    for (; i < length; ++i) {
        a.append(i);
    }
    assert(a.getSize() == size);
    assert(a.getLength() == length);
    length = 10;
    try {
        for (; i <= length; ++i) {
            a.append(i);
        }
        assert(0 == 1); // Should not get here if we are throwing the exception
    }
    catch (ArrayException err) {
        std::cout << "\t\tException caught - " << err.what() << std::endl;
    }
    std::cout << "\tPassed: append(value)" << std::endl;
    
    // Array should look like {0, 1, 2, 3, 4, 5, ...}
    for (uint32_t i = 0; i < size; ++i) {
        assert(i == a.get(i));
    }
    try {
        a.get(-1);
    }
    catch (ArrayException err) {
        std::cout << "\t\tException caught - " << err.what() << std::endl;
    }
    try {
        a.get(12);
    }
    catch (ArrayException err) {
        std::cout << "\t\tException caught - " << err.what() << std::endl;
    }
    std::cout << "\tPassed: get(index)" << std::endl;
}

/*
 This function will be responsible for helping to fill an array of a given size "size"
 with random numbers between the ranges of the given "low" and "high" numbers
 */
void fillArrayWithRandomNumbers(Array *arr, uint32_t low, uint32_t high) {
    for (uint32_t i = 0; i < arr->getSize(); ++i) {
        // Append random numbers in the range of (low - high)
        arr->append( boundedRandomNumberGenerator(i, low, high) );
    }
}

void testGenericSortMethod(void (Array::*pFunc)(void)) {
    uint32_t size;
#if ENABLE_SORT_DEBUG
    size = 5;
#else // ENABLE_SORT_DEBUG
    size = 50000;
#endif // ENABLE_SORT_DEBUG
    
    Array a(size);
    fillArrayWithRandomNumbers(&a, 0, 1000);
#if ENABLE_SORT_DEBUG
    a.displayArray();
#endif // ENABLE_SORT_DEBUG
    // Pass the pointer and address of Array object 'a' to calculate the time it takes to sort
    double timeTaken = timeVoidFunction(&a, pFunc);
    
    // Will return false and assert if the array is not sorted in ascending order
#if ENABLE_SORT_DEBUG
    a.displayArray();
#else // ENABLE_SORT_DEBUG
    assert(a.isSorted());
#endif // ENABLE_SORT_DEBUG
    
    std::cout << "\t\tArray is sorted!  Took " << timeTaken << " to sort an array of size " << size << std::endl;
}

void testBubbleSort(void) {
    std::cout << "\nTesting bubbleSort():" << std::endl;
    
    // Get a pointer to the address of a member function of class Array
    // in this case, the bubbleSort method
    testGenericSortMethod(&Array::bubbleSort);
    std::cout << "\tPassed: bubbleSort()" << std::endl;
}

void testInsertionSort(void) {
    std::cout << "\nTesting insertionSort():" << std::endl;
    testGenericSortMethod(&Array::insertionSort);
    std::cout << "\tPassed: insertionSort()" << std::endl;
}

void testSelectionSort(void) {
    std::cout << "\nTesting selectionSort():" << std::endl;
    testGenericSortMethod(&Array::selectionSort);
    std::cout << "\tPassed: selectionSort()" << std::endl;
}
