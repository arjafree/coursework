#include <stdio.h>
#include "graphics.h"
#include "background.h"
#include "robot.h"
#include <time.h>
#include <stdlib.h>

#define MAX_MARKERS 6
#define MAX_OBSTACLES 6
#define WHITESPACE 25
#define MIN_WINDOW_SIZE 300
#define MAX_WINDOW_SIZE 500

void initializeWindow(Dimensions* windowDimensions, int gridSize) {
    // Set the window dimensions to a random size divisible by gridSize, and between MIN_WINDOW_SIZE and MAX_WINDOW_SIZE
    windowDimensions->height = gridSize * (rand()%((MAX_WINDOW_SIZE / gridSize)-(MIN_WINDOW_SIZE / gridSize)) + (MIN_WINDOW_SIZE / gridSize));
    windowDimensions->width = gridSize * (rand()%((MAX_WINDOW_SIZE / gridSize)-(MIN_WINDOW_SIZE / gridSize)) + (MIN_WINDOW_SIZE / gridSize));
    setWindowSize(windowDimensions->width, windowDimensions->height);
}

int main(void){
    srand(time(NULL)); // seed the random number generator
    Dimensions windowDimensions;
    initializeWindow(&windowDimensions, WHITESPACE);

    background();
    drawBackground(MAX_MARKERS, MAX_OBSTACLES, WHITESPACE, windowDimensions);

    activateRobot(WHITESPACE);

    freeAll(); //free all manually allocated memory used that haven't been freed yet

    return 0;
}
