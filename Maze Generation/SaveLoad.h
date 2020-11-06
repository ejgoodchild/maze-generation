#pragma once
#include "Maze.h"
 class SaveLoad
{
	public:
		static void save(string);
		static Maze* load();

	private:
	
		static string getFileNameSave();
		 static string getFileNameLoad();
		static string checkExtension(string*);
};

