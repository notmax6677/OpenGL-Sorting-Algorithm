#ifndef _BAR_HPP_
#define _BAR_HPP_

#include "vectors.hpp"

#include "bubbleSort.hpp"

// bar width
const float barWidth = 2.0f/arraySize;

// initiates bar and defines a mesh for drawing bars
void InitBar();

// draws a line at given location
void DrawBar(float x, float y, float height, Vector4 color);

#endif