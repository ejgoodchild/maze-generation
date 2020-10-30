#include "Maze.h"

Maze::Maze(int w, int h)
{
	width = w;
	height = h;
	
}

void Maze::printMazeSize()
{
	cout << "The maze is a size of " << width << "x" << height << endl;
}

int Maze::getMaxNumOfEdges()
{
	return (width-2)*2 + (height-2)*2;
}

void Maze::printMaze()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cout << nodes.at(x + (y * width)).nodeType;
		}
		cout << endl;
	}
	cout << endl;

}

void Maze::generateMaze()
{
	MazeNode* mNode;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			mNode = new MazeNode();
			mNode->x = x;
			mNode->y = y;
			nodes.emplace_back(*mNode);
		}
	}
}




