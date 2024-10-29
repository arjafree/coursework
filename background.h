typedef struct coords{
    int x;
    int y;
}coords;
typedef struct size{
    int width;
    int height;
}size;
coords drawBackground(int whitespace, size stadiumSize, int gridSize);
coords randomCooords();
int** getGrid();