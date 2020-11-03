#pragma once
#include "Maze.h"
#include "SaveLoad.h"
enum class UserOptions {GENERATE = 1, LOAD = 2, SAVE = 3, EXIT = 4, SOLVE = 5, CLEAR = 6, CHANGE_MAZE = 7,
EXITS_PATHFINDING = 8, COLLAB_PATHFINDING = 9};
class MazeGeneration {

	public:
		
		void start();

	private:
		int const MIN_MAZE_LENGTH = 5;
		int getMazeWidth();
		int getMazeHeight();
		int getNumberOfExits();

		Maze* curMaze = NULL;
		MazeProgression* curMazeProg = NULL;

		void generateMaze();
		void saveMaze();
		void loadMaze();
		void getUserMaze();
		void promptUserOptions();
		void performUserOption(UserOptions options);
		void performPathFinding();
};