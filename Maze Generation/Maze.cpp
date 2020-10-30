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




