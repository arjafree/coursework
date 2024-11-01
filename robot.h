#include <stdlib.h>
typedef struct bot{
    coords botCoords;
    coords botPixelCoods;
    int direction;
}bot;

coords generateBot();
coords moveForward(coords currCoords, int gridSize);