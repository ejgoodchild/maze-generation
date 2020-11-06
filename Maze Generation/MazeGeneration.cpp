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
    int width = getMazeWidth();
    int height = getMazeHeight();
    curMaze = new Maze(width, height);
    curMaze->setExits(getNumberOfExits());
    curMaze->printMazeSize();
    curMaze->generateMaze();
    curMazeProg = curMaze->getProgression();
    curMaze->printMaze();
    

}

void MazeGeneration::saveMaze()
{
    SaveLoad saveload;

    
        cout << "Please type the number for the option you'd like to pick..." << endl;
        cout << "| Save Maze (1) | Save Progression (2)" << endl;
        int option;
        cin >> option;
        option == 1 ? saveload.save(curMaze->toString()) : saveload.save(curMazeProg->toString());
        
}

void MazeGeneration::loadMaze()
{
    
    SaveLoad saveload;
    curMaze = saveload.load();
    curMazeProg = curMaze->getProgression();
    curMaze->printMaze();
}



void MazeGeneration::getUserMaze()
{
    if (curMaze) {
        delete curMaze;
    }
    cout << "Please type the number for the option you'd like to pick..." << endl;
    cout << "| Generate Maze (1) | Load Maze (2) | Analyse Mazes (3) | Exit (4)" << endl;
    int option;
    cin >> option;
    UserOptions userOptions[4]{ UserOptions::GENERATE, UserOptions::LOAD, UserOptions::ANALYSIS, UserOptions::EXIT };

    option <= sizeof(userOptions) / sizeof(userOptions[0]) ? performUserOption(userOptions[option - 1]) : getUserMaze();

}



void MazeGeneration::promptUserOptions()
{
    cout << "Please type the number for the option you'd like to pick..." << endl;
    cout << "| Solve Maze (1) | Clear Progression (2) | Save Maze (3) | Change Maze (4) | Analyse Mazes (5) | Exit (6)" << endl;
    
    UserOptions userOptions[6]{ UserOptions::SOLVE, UserOptions::CLEAR, UserOptions::SAVE, UserOptions::CHANGE_MAZE, UserOptions::ANALYSIS , UserOptions::EXIT };

    int option;
    cin >> option;

    option <= sizeof(userOptions) / sizeof(userOptions[0]) ? performUserOption(userOptions[option-1]) : promptUserOptions();

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
            performPathFinding();
            break;
        case UserOptions::CLEAR:
            curMaze->clearSolutions();
            curMazeProg->progress.clear();
            break;
        case UserOptions::COLLAB_PATHFINDING:
            performCollabPathfinding();
            cout << curMazeProg->toString();
            break;
        case UserOptions::EXITS_PATHFINDING:
            curMaze->getBestExitPaths();
            break;
        case UserOptions::ANALYSIS:
            analyseMazes();
            break;
    
    }
}

void MazeGeneration::performPathFinding()
{
    performUserOption(UserOptions::CLEAR);
    cout << "Please type the number for the option you'd like to pick..." << endl;
    cout << "| Pathfinding For Each Exit (1) | Collaborative Pathfinding (2)" << endl;
    int option;
    cin >> option;
    UserOptions method = option == 1 ? UserOptions::EXITS_PATHFINDING : UserOptions::COLLAB_PATHFINDING;
    performUserOption(method);



}

void MazeGeneration::performCollabPathfinding()
{
    cout << "How many players would you like in the game?" << endl << "Must be between the range of 2 and " << curMaze->getNoOfExits() << endl;

    int numOfPlayers;
    cin >> numOfPlayers;
    numOfPlayers > 2 && numOfPlayers <= curMaze->getNoOfExits() ? curMaze->collabPathfinding(numOfPlayers) : performCollabPathfinding();



}

void MazeGeneration::analyseMazes()
{
    int players, width, height;
    cout << "Please define the upper limit for the maze height..." << endl;
    cin >> height;
    cout << "Please define the upper limit for the maze width..." << endl;
    cin >> width;
    cout << "Please define the upper limit for the number of players..." << endl;
    cin >> players;

    for (int x = MIN_MAZE_LENGTH; x <= width; x++) {
        for (int y = MIN_MAZE_LENGTH; y <= height; y++) {
            for (int p = 2; p <= players; p++) {
                analyseMazes(x, y, p);

            }
        }
    }

}

void MazeGeneration::analyseMazes(int width, int height, int players)
{
    MazeAnalysis ma =  MazeAnalysis(width, height, players);
    for (int i = 0; i < 100; i++) {
        generateMaze(width, height, players);
        curMaze->collabPathfinding(players);
        ma.solvable += curMazeProg->outcome == Outcome::SOLVABLE ? 1: 0;
        ma.partial += curMazeProg->outcome == Outcome::PARTIAL ? 1 : 0;
        ma.unsolvable += curMazeProg->outcome == Outcome::UNSOLVABLE ? 1 : 0;

    }
    cout << ma.toString();
}

void MazeGeneration::generateMaze(int width, int height, int players)
{
    if (curMaze) {
        delete curMaze;
    }
    curMaze = new Maze(width, height);
    

    curMaze->setExits(randInt(players, curMaze->getMaxNumOfExits()/2));
    curMaze->generateMaze();
    curMazeProg = curMaze->getProgression();



}


void MazeGeneration::start()
{
    getUserMaze();
    promptUserOptions();
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


