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
void SaveLoad::save(string data)
{
    ofstream myfile(getFileNameSave());
    if (myfile.is_open())
    {
        myfile << data;
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
Maze* SaveLoad::load()
{
    string line;
    ifstream myfile(getFileNameLoad());
    string mazeData, tempData;
    std::vector<string> progressData;
    Maze* maze = NULL;

    bool foundMaze = false;
    int x = 0, y = 0;
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            
            if (y == 0) { x = line.length(); mazeData += line;
            }
            
            if (y > 0 && !foundMaze) {
                if(line.length() != x) { 
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
                else if(tempData.length() > 0) {
                    progressData.emplace_back(tempData);
                    tempData.clear();
                }
            }else{
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

/**
 * Gets what the user wants to save the file name as
 * 
 * @return the name of the file to save
 */
string SaveLoad::getFileNameSave()
{
    cout << "What would you like to name the file?" << endl;
    string fname;
    cin >> fname;
    return checkExtension(&fname); //Make sure name is valid
}


/**
 * Gets what file the user wants to open
 * 
 * @return the name of file to load
 */
string SaveLoad::getFileNameLoad()
{
    cout << "What file would you like to open?" << endl;
    string fname;
    cin >> fname;
    return checkExtension(&fname);//Make sure name is valid
}

/**
 * Checks to see if a .txt extension has been specified
 * if not then adds the extension
 * 
 * @param string to check for extension
 * @return string to return with extension
 */
string SaveLoad::checkExtension(string* str)
{
    int size = str->length();
    bool ext = str->substr(size - 4, size) == ".txt";
    return *str + (ext ? "" : ".txt");
}
