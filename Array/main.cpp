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

static void initializeMemorizationArray(uint32_t mem[], uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        mem[i] = -1;
    }
}

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

int main(int argc, const char * argv[]) {
    // Scan user input for size of array we will fill with fib seq.
    uint32_t size = 0;
    uint32_t * memBuf;
#if IS_CPP
//    std::string s = ;
    std::cout << "Enter the size of the array: " << std::endl;
    std::cin >> size;
    memBuf = new uint32_t[size];
#else // IS_CPP (C)
    printf("\nEnter the size of the array: ");
    scanf("%d", &size);
    memBuf = (uint32_t *)malloc(size * sizeof(uint32_t));
#endif // IS_CPP
    
    // This is created to remember what results were of each recursive call
    initializeMemorizationArray(memBuf, 100);

#if ENABLE_TIME_TEST
    // Create function pointers to the different fibonacci seq. functions to calculate the time delta's below
    uint32_t (*func1)(uint32_t *, uint32_t) = &recursiveFib;
    uint32_t (*func2)(uint32_t *, uint32_t) = &recursiveFibMemorization;
    double delta1, delta2;
    printf("\nElapsed time in seconds for both methods of fibonnaci recursion\n");
    for (uint32_t i = 0; i < size && i <= RECURSION_LIMIT; i++) {
        delta1 = timeFunction(func1, i, nullptr);
        delta2 = timeFunction(func2, i, memBuf);
        printf("(%d)  %f  |  %f\n", i, delta1, delta2);
    }
#endif // ENABLE_TIME_TEST
    uint32_t * arr = new uint32_t[size];
    for(int i = 0; i < size; i++) {
        arr[i] = recursiveFibMemorization(memBuf, i);
    }
//    Array a(arr, size, size);
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
    return 0;
}

