#include "SaveLoad.h"
#include <iostream>
#include <fstream>
using namespace std;

void SaveLoad::save(Maze* maze)
{


    ofstream myfile(getFileName());
    if (myfile.is_open())
    {
        myfile << maze->toString();
        myfile.close();
        cout << "Save successful!" << endl;
    }
    else cout << "Unable to open file" << endl;

}

string SaveLoad::getFileName()
{
    cout << "What would you like to name the file?" << endl;
    string fname;
    cin >> fname;
    
    int size = fname.length();
    bool ext = fname.substr(size - 4, size) == ".txt";
    return fname + (ext ? "" : ".txt");
}
