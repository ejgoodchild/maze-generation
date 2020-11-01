#pragma once
#include "Maze.h"
#include "SaveLoad.h"
enum class UserOptions {GENERATE = 1, LOAD = 2, SAVE = 3};
class MazeGeneration {

	public:
		
		void start();

	private:
		int const MIN_MAZE_LENGTH = 5;
		int getMazeWidth();
		int getMazeHeight();
		int getNumberOfExits();

		Maze* curMaze = NULL;

		void generateMaze();
		void saveMaze();
		UserOptions getUserSelection();
		
};