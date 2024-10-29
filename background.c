#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <stdbool.h>
#include <time.h>
#include "background.h"

int** grid;

void drawGrid(int startingX, int startingY, size arenaSize, int gridSize);
void drawMarker(coords mCoords, int gridSize);

coords randomCooords(){
    coords returnCoordinates;
    returnCoordinates.x = 25*(rand()%(18)+3);
    returnCoordinates.y = 25*(rand()%(10)+3);
    return returnCoordinates;

}

coords randomCoords(int gridSize, size arenaSize, coords arenaCoords){
    coords returnCoordinates;
    returnCoordinates.x = gridSize*(rand()%(arenaSize.width/gridSize)+(arenaCoords.x/gridSize));
    returnCoordinates.y = gridSize*(rand()%(arenaSize.height/gridSize)+(arenaCoords.y/gridSize));
    return returnCoordinates;
}

void drawStadium(coords stadiumCoords, size stadiumSize){
    setColour(gray);
    fillRect(stadiumCoords.x, stadiumCoords.y, stadiumSize.width, stadiumSize.height);

}

//playable arena is the stadium without the wall 
coords drawArena(coords stadiumCoords, size stadiumSize, int wallSize, int gridSize){
    size arenaSize;
    arenaSize.width = stadiumSize.width - wallSize*2;
    arenaSize.height = stadiumSize.height - wallSize*2;

    coords arenaCoords;
    arenaCoords.x = stadiumCoords.x + wallSize;
    arenaCoords.y = stadiumCoords.y + wallSize;

    setColour(white);
    fillRect(arenaCoords.x, arenaCoords.y, arenaSize.width, arenaSize.height);

    drawGrid(arenaCoords.x, arenaCoords.y, arenaSize, gridSize);
    coords markerCoords = randomCoords(gridSize, arenaSize, arenaCoords);
    drawMarker(markerCoords, gridSize);

    //grid[(markerCoords.y-arenaCoords.y)/gridSize][(markerCoords.x-arenaCoords.x)/gridSize] = 1;
    return markerCoords;
}


coords drawBackground(int whitespace, size windowSize, int gridSize){
    coords stadiumCoords;
    stadiumCoords.x = whitespace;
    stadiumCoords.y = whitespace;

    size stadiumSize;
    stadiumSize.height = windowSize.height - whitespace*2;
    stadiumSize.width = windowSize.width - whitespace*2;

    drawStadium(stadiumCoords, stadiumSize);
    int wallSize = 25;

    return drawArena(stadiumCoords, stadiumSize, wallSize, gridSize);
}

void drawGrid(int startingX, int startingY, size arenaSize, int gridSize){
    int** grid = (int**)malloc(arenaSize.height/gridSize * sizeof(int*));
    for (int i = 0; i < arenaSize.height/gridSize; i++) {
        grid[i] = (int*)malloc(arenaSize.width/gridSize * sizeof(int));
    }

    int currX = startingX;
    int currY = startingY;
    setColour(black);

    drawRect(currX, currY, gridSize, gridSize);
    
    for(int i = 0; i<arenaSize.height/gridSize; i++){
        for(int j = 0; j<arenaSize.width/gridSize; j++){
            grid[i][j] = 0;
            drawRect(currX, currY, gridSize, gridSize);
            currX+=gridSize;
        }
        currX = startingX;
        currY+=gridSize;
    }
}

int** getGrid(){
    return grid;
}

void updateGrid(coords coords, int state){
    
}


void drawMarker(coords mCoords, int gridSize){
    setColour(green);
    fillRect(mCoords.x+1,mCoords.y+1,gridSize-1,gridSize-1);

}