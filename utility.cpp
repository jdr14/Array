//
//  utility.cpp
//  Array
//
//  Created by Joseph Rodgers on 12/10/23.
//

#include "utility.hpp"

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
// Given a specific index, calculate the fibonnaci value for that index of the fib. seq.
uint32_t iterativeFib(uint32_t i) {
    if (i <= 1) {
        return i;
    }
    uint32_t sum = 0;
    uint32_t t0 = 0;
    uint32_t t1 = 1;
    for (uint32_t j = 2; j <= i; j++) {
        sum = (t0 + t1);
        t0 = t1;
        t1 = sum;
    }
    return sum;
}

uint32_t recursiveFactorial(uint32_t i) {
    return (i == 0) ? 1: i * recursiveFactorial(i - 1);
}

uint32_t iterativeFactorial(uint32_t i) {
    uint32_t fact = 1;
    while (i > 0) {
        fact *= i;
        i--;
    }
    return fact;
}

uint32_t boundedRandomNumberGenerator(uint32_t seed, uint32_t low, uint32_t high) {
    // Provide a seed value
    srand( (unsigned)clock() * seed );

    // Calculate and return a random number between low and high value
    uint32_t delta = high - low;
    return low + (rand() % delta);
}

double timeVoidFunction(Array *arr, void (Array::*func)(void)) {
    if (func == nullptr)
        return -1;
    
    clock_t time = clock();
    (arr->*func)();
//    (Array::*func)();
    return ((double)clock() - time) / CLOCKS_PER_SEC;
};

double timeFib(uint32_t (*func)(uint32_t *, uint32_t), uint32_t param, uint32_t m[]) {
    clock_t time;
    
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

void initializeMemorizationArray(uint32_t mem[], uint32_t size) {
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

void timeTest(void) {
    uint32_t *memBuf = (uint32_t *)malloc(RECURSION_LIMIT * sizeof(uint32_t));
                                          
    // This is created to remember what results were of each recursive call
    initializeMemorizationArray(memBuf, RECURSION_LIMIT);
    
    // Create function pointers to the different fibonacci seq. functions to calculate the time delta's below
    uint32_t (*func1)(uint32_t *, uint32_t) = &recursiveFib;
    uint32_t (*func2)(uint32_t *, uint32_t) = &recursiveFibMemorization;
    double delta1, delta2;
    printf("\nElapsed time in seconds for both methods of fibonnaci recursion\n");
    for (uint32_t i = 0; i < RECURSION_LIMIT; i++) {
        delta1 = timeFib(func1, i, nullptr);
        delta2 = timeFib(func2, i, memBuf);
        printf("(%d)  %f  |  %f\n", i, delta1, delta2);
    }
    
    free(memBuf); // Return memory
}
