#ifndef _BUBBLE_SORT_HPP_
#define _BUBBLE_SORT_HPP_

#include <iostream>
#include <array>

using namespace std;

#include "settings.hpp"

// returns std::array<int, arraySize> type with numbers ranging from 1-20, each one is mentioned only once and they are in mixed order
array<int, arraySize> CreateSortingArray();

// steps through one iteration of bubble sorting
array<int, arraySize> BubbleSortStep(array<int, arraySize> arr);

#endif