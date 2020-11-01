#pragma once
#include "Maze.h"
class SaveLoad
{
	public:
		void save(Maze*);

	private:
		string getFileName();
};

