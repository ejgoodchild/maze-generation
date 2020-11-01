#pragma once
#include "Maze.h"
 class SaveLoad
{
	public:
		void save(Maze*);
		Maze* load();

	private:
	

		string getFileNameSave();
		 string getFileNameLoad();
		string checkExtension(string*);
};

