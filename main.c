#include <stdio.h>
#include "graphics.h"
#include "background.h"
#include "robot.h"
#include <time.h>
#include <stdlib.h>


int main(void){
    srand(time(NULL));

    background();
    coords startingCoords;
    size windowSize;
    windowSize.width = 600;
    windowSize.height = 400;
    setWindowSize(windowSize.width,windowSize.height);
    int whitespace = 25;
    int gridSize = 25;
    coords markerCoords = drawBackground(whitespace, windowSize, gridSize);
    int** grid = getGrid();

    foreground();
    coords botCoords = generateBot();
    botCoords = moveForward(botCoords, gridSize);
    return 0;
}
