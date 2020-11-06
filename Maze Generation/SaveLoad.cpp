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
    string line;
    ifstream myfile(filename);
    string mazeData, tempData;
    std::vector<string> progressData;
    Maze* maze = NULL;

    bool foundMaze = false;
    int x = 0, y = 0;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {

            if (y == 0) {
                x = line.length(); mazeData += line;
            }

            if (y > 0 && !foundMaze) {
                if (line.length() != x) {
                    foundMaze = true;
                }
                else {
                    mazeData += line;
                }

            }

            if (foundMaze) {
                if (line.length() == x) {
                    tempData += line + "\n";
                }
                else if (tempData.length() > 0) {
                    progressData.emplace_back(tempData);
                    tempData.clear();
                }
            }
            else {
                y++;
            }


        }
        myfile.close();

        maze = foundMaze ? new Maze(x, y, mazeData, progressData) : new Maze(x, y, mazeData);;
        cout << "Maze sucessfully loaded" << endl;

    }

    else cout << "Unable to open file";

    return maze;
}
