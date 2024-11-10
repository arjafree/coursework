#include <stdio.h>
#include "graphics.h"
#include "background.h"
#include <stdlib.h>
#include <time.h>
#include "robot.h"
#include <stdbool.h>

Bot robot;
int** grid;
Dimensions gridDimensions;
int gridSize;
Coords arenaCoords;

int totalMarkers;
int robotMarkerCount;
int sleepTime;

int colDirections[4] = {0, 1, 0, -1};
int rowDirections[4] = {-1, 0, 1, 0};

char robotImages[4][11] = {"robot0.png", "robot1.png", "robot2.png", "robot3.png"};


Coords initRobotCoords(){
    while(true){
        robot.botPixelCoords = randomCoords();
        if(grid[getIndex(robot.botPixelCoords).row][getIndex(robot.botPixelCoords).col]==1){
            return robot.botPixelCoords;
        }
        
    }
}

void generateBot(){
    grid = getGrid();
    gridDimensions = getGridDimensions();
    robot.direction = rand()%4;
    displayImage(robotImages[robot.direction], robot.botPixelCoords.x, robot.botPixelCoords.y);
    robot.botIndex = getIndex(robot.botPixelCoords);
    grid[robot.botIndex.row][robot.botIndex.col] = 4;
    background();
    displayImage("home.png", robot.botPixelCoords.x, robot.botPixelCoords.y);
    foreground();
    totalMarkers = getNumMarks();
    
}

bool canMoveForward(int** visited){
    Index checkIndex = robot.botIndex;
    switch(robot.direction){
            case(0): checkIndex.row--;
                break;
            case(1): checkIndex.col++;
                break;
            case(2): checkIndex.row++;
                break;
            case(3): checkIndex.col--;
                break;
    }
    return(!(checkIndex.col<0||checkIndex.row<0||checkIndex.row>gridDimensions.height-1||checkIndex.col>gridDimensions.width-1||
    visited[checkIndex.row][checkIndex.col]||grid[checkIndex.row][checkIndex.col]==3||!grid[checkIndex.row][checkIndex.col]));

}


bool checkBoundaries(Index index){
    if(index.col<0||index.row<0||index.col>=gridDimensions.width-1||index.row>=gridDimensions.height-1){
        return false;
    }
    return true;
}


Index getForward(){
    Index returnIndex = robot.botIndex;
    switch(robot.direction){
        case(0):
            returnIndex.row--;
            break;
        case(1):
            returnIndex.col++;
            break;
        case(2):
            returnIndex.row++;
            break;
        case(3):
            returnIndex.col--;
            break;
    }
    //printf("\n%i, %i\n", returnIndex.col, returnIndex.row);
    return returnIndex;

}

void right(){
    sleep(sleepTime);
    robot.direction = (robot.direction+1)%4;
    clear();
    displayImage(robotImages[robot.direction], robot.botPixelCoords.x, robot.botPixelCoords.y);
}


void forward(){
    sleep(sleepTime);
    clear();
    switch(robot.direction){
        //facing forwards
        case(0):
            displayImage(robotImages[robot.direction], robot.botPixelCoords.x, robot.botPixelCoords.y-=gridSize);
            robot.botIndex.row--;
            break;
        case(1):
            displayImage(robotImages[robot.direction], robot.botPixelCoords.x+=gridSize, robot.botPixelCoords.y);
            robot.botIndex.col++;
            break;
        //facing south
        case(2):
            displayImage(robotImages[robot.direction], robot.botPixelCoords.x, robot.botPixelCoords.y+=gridSize);
            robot.botIndex.row++;
            break;
        //facing west
        case(3):
            displayImage(robotImages[robot.direction], robot.botPixelCoords.x-=gridSize, robot.botPixelCoords.y);
            robot.botIndex.col--;
            break;
    }
}

int atMarker(){
    if (grid[robot.botIndex.row][robot.botIndex.col] == 2) {
        return 1;
    }
    else{
        return 0;
    }
}

void dropMarker(){
    robotMarkerCount--;
}

void pickUpMarker(){
    robotMarkerCount++;
    clearMarker(robot.botIndex);
}


int** initVisited(){
    int** visited = (int**)malloc(getGridDimensions().height * sizeof(int*));
    for (int k = 0; k < getGridDimensions().height; k++) {
        visited[k] = (int*)malloc(getGridDimensions().width * sizeof(int));
        for (int l = 0; l < getGridDimensions().width; l++) {
            visited[k][l] = 0;
        }
    }
    return visited;
}

void freeVisited(int** visited){
    for (int k = 0; k < getGridDimensions().height; k++) {
            free(visited[k]);
    }
    free(visited);
}



void dfs(int** visited, int findingMarker){
    visited[robot.botIndex.row][robot.botIndex.col] = 1;
    if (findingMarker&&grid[robot.botIndex.row][robot.botIndex.col] == 2) {
        //printf("\nMarker found at: row: %d, col: %d\n", robot.botIndex.row, robot.botIndex.col);
        pickUpMarker();
        if(robotMarkerCount==totalMarkers){
            dfs(visited, 0);
        }
    }
    if(!findingMarker&&grid[robot.botIndex.row][robot.botIndex.col]==4){
        while(robotMarkerCount){
            dropMarker();
        }
        return;
    }
    
    int rotation = 4;
    while(rotation--){
        if (canMoveForward(visited)){
            forward();
            dfs(visited, findingMarker);
            right(); right();
            forward();
            right(); right();
        }
        right();
        
    }
    //return;
}



void pickUpMarkers(){
    int** visited = initVisited();
    dfs(visited, 2);
    freeVisited(visited);
}

void dropOffMarkers(){
    int** visited = initVisited();
    dfs(visited, 0);
    freeVisited(visited);
}

void activateRobot(int gridSize){
    sleepTime = 25;
    gridSize = gridSize;
    robotMarkerCount = 0;
    foreground();
    generateBot();
    pickUpMarkers();
    dropOffMarkers();
}



