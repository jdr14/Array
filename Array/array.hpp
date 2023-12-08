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

// NOTE: I realize C does not support the use of classes to encapsulate data and their related functions; however since this is a DSA review
// I have defined IS_CPP macro to test out allocating memory on heap via new for cpp and via malloc for C.  Additionally, I realize malloc does
// work for C++ as well since C is a subset of C++; however, this is purely for my own practice.

#define IS_CPP (1)
#define DEFAULT_ARRAY_SIZE (10)

class Array
{
private:
    uint32_t *A;  // Dynamically Allocated array
    uint32_t size;  // Total size of memory allocated
    uint32_t length;  // Number of elements stored in the array
    uint32_t * allocateMemory(uint32_t size);
    void freeMemory(uint32_t *p);
    bool swap(uint32_t index1, uint32_t index2);
public:
    Array(void); // This can dynamically allocate memory for a fixed size
    Array(uint32_t size); // Determine size
    Array(uint32_t * arr, uint32_t size, uint32_t length);
    void displayArray(void);
    bool append(uint32_t value);
    bool insert(uint32_t i, uint32_t value);
    bool linearSearch(uint32_t value, uint32_t &index);
    bool modifiedLinearSearch(uint32_t value, uint32_t &index, bool moveToBegin);
    bool linearSearchByIndex(uint32_t index, uint32_t &value);
    bool deleteByValue(uint32_t value);
    bool deleteByIndex(uint32_t index);
    ~Array(void); // Destructor to delete dynamically allocated memory (i.e. memory allocated on the heap)
};

uint32_t * Array::allocateMemory(uint32_t size) {
#if IS_CPP
    return new uint32_t[size]; // Dynamically allocate buffer on heap (C++)
#else // IS_CPP
    return (uint32_t *)malloc(size * sizeof(uint32_t)); // Dynamically allocate buffer on heap (C)
#endif // IS_CPP
}

void Array::freeMemory(uint32_t *p) {
#if IS_CPP
    delete []p; // Dynamically allocate buffer on heap (C++)
#else // IS_CPP
    free(p); // Dynamically allocate buffer on heap (C)
#endif // IS_CPP
}

//static void _print(char * msg, bool endline) {
//#if IS_CPP
//    std::cout << msg;
//    if (endline)
//        std::cout << std::endl;
//#else // IS_CPP
//    printf("\n%s", msg);
//    if (endline)
//        printf("\n");
//#endif // IS_CPP
//}

bool Array::swap(uint32_t index1, uint32_t index2) {
    if (index1 < this->length && index2 < this->length) {
        uint32_t temp = this->A[index1]; // saved 1st index
        this->A[index1] = this->A[index2];
        this->A[index2] = temp;
        return true;
    }
    return false;
}

void _error(std::string err_str) {
    std::cout << "Error: " << err_str << std::endl;
}

Array::Array(void) {
    this->size = DEFAULT_ARRAY_SIZE;  // Use default array size since user does not provide size using this constructor
    this->length = 0;  // No elements in array yet
    this->A = allocateMemory(this->size);
}

Array::Array(uint32_t size) {
    this->size = size;  //
    this->length = 0;  // No elements in array yet
    this->A = allocateMemory(this->size);
}

Array::Array(uint32_t * arr, uint32_t size, uint32_t numElements) {
    this->size = size;
    this->length = numElements;  // No elements in array yet
    this->A = allocateMemory(this->size);  // Allocate on heap (C++)
    
    // Deep copy of the array
    for (int i = 0; i < numElements; i++) {
        this->A[i] = arr[i];
    }
}

Array::~Array(void) {
    freeMemory(this->A);
}

void Array::displayArray(void) {
//    char index[20];
//    char buf[50];
//    snprintf(buf, 50, "Array of size %d and %d elements:", this->size, this->length);
//    _print(buf, true);
//    for (uint32_t i = 0; i < this->length; i++) {
//        snprintf(index, sizeof(index), "%d, ", this->A[i]);
//        _print(index, false);
//    }
    printf("\nFibonacci Sequence:");
    std::cout << std::endl << "{";
    for (uint32_t i = 0; i < this->length; i++) {
        std::cout << *(this->A + i);
        if (i == this->length-1)
            std::cout << "}\n" << std::endl;
        else
            std::cout << ", ";
    }
}

/*
 uint32_t *A;  // Dynamically Allocated array
 uint32_t size;  // Total size of memory allocated
 uint32_t length;  // Number of elements stored in the array
 */
bool Array::append(uint32_t value) {
    if (this->length == this->size) { // Array is full
        _error((std::string)"Array is full!");
        return false;
    }
    this->A[this->length] = value;
    this->length++;
    return true; // Append was successful
}

bool Array::insert(uint32_t i, uint32_t value) {
    if (i > this->length) {  // Check that we are given a valid index
        _error((std::string)"Index is invalid");
        return false;
    }
    if (i == this->length) {  // Check if we are just appending (i.e. inserting at the end)
        this->A[i] = value;
        this->length++;
        return true;
    }
    if (this->length == this->size) {  // Check if array is full
        _error((std::string)"Array is full!");
        return false;
    }
    
    // Shift all elements above the index to make space
    for (uint32_t index = this->length; index > i; index--) {
        this->A[index] = this->A[index - 1];
    }
    this->A[i] = value; // Update value at index (i.e. perform the insertion)
    this->length++; // Don't forget to update the length
    return true;
}

bool Array::linearSearch(uint32_t value, uint32_t &index) {
    for (int i = 0; i < this->length; ++i) {
        if (this->A[i] == value) {
            index = i;
            return true; // Index found
        }
    }
    return false;
}

bool Array::modifiedLinearSearch(uint32_t value, uint32_t &index, bool moveToBegin) {
    for (int i = 0; i < this->length; ++i) {
        if (this->A[i] == value) {
            index = i;
            if (i > 0) {
                if (moveToBegin) {
                    this->swap(i, 0);
                }
                else {
                    this->swap(i, i-1); // With each search
                }
            }
            return true; // Index found
        }
    }
    _error((std::string)"Failed to find the value");
    return false; // We failed the search if nothing is returned
}

bool Array::linearSearchByIndex(uint32_t index, uint32_t &value) {
    if (index >= this->length) {
        // throw exception
        return false;
    }
    return true;
}

bool deleteByValue(uint32_t value);
bool deleteByIndex(uint32_t index);

#endif /* array_hpp */
