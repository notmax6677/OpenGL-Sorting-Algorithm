# OpenGL-Sorting-Algorithm
Bubble sort visualizer programmed in OpenGL 3.3 _(Using GLAD and GLFW 3.3)_

<br>

<!-- gif preview of app -->
<div align="center">
  <img src="./sortingAlgorithm.gif" alt="Sorting Algorithm Preview" width=500></img>
</div>

<br>

Not much to say, it looks satisfying i guess. I made this because i saw others do it on the internet and also i wanted to exercise some OpenGL skills since a the time of this README's creation, i have just started learning OpenGL a few weeks back.

Build with `./bin/Makefile` for your system, `.exe` is already included because i worked on this on a windows machine.

Use `SPACE` to reset the algorithm and begin the process anew with randomized values.

Do keep note that while the algorithm may seem slow and impractical, this is not the case, it just looks like it because to visualize the process properly for the user, the program only takes one "sorting step" per frame, so if you're running at 60fps, do the math...
However, if need be, this whole process could be done in an instant in a single frame when applied to a real situation.

In `./src/headers/settings.hpp` you will find two values:
1) `bool slowSort` - If `true`, the sorting process will be slowed down even further to allow for you to more closely see how it looks.
2) `int arraySize` - Defines the amount of numbers that shall be sorted in the visualized array.

<br>

_Remember to build the project again if you choose to change these values, i know it's not the most efficient way but it is what it is ig..._
