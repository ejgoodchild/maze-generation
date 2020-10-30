#pragma once
#include "Maze.h"
class MazeGeneration {

	public:
		void generateMaze();

	private:
		int const MIN_MAZE_LENGTH = 5;
		int getMazeWidth();
		int getMazeHeight();
		int getNumberOfEdges();

		Maze* curMaze = NULL;
};