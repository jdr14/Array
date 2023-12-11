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

double timeFunction(uint32_t (*func)(uint32_t *, uint32_t), uint32_t param, uint32_t m[]) {
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
        delta1 = timeFunction(func1, i, nullptr);
        delta2 = timeFunction(func2, i, memBuf);
        printf("(%d)  %f  |  %f\n", i, delta1, delta2);
    }
    
    free(memBuf); // Return memory
}
