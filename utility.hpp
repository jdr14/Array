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
#include <stdarg.h> // useful for passing arbitrary # of args in C


#define RECURSION_LIMIT (45)

// Fibonnaci sequence functions
uint32_t recursiveFib(uint32_t *mem, uint32_t i);
uint32_t recursiveFibMemorization(uint32_t * mem, uint32_t i);
uint32_t iterativeFib(uint32_t i);

// Factorial calculation functions
uint32_t recursiveFactorial(uint32_t i);
uint32_t iterativeFactorial(uint32_t i);

double timeFunction(uint32_t (*func)(uint32_t *, uint32_t), uint32_t param, uint32_t m[]);
void initializeMemorizationArray(uint32_t mem[], uint32_t size);
void fillArrayWithFibNumbers(uint32_t *arr, uint32_t size);
void timeTest(void);


#endif /* utility_hpp */
