#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

#include "headers/bubbleSort.hpp"

using namespace std;

array<int, arraySize> CreateSortingArray() {
    // array (1-arraySize)
    array<int, arraySize> arr;

    // load array with numbers 1-arraySize
    for(int i = 0; i < arraySize; i++)
        arr[i] = i+1;

    // get a time-based random seed
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();

    // shuffle the array
    shuffle(
        arr.begin(),
        arr.end(),
        std::default_random_engine(seed)
    );

    return arr;
}

array<int, arraySize> BubbleSortStep(array<int, arraySize> arr) {
    // loop through elements
    for(int i = 0; i < arraySize; i++) {
        // if element isn't the very last one in the array
        if(i != arraySize-1) {
            // if the indexed element is more than the elemtent in front of it
            if(arr[i] > arr[i+1]) {
                // switch them around

                // save them to other variables first
                int num1 = arr[i];
                int num2 = arr[i+1];

                // set both numbers to the other
                arr[i] = num2;
                arr[i+1] = num1;
            }
        }
    }

    return arr;
}