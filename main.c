#include <stdio.h>
#include "graphics.h"
#include "background.h"
#include "robot.h"
#include <time.h>
#include <stdlib.h>

size windowSize;

int main(void){
    srand(time(NULL));
    coords startingCoords;
    windowSize.width = 600;
    windowSize.height = 400;
    //the space beetween the window and the stadium
    int whitespace = 25;
    setWindowSize(windowSize.width,windowSize.height);
    int gridSize = 25;
    background();
    coords markerCoords = drawBackground(whitespace, windowSize, gridSize);
    int** grid = getGrid();
    foreground();
    coords botCoords = generateBot();
    sleep(500);
    clear();
    return 0;
}
