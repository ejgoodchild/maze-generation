#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct MazeNode {
	int x, y;
	char nodeType = NULL;
	float g, h;
	bool passable = true;
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
		int getNodesPos(int x, int y){
			return x + (y * width);
		}
		std::vector <MazeNode> nodes;
		void generateNodes();
		void generateStartPoint();

};

