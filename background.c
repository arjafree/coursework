#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <stdbool.h>
#include <time.h>
#include "background.h"
#include "robot.h"

int** grid;
Coords* markers;
Coords* obstacles;
int gridSize;
int markersFound;
int numMarks;
Dimensions arenaDimensions;
Coords arenaCoords;

void generateElements(int maxMarkers, int maxObs);
void generateExtraFunk();
void free2d(int** arr);
Dimensions getGridDimensions();

Coords randomCoords(){
    Coords returnCoordinates;
    //returns a value that is divisible by gridSize, between arenaCoords (uppermost left corner of the grid) and arenaDimensions.width (bottommost right corner of the grid)
    returnCoordinates.x = gridSize * (rand() % ((arenaDimensions.width / gridSize) - (arenaCoords.x / gridSize) + 1) + (arenaCoords.x / gridSize));
    returnCoordinates.y = gridSize * (rand() % ((arenaDimensions.height / gridSize) - (arenaCoords.y / gridSize) + 1) + (arenaCoords.y / gridSize));
    return returnCoordinates;
}

//drawing functions

void drawStadium(Coords stadiumCoords, Dimensions stadiumDimensions, int wallSize){
    setColour(gray);
    fillRect(stadiumCoords.x, stadiumCoords.y, stadiumDimensions.width, stadiumDimensions.height);

    //playable arena is the stadium, minus the wall
    arenaDimensions.width = stadiumDimensions.width - wallSize*2;
    arenaDimensions.height = stadiumDimensions.height - wallSize*2;

    arenaCoords.x = stadiumCoords.x + wallSize;
    arenaCoords.y = stadiumCoords.y + wallSize;

    setColour(white);
    fillRect(arenaCoords.x, arenaCoords.y, arenaDimensions.width, arenaDimensions.height);
}

void drawGrid(){
    int currX = arenaCoords.x;
    int currY = arenaCoords.y;
    grid = (int**)malloc(getGridDimensions().height * sizeof(int*));
    setColour(black);
    drawRect(currX, currY, gridSize, gridSize);
    for (int i = 0; i < getGridDimensions().height; i++) {
        grid[i] = (int*)malloc(getGridDimensions().width * sizeof(int));
        for(int j = 0; j<getGridDimensions().width; j++){
            //signals an empty square
            grid[i][j] = 1;
            drawRect(currX, currY, gridSize, gridSize);
            currX+=gridSize;
        }
        currX = arenaCoords.x;
        currY+=gridSize;
    }
}

void drawBackground(int maxMarkers, int maxObs, int whitespace, Dimensions windowDimensions){
    gridSize = whitespace;
    int wallSize = whitespace; 
    Coords stadiumCoords = (Coords){whitespace, whitespace};
    Dimensions stadiumDimensions = (Dimensions){windowDimensions.width - whitespace*2, windowDimensions.height - whitespace*2};
    drawStadium(stadiumCoords, stadiumDimensions, wallSize);
    drawGrid();
    generateExtraFunk();
    generateElements(maxMarkers, maxObs);
    markersFound = 0;
}

void drawMarkers(){
    setColour(green);
    for(int i = 0; i<numMarks; i++){
        fillRect(markers[i].x+1,markers[i].y+1,gridSize-1,gridSize-1);
    }

}

//helper functions

int checkDuplicateMarkers(Coords markerCoords){
    for(int i = 0; i<numMarks;i++){
        if(markers[i].x == markerCoords.x && markers[i].y == markerCoords.y){
            return 1;
        }
    }
    return 0;
}   

void generateMarkers(){
    Coords currMkrCoords;
    Index currMkrIndex;
    markers = (Coords*)malloc(numMarks*sizeof(Coords));
    for(int i = 0; i<numMarks; i++){
        currMkrCoords = randomCoords();
        currMkrIndex = getIndex(currMkrCoords);
        if(checkDuplicateMarkers(currMkrCoords)){
            i--;
        }
        else if(!grid[currMkrIndex.row][currMkrIndex.col]||grid[currMkrIndex.row][currMkrIndex.col]==3){
            i--;;
        }
        else{
            grid[currMkrIndex.row][currMkrIndex.col] = 2;
            markers[i] = currMkrCoords;
        }
    }
    drawMarkers();
}


