#include "SaveLoad.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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
           // foundMaze ? updateProgress() : updateMaze();
            /*mazeData += line;
                cout << line << endl;
                x = line.length();
                y++;
         */
           

        }
        myfile.close();
        
        maze = foundMaze ? new Maze(x, y, mazeData, progressData) : new Maze(x, y, mazeData);;
        cout << "Maze sucessfully loaded" << endl;

    }

    else cout << "Unable to open file";
    
    return maze;
}


string SaveLoad::getFileNameSave()
{
    cout << "What would you like to name the file?" << endl;
    string fname;
    cin >> fname;
    return checkExtension(&fname);
}

string SaveLoad::getFileNameLoad()
{
    cout << "What file would you like to open?" << endl;
    string fname;
    cin >> fname;
    return checkExtension(&fname);
}

string SaveLoad::checkExtension(string* str)
{
    int size = str->length();
    bool ext = str->substr(size - 4, size) == ".txt";
    return *str + (ext ? "" : ".txt");
}
