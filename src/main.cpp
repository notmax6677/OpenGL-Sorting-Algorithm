#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include <cmath>

#include "headers/shader.hpp"
#include "headers/bar.hpp"

#include "headers/vectors.hpp"

#include "headers/bubbleSort.hpp"

#include "headers/settings.hpp"

using namespace std;

// initial window size
const int INIT_SCR_WIDTH = 1000;
const int INIT_SCR_HEIGHT = 600;

// array that holds numbers 1-20 in a mixed order
array<int, arraySize> arr = CreateSortingArray();

// record last array
array<int, arraySize> lastArr = arr;

// has sorted during that specific frame
bool hasSorted = false;

// has finished sorting
bool finishedSort = false;

// counts up each frame and each bar that is equal or lower than it is highlighted green
int finishedCounter = 0;

void sortCallback() {
    if(!finishedSort) {
        // record array before changing it
        lastArr = arr;

        if(slowSort) {
            // is hasn't sorted during time frame yet
            if(!hasSorted) {
                // bubble sort step
                arr = BubbleSortStep(arr);
                
                //cout << endl;
            }
            // set hasSorted to true
            hasSorted = true;
        }
        else {
            // just do step
            arr = BubbleSortStep(arr);
        }

        // if array has been completed (check if new array is equal to last array) then enable finished sort
        if(arr == lastArr) {
            finishedSort = true;
            finishedCounter = 0; // reset finished counter
        }
    }
}


// all other init functions are here
void init() {
    InitBar();
}

// framebuffer resizing callback
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// key callback function
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // reset array
        arr = CreateSortingArray();

        // reset finishedSort
        finishedSort = false;
    }
}

int main() {
    // glfw error stuff
    int glfwErrorCode;
    const char* glfwErrorCodeDescription;

    // init glfw
    glfwInit();

    // error code
    glfwErrorCode = glfwGetError(&glfwErrorCodeDescription);

    // handle error
    if(glfwErrorCode != GLFW_NO_ERROR) {
        cout << "ERROR - FAILED TO LOAD GLFW: " << glfwErrorCodeDescription << endl;
        return -1;
    }

    // window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // setting required to work on macos
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // create window
    GLFWwindow* window = glfwCreateWindow(INIT_SCR_WIDTH, INIT_SCR_HEIGHT, "Sorting Algorithm", NULL, NULL);

    // error code
    glfwErrorCode = glfwGetError(&glfwErrorCodeDescription);

    // handle error
    if(glfwErrorCode != GLFW_NO_ERROR) {
        cout << "ERROR - FAILED TO CREATE WINDOW: " << glfwErrorCodeDescription << endl;
        return -1;
    }

    // set opengl context
    glfwMakeContextCurrent(window);

    // load glad and display error if something went wrong
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "ERROR - FAILED TO LOAD GLAD" << endl;
        return -1;
    }

    // set window resize callback
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // set keypress callback
    glfwSetKeyCallback(window, keyCallBack);

    // call init
    init();

    // save last time there to work out delta time each frame
    float lastGlfwTime = 0;

    // sort count to count when to update array and call sort step
    float sortCount = 0;

    // record last frame's sort count
    float lastSortCount = 0;

    // loop
    while(!glfwWindowShouldClose(window)) {
        // swap buffers
        glfwSwapBuffers(window);

        // poll for events
        glfwPollEvents();

        // set clear color buffer
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

        // clear with color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // calculate dt
        float deltaTime = glfwGetTime() - lastGlfwTime;
        lastGlfwTime = glfwGetTime();

        // add dt to sortCount
        sortCount += deltaTime;

        // if at slow sorting speed
        if(slowSort) {
            // if sortCount is more than lastSortCount + 0.2
            if(sortCount > lastSortCount+0.2) {
                sortCallback();
            }
            else {
                hasSorted = false;
            }

            // set last sort count to equal sortCount rounded DOWN to the nearest 0.2
            lastSortCount = sortCount - fmod(sortCount, 0.2);
        }
        else {
            sortCallback();
        }

        // if the sort has finished increment finishedCounter by 1 hundredth of arraySize
        if(finishedSort) {
            finishedCounter += arraySize/100;
        }

        // draw bars, iterate through arraySize cus thats the amount of numbers in our array
        for(int i = 0; i < arraySize; i++) {
            // if i is less than or equal to the finished counter and the sort has finished
            if(i <= finishedCounter && finishedSort)
                DrawBar(
                    barWidth*i, 0, (float)arr[i]/arraySize, Vector4{0.2f, 0.9f, 0.2f, 1.0f} // green
                );
            // if number has swapped last frame
            else if(lastArr[i] != arr[i] && lastArr[i] > arr[i])
                DrawBar(
                    barWidth*i, 0, (float)arr[i]/arraySize, Vector4{1.0f, 0.3f, 0.5f, 1.0f} // pink-ish
                );
            // if number is in place
            else
                DrawBar(
                    barWidth*i, 0, (float)arr[i]/arraySize, Vector4{1.0f, 1.0f, 1.0f, 1.0f} // white
                );
        }
    }

    // terminate glfw
    glfwTerminate();

    // return 0
    return 0;
}

