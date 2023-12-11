//
//  exceptions.hpp
//  Array
//
//  Created by Joseph Rodgers on 12/10/23.
//

#ifndef exceptions_hpp
#define exceptions_hpp

#include <stdio.h>
#include <string>

class ArrayException : public std::exception {
private:
    char * message;
public:
    ArrayException(char * msg);
    // Override the what() method to return a custom error message
    char * what();
};

#endif /* exceptions_hpp */
