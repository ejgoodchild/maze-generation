#pragma once
#include "Maze.h"
 class SaveLoad
{
	public:
		void save(string);
		Maze* load();

	private:
	

		string getFileNameSave();
		 string getFileNameLoad();
		string checkExtension(string*);
};

