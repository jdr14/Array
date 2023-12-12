//
//  array.hpp
//  Array
//
//  Created by Joseph Rodgers on 12/5/23.
//

#ifndef array_hpp
#define array_hpp

#include <stdlib.h> // Contains C functions to dynamically allocate/deallocate memory (e.g. free/malloc)
#include <stdio.h> // C IO
#include <string.h> // C strings
#include <stdint.h> // C ints
#include <array>
#include <iostream> // C++ IO
#include <time.h> // useful for timing functions in C
#include "exceptions.hpp"

// NOTE: I realize C does not support the use of classes to encapsulate data and their related functions; however since this is a DSA review
// I have defined IS_CPP macro to test out allocating memory on heap via new for cpp and via malloc for C.  Additionally, I realize malloc does
// work for C++ as well since C is a subset of C++; however, this is purely for my own practice.

#define IS_CPP (1)
#define DEFAULT_ARRAY_SIZE (10)

enum searchmethod_e {
    linearSearch = 0,
    frequencySearch = 1,
    swapToBeginSearch = 2,
};

enum shiftDirection_e {
    right,
    left,
};

class Array
{
private:
    uint32_t *A;  // Dynamically Allocated array
    uint32_t size;  // Total size of memory allocated
    uint32_t length;  // Number of elements stored in the array
    uint32_t * allocateMemory(uint32_t size);
    void freeMemory(uint32_t *p);
    bool swap(uint32_t index1, uint32_t index2);
    uint32_t shift(shiftDirection_e direction, uint32_t start, uint32_t end);
    uint32_t quickSortPartition(uint32_t low, uint32_t high);
public:
    Array(void); // This can dynamically allocate memory for a fixed size
    Array(uint32_t size); // Determine size
    Array(uint32_t * arr, uint32_t size, uint32_t length);
    ~Array(void); // Destructor to delete dynamically allocated memory (i.e. memory allocated on the heap)
    
    uint32_t getSize(void);
    uint32_t getLength(void);
    
    void displayArray(void);
    
    uint32_t get(uint32_t index);
    void set(uint32_t index, uint32_t value);
    uint32_t max(void);
    uint32_t sum(void);
    
    void reverse(void); // Reverse the array elements using the same block of memory allocated for the array
    uint32_t leftShift(uint32_t start, uint32_t end);
    void leftRotate(uint32_t start, uint32_t end);
    uint32_t rightShift(uint32_t start, uint32_t end);
    void rightRotate(uint32_t start, uint32_t end);
    
    // Sorting techniques
    bool isSorted(void);
    void bubbleSort(void);
    void insertionSort(void);
    void selectionSort(void);
    void quickSortVoidHandle(void);
    void quickSort(uint32_t low, uint32_t high);
    
    void append(uint32_t value);  // also add
    void insert(uint32_t i, uint32_t value);
    void del(uint32_t index);
    
    uint32_t search(uint32_t value, searchmethod_e searchMethod);
    uint32_t iterativeBinarySearch(uint32_t key);
    uint32_t binarySearchRecursive(uint32_t low, uint32_t high, uint32_t key);
};


#endif /* array_hpp */
