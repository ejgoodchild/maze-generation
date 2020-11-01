#include "MazeGeneration.h"
#include <iostream>
#include <time.h>

using namespace std;
int main()
{
    srand(time(NULL));

    MazeGeneration mazeGen;
    mazeGen.generateMaze();
}

void MazeGeneration::generateMaze()
{
    curMaze = new Maze(getMazeWidth(), getMazeHeight());
    curMaze->setEdges(getNumberOfEdges());
    curMaze->printMazeSize();
    curMaze->generateMaze();
    curMaze->printMaze();
    
   

}

int MazeGeneration::getMazeWidth()
{
    int width;
    cout << "Enter the width of the maze..." << endl;
    cin >> width;

    
    if (width < MIN_MAZE_LENGTH) {
        cout << "The width is too small, it must be at least a size of " << MIN_MAZE_LENGTH << endl;
        return getMazeWidth();
    }
    return width;
}

int MazeGeneration::getMazeHeight()
{
    int height;
    cout << "Enter the height of the maze..." << endl;
    cin >> height;


    if (height < MIN_MAZE_LENGTH) {
        cout << "The height is too small, it must be at least a size of " << MIN_MAZE_LENGTH << endl;
        return getMazeHeight();
    }
    return height;
}

int MazeGeneration::getNumberOfEdges()
{
    int edges;
    cout << "Enter the number of edges in the maze" << endl;
    cin >> edges;
    if (edges > 1 && edges <= curMaze->getMaxNumOfEdges()) {
        return edges;
    }
    cout << "The number of edges is outside the range, the number of edges must be between 1 and " << curMaze->getMaxNumOfEdges() << endl;

    return getNumberOfEdges();
}


