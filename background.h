typedef struct Coords{
    int x;
    int y;
}Coords;
typedef struct Dimensions{
    int width;
    int height;
}Dimensions;
typedef struct Index{
    int row;
    int col;
}Index;
void drawBackground(int maxMarkers, int maxObs, int whitespace, Dimensions stadiumDimensions);
Coords randomCoords();
Index getIndex(Coords botCoords);
Dimensions getGridDimensions();
Coords getArenaCoords();
int** getGrid();
void clearMarker(Index markerIndex);
int getNumMarks();
void freeAll();