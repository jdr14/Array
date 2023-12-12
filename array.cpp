//
//  array.cpp
//  Array
//
//  Created by Joseph Rodgers on 12/11/23.
//

#include "array.hpp"

/*
 Method to check if the internal array is sorted or not
 */
bool Array::isSorted(void) {
    if (this->length <= 1) {
        return true;
    }
    for (uint32_t i = 0; i < this->getLength() - 1; ++i) {
        // The next index should never have a value lesser than the current one in a sorted array
        if(this->A[i+1] < this->A[i]) {
            return false;
        }
    }
    return true;
}

void Array::bubbleSort(void) {
    if (this->length <= 1) {
        return;  // we need this check because it is uint32_t
    }
    for (uint32_t i = this->length - 1; i > 0; --i) {
        for (uint32_t j = 0; j < i; ++j) {
            if (this->A[j] <= this->A[j+1]) {
                continue;
            }
            this->swap(j, j+1);
        }
    }
}

void Array::insertionSort(void) {
    if (this->length <= 1) {
        return;  // array of size 1 is already sorted
    }
    uint32_t i, j, remember;
    for (i = 1; i < this->length; ++i) {
        j = i-1;
        remember = this->A[i];
        while (j >= 0 && j < UINT32_MAX && this->A[j] > remember) {
            // We want to use >= instead of < in this case to prevent excessive and unnecessary swapping
            // We want to check for N times and swap only once.
            this->A[j+1] = this->A[j];
            j--;
        }
        this->A[j+1] = remember; // insert at correct location
    }
}

void Array::selectionSort(void) {
    
}

uint32_t * Array::allocateMemory(uint32_t size) {
#if IS_CPP
    return new uint32_t[size]; // Dynamically allocate buffer on heap (C++)
#else // IS_CPP
    return (uint32_t *)malloc(size * sizeof(uint32_t)); // Dynamically allocate buffer on heap (C)
#endif // IS_CPP
}

void Array::freeMemory(uint32_t *p) {
#if IS_CPP
    delete []p; // Dynamically allocate buffer on heap (C++)
    p = nullptr;
#else // IS_CPP
    free(p); // Dynamically allocate buffer on heap (C)
    p = NULL;
#endif // IS_CPP
}

bool Array::swap(uint32_t index1, uint32_t index2) {
    if (index1 < this->length && index2 < this->length) {
        uint32_t temp = this->A[index1]; // saved 1st index
        this->A[index1] = this->A[index2];
        this->A[index2] = temp;
        return true;
    }
    return false;
}

uint32_t Array::shift(shiftDirection_e direction, uint32_t start, uint32_t end) {
    if (this->length == 0 || end >= this->length) { // Nothing in the array
        return 0;
    }
    uint32_t saveValue = 0;
    switch(direction) {
        case right:
            saveValue = this->A[end];
            for (uint32_t i = start; i < end; i++) {
                this->A[i+1] = this->A[i];
            }
            // Set the empty value to 0 as a default value, We could modify the implementation of this as needed
            this->A[start] = 0;
            break;
        case left:
            saveValue = this->A[start];
            for (uint32_t i = end; i > start; i--) {
                this->A[i] = this->A[i-1];
            }
            // Set the empty value to 0 as a default value, We could modify the implementation of this as needed
            this->A[end] = 0;
            break;
        default:
            break;
    }
    return saveValue;
}

Array::Array(void) {
    this->size = DEFAULT_ARRAY_SIZE;  // Use default array size since user does not provide size using this constructor
    this->length = 0;  // No elements in array yet
    this->A = allocateMemory(this->size);
}

Array::Array(uint32_t size) {
    this->size = size;  //
    this->length = 0;  // No elements in array yet
    this->A = allocateMemory(this->size);
}

Array::Array(uint32_t * arr, uint32_t size, uint32_t numElements) {
    this->size = size;
    this->length = numElements;  // No elements in array yet
    this->A = allocateMemory(this->size);  // Allocate on heap (C++)
    
    // Deep copy of the array
    for (int i = 0; i < numElements; i++) {
        this->A[i] = arr[i];
    }
}

uint32_t Array::getSize(void) {
    return this->size;
}

uint32_t Array::getLength(void) {
    return this->length;
}

void Array::displayArray(void) {
    std::cout << "{";
    for (uint32_t i = 0; i < this->length; i++) {
        std::cout << *(this->A + i);
        if (i == this->length-1)
            std::cout << "}" << std::endl;
        else
            std::cout << ", ";
    }
}

