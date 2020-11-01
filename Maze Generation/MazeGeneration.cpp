#include "MazeGeneration.h"
#include <iostream>
#include <time.h>

using namespace std;
int main()
{
    srand(time(NULL)); // For randomness effect
    MazeGeneration mazeGen;
    mazeGen.start();
}

/**
 * Generates, sets up and prints out the maze
 */
void MazeGeneration::generateMaze()
{
    curMaze = new Maze(getMazeWidth(), getMazeHeight());
    curMaze->setExits(getNumberOfExits());
    curMaze->printMazeSize();
    curMaze->generateMaze();
    curMaze->printMaze();
    

}

void MazeGeneration::saveMaze()
{
    SaveLoad saveload;
    saveload.save(curMaze);
}

void MazeGeneration::loadMaze()
{
    if (curMaze) {
        delete curMaze;
    }
    SaveLoad saveload;
    curMaze = saveload.load();
    curMaze->printMaze();
}

UserOptions MazeGeneration::getUserSelection()
{
    cout << "Please type the number for the option you'd like to pick..." << endl;
    cout << "| Generate Maze (1) | Load Maze (2) |" << endl;
    int option;
    cin >> option;
    
    return option == 1 ?  UserOptions::GENERATE : (option == 2 ? UserOptions::LOAD : getUserSelection()) ;
}

void MazeGeneration::start()
{
    UserOptions mode = getUserSelection();
    mode == UserOptions::GENERATE ? generateMaze() : (mode == UserOptions::LOAD ?  loadMaze(): (void)(cout << "No option selected" << endl));

    saveMaze();
    cout << endl << endl;
    start();
}

/**
 * Asks the user the width they want the maze
 * If width too small, then the user is asked to type in another width
 *
 * @return the width of the maze
 */
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

/**
 * Asks the user the height they want the maze
 * If height too small, then the user is asked to type in another height
 * 
 * @return the height of the maze
 */
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

/**
 * Asks user how many edges they want in the maze
 * If not within the range, then the user is asked to type in another amount
 * 
 * @return the amount of edges the user has requested
 */
int MazeGeneration::getNumberOfExits()
{
    int edges;
    cout << "Enter the number of edges in the maze" << endl;
    cin >> edges;
    if (edges > 1 && edges <= curMaze->getMaxNumOfExits()) {
        return edges;
    }
    cout << "The number of edges is outside the range, the number of edges must be between 1 and " << curMaze->getMaxNumOfExits() << endl;

    return getNumberOfExits();
}


