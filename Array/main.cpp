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

void testConstructors(void);
void testDisplayArray(void);
static void testAppendAndGet(void);

int main(int argc, const char * argv[]) {
    
#if ENABLE_TIME_TEST
    timeTest();
#endif // ENABLE_TIME_TEST
    
#if ENABLE_FIB_TEST
    uint32_t * arr = new uint32_t[RECURSION_LIMIT];
    fillArrayWithFibNumbers(arr, RECURSION_LIMIT);
#endif // ENABLE_FIB_TEST
    
    testConstructors();
    testDisplayArray();
    testAppendAndGet();
    
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