bool isPathAccessible(Index startIndex, Index targetIndex, int** visited) {
    //maxIndex = rows - 1, cols - 1
    if (startIndex.row < 0 || startIndex.col < 0 || startIndex.row > getGridDimensions().height-1 || startIndex.col > getGridDimensions().width-1||
        !grid[startIndex.row][startIndex.col]|| grid[startIndex.row][startIndex.col]==3|| visited[startIndex.row][startIndex.col]){
        return false;
    }
    if (startIndex.row == targetIndex.row && startIndex.col == targetIndex.col) {
        return true;
    }
    visited[startIndex.row][startIndex.col] = 1;
    Index startIndexLeft = startIndex;
    startIndexLeft.col--;
    Index startIndexRight = startIndex;
    startIndexRight.col++;
    Index startIndexForward = startIndex;
    startIndexForward.row--;
    Index startIndexBack = startIndex;
    startIndexBack.row++;
    // Explore all four directions
    return(isPathAccessible(startIndexLeft, targetIndex, visited) || isPathAccessible(startIndexRight, targetIndex, visited) || isPathAccessible(startIndexForward, targetIndex, visited) ||
        isPathAccessible(startIndexBack, targetIndex, visited));
}

int** mallocVisited(){
    int** visited = (int**)malloc(getGridDimensions().height * sizeof(int*));
    for (int k = 0; k < getGridDimensions().height; k++) {
        visited[k] = (int*)malloc(getGridDimensions().width * sizeof(int));
        for (int l = 0; l < getGridDimensions().width; l++) {
            visited[k][l] = 0;
        }
    }
    return visited;

}

void generateElements(int maxMarkers, int maxObs){
    numMarks = rand()%maxMarkers+1;
    int numObs = rand()%maxObs+1;
    generateMarkers();
    Coords startingCoords = initRobotCoords();
    Index startingIndex = getIndex(startingCoords);
    int** visited;
    setColour(red);
    for (int i = 0; i < numObs; i++) {
        Coords obsCoords;
        Index obsIndex;
        do {
            obsCoords = randomCoords();
            obsIndex = getIndex(obsCoords);
            visited = mallocVisited();
        } while (grid[obsIndex.row][obsIndex.col] != 1 || !isPathAccessible(startingIndex, obsIndex, visited));
        // Place the obstacle
        grid[obsIndex.row][obsIndex.col] = 0;
        fillRect(obsCoords.x + 1, obsCoords.y + 1, gridSize - 1, gridSize - 1);
    }
    free2d(visited);
}  
    
int** getGrid(){
    return grid;
}

Index getIndex(Coords coords){
    //Index struct is int row, int col
    return (Index) {(coords.y-arenaCoords.y)/gridSize, (coords.x-arenaCoords.x)/gridSize};
}

Dimensions getGridDimensions(){
    //Dimensions struct is widht, height
    return (Dimensions) {arenaDimensions.width/gridSize, arenaDimensions.height/gridSize};
}


Coords getArenaCoords(){
    return arenaCoords;
}

void clearMarker(Index markerIndex){
    grid[markerIndex.row][markerIndex.col] = 1;
    Coords markerCoords;
    markerCoords.x = markerIndex.col*gridSize+arenaCoords.x;
    markerCoords.y = markerIndex.row*gridSize+arenaCoords.y;
    background();
    setColour(white);
    fillRect(markerCoords.x+1,markerCoords.y+1,gridSize-1,gridSize-1);
    foreground();
}

void generateExtraFunk(){
    setColour(gray);
    int Y = rand()%(getGridDimensions().height - getGridDimensions().height/2) + getGridDimensions().height/4;
    Coords currCoords;
    for(int i = getGridDimensions().height-1; i>Y; i--){
        currCoords.y = i*gridSize+arenaCoords.y;
        for(int j = 0; j<=(rand()%(getGridDimensions().width/2-getGridDimensions().width/4)+getGridDimensions().width/4); j++){
            currCoords.x = j*gridSize+arenaCoords.x;
            fillRect(currCoords.x, currCoords.y, gridSize+1, gridSize+1);
            grid[i][j] = 3;
        }
    }
}

void free2d(int** arr) {
    for (int i = 0; i < getGridDimensions().height; i++) {
        free(arr[i]);
    }
    free(arr);
}

void freeAll() {
    free2d(grid);
    free(obstacles);
    free(markers);
}

int getNumMarks(){
    return numMarks;
}