#include "graphics.h"
#include "background.h"
#include <stdlib.h>
#include "robot.h"

Bot robot;
Dimensions gridDimensions;

//different identifiers for the robot file
int** grid_r;
int gridSize_r;

int totalMarkers;
int robotMarkerCount;
int sleepTime;

int colDirections[4] = {0, 1, 0, -1};
int rowDirections[4] = {-1, 0, 1, 0};

//different images for the different directions of the robot
char robotImages[4][11] = {"robot0.png", "robot1.png", "robot2.png", "robot3.png"};


Coords initRobotCoords(){
    grid_r = getGrid();
    while(1){
        robot.botPixelCoords = randomCoords();
        //ensures that the robot's starting position is an empty grid square
        if(grid_r[getIndex(robot.botPixelCoords).row][getIndex(robot.botPixelCoords).col]==1){
            //setting the 'home' tile with value 4, as the tile which the robot spawns from
            grid_r[getIndex(robot.botPixelCoords).row][getIndex(robot.botPixelCoords).col] = 4;
            return robot.botPixelCoords;
        }
        
    }
}

void generateBot(){
    gridDimensions = getGridDimensions();
    //generates a random direction for the robot in range [0,3]
    robot.direction = rand()%4;

    displayImage(robotImages[robot.direction], robot.botPixelCoords.x, robot.botPixelCoords.y);
    robot.botIndex = getIndex(robot.botPixelCoords);
    background();
    displayImage("home.png", robot.botPixelCoords.x, robot.botPixelCoords.y);
    foreground();

    totalMarkers = getNumMarks();
}

int canMoveForward(int** visited){
    
    Index checkIndex = (Index) {robot.botIndex.row+rowDirections[robot.direction], robot.botIndex.col+colDirections[robot.direction]};

    //Checks that, if it moved forward, the robot won't exceed the grid boundary, will not step onto the abnormality and won't stop onto an obstacle
    return(!(checkIndex.col<0||checkIndex.row<0||checkIndex.row>gridDimensions.height-1||checkIndex.col>gridDimensions.width-1||
    visited[checkIndex.row][checkIndex.col]||grid_r[checkIndex.row][checkIndex.col]==3||!grid_r[checkIndex.row][checkIndex.col]));

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
    //Re-displaying the robot, one grid forward, based on its current direction and updating its coordinates and index
    displayImage(robotImages[robot.direction], robot.botPixelCoords.x+=(gridSize_r*colDirections[robot.direction]), robot.botPixelCoords.y+=((gridSize_r*rowDirections[robot.direction])));
    robot.botIndex = (Index) {robot.botIndex.row+rowDirections[robot.direction], robot.botIndex.col+colDirections[robot.direction]};
}

int atMarker(){
    return(grid_r[robot.botIndex.row][robot.botIndex.col] == 2);
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


void dfs(int** visited, int findingMarker){
    visited[robot.botIndex.row][robot.botIndex.col] = 1;
    if (findingMarker&&grid_r[robot.botIndex.row][robot.botIndex.col] == 2) {
        pickUpMarker();
        if(robotMarkerCount==totalMarkers){
            dfs(visited, 0);
        }
    }
    if(!findingMarker&&grid_r[robot.botIndex.row][robot.botIndex.col]==4){
        return;
    }

    for(int i  = 0; i<4;i++){
        if (canMoveForward(visited)){
            forward();
            dfs(visited, findingMarker);
            right(); right(); 
            forward();
            right(); right();
        }
        right();
    }
}


void startRobotJourney(){
    int** visited = initVisited();
    dfs(visited, 2);
    free2d(visited);
}


void activateRobot(int gridSize){
    sleepTime = 25;
    gridSize_r = gridSize;
    robotMarkerCount = 0;
    foreground();
    generateBot();
    startRobotJourney();
    while(robotMarkerCount){
        dropMarker();
    }
}



