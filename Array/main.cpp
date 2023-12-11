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


#define ENABLE_TIME_TEST (1)
#define ENABLE_FIB_TEST  (1)


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

