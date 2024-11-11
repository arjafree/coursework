Program compilation command:
gcc -o main main.c graphics.c background.c robot.c

Program run command:
./main | java -jar drawapp-4.0.jar

**customisation**
You may customise this program, in main.c you can change the maximum size of the window, the max number of markers and obstacles as well as the whitespace. Please note, that the whitespace 
is also the same value that will be used for grid size as well as the wall between the grid and the stadium, so if your max/min window sizes are too small for the whitespace, then the program 
will not run. Additionally, please remember that the program will not run if there are too many obstacles such that the markers are not accessible, so please do keep the number of max obstacles and
markers reasonable if you want the program to run. 

**what it does**
For this assignment, I created a program which:
    a) Generates a randomly sized and shaped arena, with a random number of obstacles and markers. The arena is split into a grid
    b) Spawns in a single robot, in a random grid location, and the robot must be able to make it to all the markers
    c) Guides the robot through the arena, making it pick up all markers and not move onto any obstacles or out of bounds
Thus, the program is at stage 7 from the CCourswork.pdf requirements list.

**how it does it (briefly)**
a) With the exception of a few values passed in from main.c, the handling of part a is done entirely in the source code file, background.c. The arena's size is determined by the (randomly determined) 
size of the window, and the size of the whitespace. A 2d grid is drawn, the obstacles and markers are generated, with the program storing the status of each grid space (0 for obstacle, 1 for empty, 
2 for marker, 3 for wall, 4 for robot home). Some random abnormality in the bottom left quadrant of the grid, is created to make the arena a random shape each time the program is run.

b) In order for the robot to be able to make it to all the markers, the robot's coordinates also have to be initialised within the background.c source code. This is the reason robot.h is included in 
background.c. From here, a depth first search is conducted using recursion in order to ensure that each marker is accessible, and if the marker is not accessible, then the obstacles will delete, and 
re-generate again to random positions. This occurs within the generateElements function. 

c) The robot's movements are handled within robot.c. When the robot is activated by the main.c source code, the robot's direction is randomised, its "home" grid space is allocated to wherever it 
spawned, and the robot's search begins. The robot conducts a thorough search using a dfs-based recursion method in order to find all the  markers and return back to its home. 