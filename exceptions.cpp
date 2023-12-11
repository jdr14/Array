//
//  exceptions.cpp
//  Array
//
//  Created by Joseph Rodgers on 12/10/23.
//

#include "exceptions.hpp"

ArrayException::ArrayException(char *msg) : message(msg) {}

char * ArrayException::what() {
    return message;
}
