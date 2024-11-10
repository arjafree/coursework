typedef struct Bot{
    Index botIndex;
    Coords botPixelCoords;
    int direction;
}Bot;
void activateRobot(int gridSize);
Coords initRobotCoords();