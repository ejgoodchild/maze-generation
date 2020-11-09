/*
* Author: Ethan Goodchild
*/

#include "UserInterface.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;
int main()
{
    srand(time(NULL)); // For randomness effect
    UserInterface ui;
    ui.start();
    return 0;
}

/**
 * Generates, sets up and prints out the maze
 */
void UserInterface::generateMaze()
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

/**
 * Lets user choose whether they would like to save the maze or the 
 * mazes progression
 */
void UserInterface::saveMaze()
{ 
    string msg = "Please type the number for the option you'd like to pick...\n| Save Maze (1) | Save Progression (2)";
    string msgSave = "What would you like to name the file?";
    outputln(msg);

    
    getUserInt(msg, 1, 2) == 1 ? SaveLoad::save(getUserFileName(msgSave),curMazeProg->originalMaze) : 
        SaveLoad::save(getUserFileName(msgSave),curMazeProg->toString());
}

/**
 * Lets the user load a file which contains a maze with/without 
 * progression that has been saved
 */
void UserInterface::loadMaze()
{
    curMaze = NULL;
    while (!curMaze) {
        string msg = "What file would you like to load?";
        curMaze = SaveLoad::load(getUserFileName(msg));
    }  
    curMazeProg = curMaze->getProgression();
    curMaze->printMaze();
    outputln(curMaze->getMazeInfo() + " has been loaded...");
}


/**
 * When no maze has been selected, this menu provides options
 * to either generate maze, load a maze, perform maze analysis
 * or exit the program
 */
void UserInterface::getUserMaze()
{
    if (curMaze) { delete curMaze; }
    string msg = "Please type the number for the option you'd like to pick...\n| Generate Maze (1) | Load Maze (2) | Analyse Mazes (3) | Exit (4)";
    outputln(msg);
    UserOptions userOptions[4]{ UserOptions::GENERATE, UserOptions::LOAD, UserOptions::ANALYSIS, UserOptions::EXIT };
    performUserOption(userOptions[getUserInt(msg, 1, 4) - 1]);

}


/**
 * Loads the main menu which gives the user the option to
 * solve the currently loaded maze, clear any progression
 * save the maze, change the maze, analyse the maze or exit
 * the program
 */
void UserInterface::promptUserOptions()
{
    string msg = "Please type the number for the option you'd like to pick...\n"
        "| Solve Maze (1) | Clear Progression (2) | Save Maze (3) | Change Maze (4) | Analyse Mazes (5) | Exit (6)";
    outputln(msg);
    UserOptions userOptions[6]{ UserOptions::SOLVE, UserOptions::CLEAR, UserOptions::SAVE, UserOptions::CHANGE_MAZE, UserOptions::ANALYSIS , UserOptions::EXIT };
    performUserOption(userOptions[getUserInt(msg, 1, 6) - 1]);
    promptUserOptions();
}

/**
 * Performs user option based on its parameter
 * 
 * param the selected option  
 */
void UserInterface::performUserOption(UserOptions options)
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

/**
 * Asks user what kind of pathfinding they would like to perform
 * and performs it based on their choice
 */
void UserInterface::performPathFinding()
{
    performUserOption(UserOptions::CLEAR);
    string msg = "Please type the number for the option you'd like to pick... \n| Pathfinding For Each Exit (1) | Collaborative Pathfinding (2)";
    outputln(msg);
    UserOptions method = getUserInt(msg, 1, 2) == 1 ? UserOptions::EXITS_PATHFINDING : UserOptions::COLLAB_PATHFINDING;
    performUserOption(method);
}

/**
 * Sets up collaborative path finding by asking the user how many
 * players they want and then calling the collaborative pathfinding
 * method
 */
void UserInterface::performCollabPathfinding()
{
    string msg = "How many players would you like in the game?";
    outputln(msg);
    curMaze->collabPathfinding(getUserInt(msg, 2, curMaze->getNoOfExits()));   

}
/**
 * Asks and returns the upper limit integer value betwen a range of values
 * 
 * @param a string the represent what the upper limit is for, the minimum 
 * value and the maximum value for the upper limit 
 */
int UserInterface::getUserUpperLimit(string msgEnd, int min, int max)
{
    string msg = "Please define the upper limit for the " + msgEnd;
    outputln(msg);
    return getUserInt(msg, min, max);
}

/**
 * Analyses mazes within a range specified by the user and performs a 100
 * tests on each combination of width, height and number of players in a 
 * maze
 */
void UserInterface::analyseMazes()
{
    int width = getUserUpperLimit("maze width...", MIN_MAZE_LENGTH, 250);
    int height = getUserUpperLimit("maze height...", MIN_MAZE_LENGTH, 250);
    int players = getUserUpperLimit("number of players...", 2, (MIN_MAZE_LENGTH - 2) * 4);
    
    for (int x = MIN_MAZE_LENGTH; x <= width; x++)
        for (int y = MIN_MAZE_LENGTH; y <= height; y++)
            for (int p = 2; p <= players; p++)
                analyseMazes(x, y, p);

}
/**
 * Analyses 100 mazes with width, height and number of players defined
 * by the user
 * 
 * @param the width, height and number of player of the maze
 */
void UserInterface::analyseMazes(int width, int height, int players)
{
    MazeAnalysis ma =  MazeAnalysis(width, height, players);
    for (int i = 0; i < 100; i++) {
        generateMaze(width, height, players);
        curMaze->collabPathfinding(players);
        ma.solvable += curMazeProg->outcome == Outcome::SOLVABLE ? 1: 0;
        ma.partial += curMazeProg->outcome == Outcome::PARTIAL ? 1 : 0;
        ma.unsolvable += curMazeProg->outcome == Outcome::UNSOLVABLE ? 1 : 0;
    }

    cout << ma.toString() ;
}
/**
 * Generates a new maze based on the width, height and number 
 * of players specified.
 *
 * @param the width, height and number of players in maze
 */
void UserInterface::generateMaze(int width, int height, int players)
{
    if (curMaze) delete curMaze;
   
    curMaze = new Maze(width, height);
    curMaze->setExits(randInt(players, curMaze->getMaxNumOfExits()));
    curMaze->generateMaze();
    curMazeProg = curMaze->getProgression();
}


/**
 * Starts the user interface
 */
void UserInterface::start()
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
int UserInterface::getMazeWidth()
{
    string msg = "Enter the width of the maze...";
    outputln(msg);
    return getUserInt(msg, MIN_MAZE_LENGTH, 250);

}

/**
 * Asks the user the height they want the maze
 * If height too small, then the user is asked to type in another height
 * 
 * @return the height of the maze
 */
int UserInterface::getMazeHeight()
{
    string msg = "Enter the height of the maze...";
    outputln(msg);
    return getUserInt(msg, MIN_MAZE_LENGTH, 250);
}

/**
 * Asks user how many edges they want in the maze
 * If not within the range, then the user is asked to type in another amount
 * 
 * @return the amount of edges the user has requested
 */
int UserInterface::getNumberOfExits()
{
    string msg = "Enter the number of edges in the maze...";
    outputln(msg);
    return getUserInt(msg, 2, curMaze->getMaxNumOfExits());
   
}


