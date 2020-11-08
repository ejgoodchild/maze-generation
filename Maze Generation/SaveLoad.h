#pragma once
#include "Maze.h"
 class SaveLoad : MazeGeneration
{
	public:
		static void save(string, string);
		static Maze* load(string);
	private:
		static void updateMazeData(string ln, int* x, int* y, bool* foundMaze, string* mazeData);
		static void updateTempData(string ln, int* x, string* tempData, vector<string>* progData);
		static void updateProgData(string* tempData, vector<string>* progData);
		static Maze* load(ifstream* file);
		static bool validateLine(string ln, bool* foundMaze);
		static bool isMazeChar(char* c);
};