uint32_t Array::get(uint32_t index) {
    if (index >= this->length) {
        throw ArrayException("Index out of range!");
    }
    return this->A[index];
}

void Array::set(uint32_t index, uint32_t value) {
    if (index >= this->length) {
        throw ArrayException("Index out of range!");
    }
    this->A[index] = value;
}

uint32_t Array::max(void) {
    uint32_t max = 0;
    // Assume we are calculating the max of an unsorted array
    for (uint32_t i = 0; i < this->length; ++i) {
        if (this->A[i] > max) {
            max = this->A[i];
        }
    }
    return max;
}

uint32_t Array::sum(void) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < this->length; ++i) {
        sum += this->A[i];
    }
    return sum;
}

void Array::reverse(void) {
    uint32_t temp;
    for (uint32_t i = 0; i < (this->length / 2); ++i) {
        temp = this->A[i];
        this->A[i] = this->A[this->length - 1 - i];
        this->A[this->length - 1 - i] = temp;
    }
}

uint32_t Array::leftShift(uint32_t start, uint32_t end) {
    return this->shift(left, start, end);
}

void Array::leftRotate(uint32_t start, uint32_t end) {
    this->A[end] = this->shift(left, start, end);
}

uint32_t Array::rightShift(uint32_t start, uint32_t end) {
    return this->shift(right, start, end);
}

void Array::rightRotate(uint32_t start, uint32_t end) {
    this->A[start] = this->shift(right, start, end);
}

void Array::append(uint32_t value) {
    if (this->length == this->size) { // Array is full
        throw ArrayException("Array is full!");
    }
    this->A[this->length] = value;
    this->length++;
}

void Array::insert(uint32_t i, uint32_t value) {
    if (i > this->length) {  // Check that we are given a valid index
        throw ArrayException("Index out of range!");
    }
    if (i == this->length) {  // Check if we are just appending (i.e. inserting at the end)
        this->A[i] = value;
        this->length++;
    }
    if (this->length == this->size) {  // Check if array is full
        throw ArrayException("Array is full!");
    }
    
    // Shift all elements above the index to make space
    for (uint32_t index = this->length; index > i; index--) {
        this->A[index] = this->A[index - 1];
    }
    this->A[i] = value; // Update value at index (i.e. perform the insertion)
    this->length++; // Don't forget to update the length
}

uint32_t Array::search(uint32_t value, searchmethod_e searchMethod) {
    for (int i = 0; i < this->length; ++i) {
        if (this->A[i] == value) { // Value found!
            switch(searchMethod) {
                case frequencySearch:
                    this->swap(i, i-1);
                case swapToBeginSearch:
                    this->swap(i, 0);
                case linearSearch:
            }
            return i;
        }
    }
    throw ArrayException("Value does not exist!");
}

uint32_t Array::iterativeBinarySearch(uint32_t key) {
    uint32_t low, mid, high;
    low =  0;
    high = this->length;
    while (low < high) {
        mid = (low + high) / 2;
        if (this->A[mid] == key) { // We found the value!
            return mid;
        }
        // If in higher half, update low to be 1 greater than the mid that was just checked
        if (key > this->A[mid]) {
            low = mid + 1;
        }
        // If in lower half, update the high to be 1 less than the mid that was just checked
        if (key < this->A[mid]) {
            high = mid - 1;
        }
    }
    throw ArrayException("Value not found!");
}

uint32_t Array::binarySearchRecursive(uint32_t low, uint32_t high, uint32_t key) {
    static uint32_t mid = (low + high) / 2;
    if (this->A[mid] == key) { // found
        return mid;
    }
    if (key > this->A[mid]) {
        return binarySearchRecursive(mid + 1, high, key);
    }
    else {
        return binarySearchRecursive(low, mid - 1, key);
    }
}

void Array::del(uint32_t index) {
    if (index >= this->length) {
        throw ArrayException("Index out of range!");
    }
    for (int i = index; i < this->length-1; i++) {
        this->A[i] = this->A[i+1];
    }
    this->A[this->length-1] = 0;
    this->length--;
}

/*
 Destructor to free dynamically allocated memory (on the heap when the object is destroyed)
 This is automatically invoked when the caller goes out of scope.
 */
Array::~Array(void) {
    freeMemory(this->A);
}
