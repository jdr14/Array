//
//  main.cpp
//  Array
//
//  Created by Joseph Rodgers on 12/5/23.
//

#include <iostream>
#include <stdlib.h> // includes dynamic memory allocation functions in C (i.e. malloc/free)
#include <stdint.h>
#include <time.h> // useful for timing functions in C
#include <stdarg.h> // useful for passing arbitrary # of args in C
#include "array.hpp"

#define ENABLE_TIME_TEST (0)
#define RECURSION_LIMIT (45)
#define ENABLE_FIB_TEST (0)

// 1st parameter is dummy
uint32_t recursiveFib(uint32_t *mem, uint32_t i) {
    if (i <= 1) {
        
        return i;
    }
    return recursiveFib(nullptr, i-2) + recursiveFib(nullptr, i-1);
}
uint32_t recursiveFibMemorization(uint32_t * mem, uint32_t i) {
    if (i <= 1) {
        mem[i] = i;
    }
    if (mem[i] == -1) {
        mem[i] = recursiveFibMemorization(mem, i-1) + recursiveFibMemorization(mem, i-2);
    }
    return mem[i];
}
//int iterativeFib(int i) {
//    if (i <= 1) {
//        return i;
//    }
//    int s = 0;
//    int t0 =
//    for (int j = 2; j <= i; j++) {
//        s += (2 * j) - 3;
//    }
//    return s;
//}

static double timeFunction(uint32_t (*func)(uint32_t *, uint32_t), uint32_t param, uint32_t m[]) {
    static clock_t time;
    
    if (m == nullptr) {
        time = clock();
        (*func)(m, param);  // Execute the function
    }
    else {
        time = clock();
        (*func)(m, param);
    }
    
    // Calculate time delta = current clock - start and convert to double based on clock cycles per sec of specific hardware
    return ((double)(clock() - time)) / CLOCKS_PER_SEC;
}

static void initializeMemorizationArray(uint32_t mem[], uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        mem[i] = -1;
    }
}

void fillArrayWithFibNumbers(uint32_t *arr, uint32_t size) {
    // Use memoization technique to speed up recursive fib
    uint32_t * memBuf = new uint32_t[size];
    
    // This is created to remember what results were of each recursive call
    initializeMemorizationArray(memBuf, size);
    
    for(int i = 0; i < size; i++) {
        arr[i] = recursiveFibMemorization(memBuf, i);
    }
    
    delete []memBuf; // Return memory
}

static void timeTest(void) {
    uint32_t *memBuf = (uint32_t *)malloc(RECURSION_LIMIT * sizeof(uint32_t));
                                          
    // This is created to remember what results were of each recursive call
    initializeMemorizationArray(memBuf, RECURSION_LIMIT);
    
    // Create function pointers to the different fibonacci seq. functions to calculate the time delta's below
    uint32_t (*func1)(uint32_t *, uint32_t) = &recursiveFib;
    uint32_t (*func2)(uint32_t *, uint32_t) = &recursiveFibMemorization;
    double delta1, delta2;
    printf("\nElapsed time in seconds for both methods of fibonnaci recursion\n");
    for (uint32_t i = 0; i < RECURSION_LIMIT; i++) {
        delta1 = timeFunction(func1, i, nullptr);
        delta2 = timeFunction(func2, i, memBuf);
        printf("(%d)  %f  |  %f\n", i, delta1, delta2);
    }
    
    free(memBuf); // Return memory
}

int main(int argc, const char * argv[]) {
    
#if ENABLE_TIME_TEST
    timeTest();
#endif // ENABLE_TIME_TEST
    
#if ENABLE_FIB_TEST
    uint32_t * arr = new uint32_t[RECURSION_LIMIT];
    fillArrayWithFibNumbers(arr, RECURSION_LIMIT);
#endif // ENABLE_FIB_TEST

    Array a;
    for (int i = 0; i < 4; ++i) {
        a.append(i);
    }
    for (int i = 0; i < 4; ++i) {
        a.insert(2, (i+1) * 4);
    }
    a.insert(10, 20);
    a.insert(8, 20);
    a.insert(0, 30);
    a.displayArray();
    
    uint32_t value = 0;
    
    return 0;
}

