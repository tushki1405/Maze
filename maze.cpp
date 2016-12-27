/**
 * Maze creation and solving using Recursive Backtracking. With recursive
 * backtracking, there can be long paths but there always will be a path.
 * Tushar Gupta
 * Future work: 
 * - Can randomly pick source as well.
 * - Implement different algorithms for implementing maze.
 * - Take width and height as input parameters.
 */
#include <iostream>
#include <algorithm>

using namespace std;

//Width and height of the maze.
const int width = 10;
const int height = 10;

//A node in the maze.
struct gridNode {
    bool visited, top, bottom, left, right;
    //0-nothing, 1-path, 2-destination
    int value;
};

gridNode grid[height][width];
//Destination of maze selected randomly.
int destinationX, destinationY;

//Initialize the grid and set default values.
void initializeGrid() {
   for(int i=0; i<height; i++) {
       for(int j=0; j<width; j++) {
           grid[i][j].visited = false; 
           grid[i][j].top = false; 
           grid[i][j].bottom = false; 
           grid[i][j].left = false; 
           grid[i][j].right = false; 
           grid[i][j].value = 0;
       }
   } 
}


//Method to display grid. Every grid node takes 6 spaces.
void displayGrid() {
    cout << "#S#";
    for (int j=0; j<width-1; j++) {
        cout << "###";
    }
    cout << "\n";
    for(int i=0; i<height; i++) {
        // Middle bar. Top bar is the same as top rows bottom bar.
        for(int j=0; j<width; j++) {
            string side = "";
            // Left char. Print period if part of path, space if nothing, and # if wall
            if (grid[i][j].left == true && grid[i][j].value == 1 && grid[i][j-1].value == 1)
                side += ".";
            else if (grid[i][j].left == true) 
                side += " ";
            else 
                side += "#";
            // Middle char.
            if (grid[i][j].value == 2)
                side += "D";
            else if (grid[i][j].value == 1)
                side += ".";
            else
                side += " ";
            // Right char.
            if (grid[i][j].right == true && grid[i][j].value == 1 && grid[i][j+1].value == 1)
                side += ".";
            else if (grid[i][j].right == true) 
                side += " ";
            else 
                side += "#";
            cout << side;
        }
        cout << "\n";
        // Bottom bar.
        for (int j=0; j<width; j++) {
            string side = "";
            if (grid[i][j].bottom == true && (grid[i][j].value == 1 || grid[i][j].value == 2) 
                    && grid[i+1][j].value == 1)
                side += "#.#";
            else if (grid[i][j].bottom == true) 
                side += "# #";
            else 
                side += "###";
            cout << side;
        }
        cout << "\n";
    }
}

//Fetches a non visited neighbor of grid node randomly.
int getNonVisitedNeighbor(int row, int col) {
    // 1-top, 2-right, 3-bottom, 4-left
    int neighbors[] = {1, 2, 3, 4};
    //seed for random method in main function.
    random_shuffle(&neighbors[0], &neighbors[4]);
    for(int i=0; i<4; i++) {
        if (neighbors[i] == 1 && row>0 && grid[row-1][col].visited == false) {
            return 1;
        }
        else if (neighbors[i] == 2 && col < width-1 && grid[row][col+1].visited == false) {
            return 2;
        }
        else if (neighbors[i] == 3 && row+1 < height && grid[row+1][col].visited == false) {
            return 3;
        }
        else if (neighbors[i] == 4 && col > 0 && grid[row][col-1].visited == false) {
            return 4;
        }   
    }
    return 0;
}

//Creates a maze using recursive backtracking method.
void createMaze(int row, int col) {
    grid[row][col].visited = true;
    
    // 1-top, 2-right, 3-bottom, 4-left
    while (getNonVisitedNeighbor(row, col) != 0) {
        int direction = getNonVisitedNeighbor(row, col);
        
        if (direction == 1) {
            //Removes wall between nodes.
            grid[row][col].top = true;
            grid[row-1][col].bottom = true;
            createMaze(row-1, col);
        }
        else if (direction == 2) {
            grid[row][col].right = true;
            grid[row][col+1].left = true;
            createMaze(row, col+1);
        }
        else if (direction == 3) {
            grid[row][col].bottom = true;
            grid[row+1][col].top = true;
            createMaze(row+1, col);
        }
        else if (direction == 4) {
            grid[row][col].left = true;
            grid[row][col-1].right = true;
            createMaze(row, col-1);
        }
    }
}

// Solves maze using recursive backtracking.
bool solveMaze(int x, int y) {
    //Base conditions.
    if (grid[x][y].visited == false)
        return false;
    if (destinationX == x && destinationY == y)
        return true;
    //Assume node is part of path.
    grid[x][y].value = 1;
    grid[x][y].visited = false;
    
    //Check in the specified order. Can do this randomly as well.
    if (grid[x][y].top == true && solveMaze(x-1,y) == true) return true;
    if (grid[x][y].right == true && solveMaze(x,y+1) == true) return true;
    if (grid[x][y].bottom && solveMaze(x+1,y) == true) return true;
    if (grid[x][y].left && solveMaze(x,y-1) == true) return true;
    
    //If here, then not part of path. Backtrack and unmark as part of path.
    grid[x][y].value = 0;
    grid[x][y].visited = true;
    return false;
}

//Randomly picks destination.
void pickDestination() {
    destinationX = rand() % width;
    destinationY = rand() % height;    
    grid[destinationX][destinationY].value = 2;
}

int main()
{
    //Method to seed random function.
    srand(time(0));
    initializeGrid();
    createMaze(0,0);
    pickDestination();
    
    //Display unsolved maze.
    cout << "Unsolved Maze (start point is always 0,0):\n";
    displayGrid();
    
    solveMaze(0,0);
    //Display solved maze.
    cout << "\nSolved maze:\n";
    displayGrid();
    return 0;
}
