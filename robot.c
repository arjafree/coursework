#include <stdio.h>
#include "graphics.h"
#include "background.h"
#include <stdlib.h>
#include <time.h>
#include "robot.h"

bot robot;
coords generateBot(){
    coords botCoords = randomCooords();
    displayImage("robot.png", botCoords.x, botCoords.y);
    robot.botCoords = botCoords;
    robot.direction = 0;
    return botCoords;
}

coords moveForward(coords currCoords, int gridSize){

    sleep(500);
    clear();
    
    switch(robot.direction){
        //facing forwards
        case(0):
            displayImage("robot.png", currCoords.x, currCoords.y-=gridSize);
            break;

        //facing east
        case(1):
            displayImage("robot.png", currCoords.x+=gridSize, currCoords.y);
            break;

        //facing south
        case(2):
            displayImage("robot.png", currCoords.x, currCoords.y+=gridSize);
            break;
        
        //facing west
        case(3):
            displayImage("robot.png", currCoords.x-=gridSize, currCoords.y);
            break;
    }
    return currCoords;
}

void rotate(int newDirection){
    robot.direction = newDirection;
}