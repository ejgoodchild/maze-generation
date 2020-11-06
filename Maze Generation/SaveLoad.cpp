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

    cout << "Unable to open file";
    return maze;
}

void SaveLoad::updateMazeData(string ln, int* x, int* y, bool* foundMaze, string* mazeData)
{
    if (*y == 0) { *x = ln.length(); };
    *foundMaze = ln.length() != *x;
    if (*foundMaze) { return; }
    (*y)++;
    *mazeData += ln;
}

void SaveLoad::updateTempData(string ln, int* x, string* tempData, vector<string>* progData)
{
    ln.length() == *x ? (void)(*tempData += ln + '\n') : updateProgData(tempData, progData);
}

void SaveLoad::updateProgData(string* tempData, vector<string>* progData)
{
    if (tempData->size() <= 0) { return; }
    progData->emplace_back(*tempData);
    tempData->clear();
}

Maze* SaveLoad::load(ifstream* file)
{
    string line;
    string mazeData, tempData;
    vector<string> progressData;
    bool foundMaze = false;
    int x = 0, y = 0;

    while (getline(*file, line))
    {
        foundMaze ? updateTempData(line, &x, &tempData, &progressData) : updateMazeData(line, &x, &y, &foundMaze, &mazeData);
    }
    cout << "Maze sucessfully loaded" << endl;
    return foundMaze ? new Maze(x, y, mazeData, progressData) : new Maze(x, y, mazeData);
}


