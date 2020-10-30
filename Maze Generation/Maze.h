#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct MazeNode {
	int x, y;
	char nodeType = NULL;
	float g, h;
	bool passable;
};
class Maze
{
	public:
		Maze(int, int);
		void printMazeSize();
		int getMaxNumOfEdges();
		void setEdges(int edges) {
			this->edges = edges;
		};
		void printMaze();
		void generateMaze();


	private:
		int width, height;
		int edges = 1;
		std::vector <MazeNode> nodes;

};

