#pragma once
#include "Maze.h"
 class SaveLoad : MazeGeneration
{
	public:
		static void save(string, string);
		static Maze* load(string);


};

