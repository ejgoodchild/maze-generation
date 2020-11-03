#include "MazeGeneration.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;
int main()
{
    srand(time(NULL)); // For randomness effect
    MazeGeneration mazeGen;
    mazeGen.start();
    return 0;
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
    
    SaveLoad saveload;
    curMaze = saveload.load();

    curMaze->printMaze();
}



void MazeGeneration::getUserMaze()
{
    if (curMaze) {
        delete curMaze;
    }
    cout << "Please type the number for the option you'd like to pick..." << endl;
    cout << "| Generate Maze (1) | Load Maze (2) | Exit (3)" << endl;
    int option;
    cin >> option;

    UserOptions mode = option == 1 ? UserOptions::GENERATE : (option == 2 ? UserOptions::LOAD : UserOptions::EXIT);
    performUserOption(mode);

}



void MazeGeneration::promptUserOptions()
{
    cout << "Please type the number for the option you'd like to pick..." << endl;
    cout << "| Solve Maze (1) | Clear Any Solutions (2) | Save Maze (3) | Change Maze (4) | Exit (5)" << endl;
    
    UserOptions userOptions[5]{ UserOptions::SOLVE, UserOptions::CLEAR, UserOptions::SAVE, UserOptions::CHANGE_MAZE, UserOptions::EXIT };

    int option;
    cin >> option;

    option < sizeof(userOptions) / sizeof(userOptions[0]) ? performUserOption(userOptions[option-1]) : promptUserOptions();

    promptUserOptions();



}

void MazeGeneration::performUserOption(UserOptions options)
{
    switch (options) {
        case UserOptions::EXIT:
            exit(0);
            break;
        case UserOptions::GENERATE:
            generateMaze();
            break;
        case UserOptions::LOAD:
            loadMaze();
            break;
        case UserOptions::SAVE:
            saveMaze();
            break;
        case UserOptions::CHANGE_MAZE:
            getUserMaze();
            break;
        case UserOptions::SOLVE:
            curMaze->clearSolutions();
            curMaze->getBestExitPaths();
            break;
        case UserOptions::CLEAR:
            curMaze->clearSolutions();
            curMaze->printMaze();
            break;
    
    }
}


void MazeGeneration::start()
{
    getUserMaze();
    promptUserOptions();

   


    cout << endl << endl;
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


