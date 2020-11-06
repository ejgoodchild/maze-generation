#pragma once
#include "Maze.h"
#include "SaveLoad.h"
enum class UserOptions {GENERATE = 1, LOAD = 2, SAVE = 3, EXIT = 4, SOLVE = 5, CLEAR = 6, CHANGE_MAZE = 7,
EXITS_PATHFINDING = 8, COLLAB_PATHFINDING = 9, ANALYSIS = 10};
struct MazeAnalysis {
	MazeAnalysis(int width, int height, int players) {
		this->width = width;
		this->height = height;
		this->players = players;
	}
	int players;
	int width, height;
	int tests = 0;
	int solvable = 0;
	int partial = 0; 
	int unsolvable = 0;
	string toString() {
		return "Maze [" + std::to_string(width) + "," + std::to_string(height) + 
			"][p = "+ std::to_string(players) +"]: solvable = "
			+ std::to_string(solvable) +", partial = " + std::to_string(partial) + 
			", unsolvable = " + std::to_string(unsolvable) + "\n" ;
	}
};

class UserInterface : protected MazeGeneration {

	public:
		
		void start();

	private:
		int const MIN_MAZE_LENGTH = 10;
		int getMazeWidth();
		int getMazeHeight();
		int getNumberOfExits();

		Maze* curMaze = NULL;
		MazeProgression* curMazeProg = NULL;
		std::vector<MazeAnalysis> analysisData;

		void generateMaze();
		void saveMaze();
		void loadMaze();
		void getUserMaze();
		void promptUserOptions();
		void performUserOption(UserOptions options);
		void performPathFinding();
		void performCollabPathfinding();
		void analyseMazes();
		void analyseMazes(int width, int height, int players);
		void generateMaze(int width, int height, int players);
		int randInt(int min, int max) {
			return min + (rand() % (max - min + 1));
		}
		int getUserUpperLimit(string, int, int);
		
};