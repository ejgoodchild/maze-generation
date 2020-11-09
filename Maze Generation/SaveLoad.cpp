/*
* Author: Ethan Goodchild
*/
#include "SaveLoad.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/**
 * Saves a string to a text file
 *
 * @param the string to save
 */

void SaveLoad::save(string filename, string msg)
{
    ofstream myfile(filename);
    if (myfile.is_open())
    {
        myfile << msg;
        myfile.close();
        cout << "Save successful!" << endl;
    }
    else cout << "Unable to open file" << endl;
}

/**
 * Loads a Maze and if any progression that is loaded too
 *
 * @param the name of the file to load
 * @return Maze* of the maze being loaded
 */
Maze* SaveLoad::load(string filename)
{
    ifstream myfile(filename);
    Maze* maze = NULL;

    if (myfile.is_open())
    {
        maze = load(&myfile);
        myfile.close();
        return maze;
    }

    cout << "Unable to open file, please try again...\n" ;
    return maze;
}
/**
 * Helps the load function work out what data is from the maze and not from the progress saved
 * 
 * @param the line being read, references to the width, the current line, bool to determine
 * if maze is found and the data of the maze
 */
void SaveLoad::updateMazeData(string ln, int* x, int* y, bool* foundMaze, string* mazeData)
{
    if (*y == 0) { *x = ln.length(); }; //if on first row, set the value of x to the line length
    *foundMaze = ln.length() != *x; //maze has finished being found when line length is not equal to the width of the maze
    if (*foundMaze) { return; } //if maze is finished return
    (*y)++; 
    *mazeData += ln; //add line to the maze data
}
/**
 * Helps the load function work out how to split the maze progress data so that it can be 
 * used and printed correctly
 * if line length is not equal to the width of maze then update the progress data otherwise
 * add to the temp data
 *
 * @param the line being read, references to the width, the temp data and progress data
 */
void SaveLoad::updateTempData(string ln, int* x, string* tempData, vector<string>* progData)
{
    ln.length() == *x ? (void)(*tempData += ln + '\n') : updateProgData(tempData, progData);
}
/**
 * Updates the maze progression data
 *
 * @param the line being read, references to the width, the temp data and progress data
 */
void SaveLoad::updateProgData(string* tempData, vector<string>* progData)
{
    if (tempData->size() <= 0)  return;  //if no temp data then there is no need to progress
    progData->emplace_back(*tempData); //add temp data to the progression data
    tempData->clear(); //clear temp data
}


/**
 * Loads a Maze and if any progression that is loaded too
 *
 * @param the file to read
 * @return Maze* of the maze being loaded
 */
Maze* SaveLoad::load(ifstream* file)
{
    string line;
    string mazeData, tempData;
    vector<string> progressData;
    bool foundMaze = false, isValid = true;
    int x = 0, y = 0;

    while (getline(*file, line))
    {
        foundMaze ? updateTempData(line, &x, &tempData, &progressData) : 
            updateMazeData(line, &x, &y, &foundMaze, &mazeData), isValid = validateLine(line, &foundMaze); //if maze data found then find progression data
        if (!isValid) {
            cout << "File does not contain Maze Data Structure..." << endl; return NULL;
        }
    }
    cout << "Maze sucessfully loaded" << endl;
    return foundMaze ? new Maze(x, y, mazeData, progressData) : new Maze(x, y, mazeData);
}
/**
 * Validates whether a line of text is part of a maze structure
 *
 * @param the line of text and if the maze has already been found
 * in textfile
 * @return if line is valid true otherwise false
 */
bool SaveLoad::validateLine(string ln, bool* foundMaze)
{
    for (int i = 0; i < ln.length(); i++)
        if (!isMazeChar(&ln.at(i))) return *foundMaze;
    return true;
}
/**
 * Checks to see if character is one that can appear on a maze
 *
 * @param character to check
 * @returnif character is valid
 */
bool SaveLoad::isMazeChar(char* c)
{
    char mazeChars[7]{ 'E',' ', 'S', 'X', 'P', 'o', 'F' };
    
    for(int i = 0; i < 7; i++) 
        if (*c == mazeChars[i]) return true;

    return false;
}


