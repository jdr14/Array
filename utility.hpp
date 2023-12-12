//
//  utility.hpp
//  Array
//
//  Created by Joseph Rodgers on 12/10/23.
//

#ifndef utility_hpp
#define utility_hpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h> // includes dynamic memory allocation functions in C (i.e. malloc/free)
#include <stdint.h>
#include <time.h> // useful for timing functions in C
#include "array.hpp"

#define RECURSION_LIMIT (45)

//#define CALL_MEMBER_FN(object, ptrToMember) ((object).*(ptrToMember)())

// Will use this to time the sorting algorithms
double timeVoidFunction(Array *arr, void (Array::*func)(void));

// Use this to generate random number
uint32_t boundedRandomNumberGenerator(uint32_t seed, uint32_t low, uint32_t high);

// Fibonnaci sequence functions
uint32_t recursiveFib(uint32_t *mem, uint32_t i);
uint32_t recursiveFibMemorization(uint32_t * mem, uint32_t i);
uint32_t iterativeFib(uint32_t i);
double timeFib(uint32_t (*func)(uint32_t *, uint32_t), uint32_t param, uint32_t m[]);
void initializeMemorizationArray(uint32_t mem[], uint32_t size);
void fillArrayWithFibNumbers(uint32_t *arr, uint32_t size);
void timeTest(void);

// Factorial calculation functions
uint32_t recursiveFactorial(uint32_t i);
uint32_t iterativeFactorial(uint32_t i);

#endif /* utility_hpp */
