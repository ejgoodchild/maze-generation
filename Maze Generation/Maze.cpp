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
			cout << nodes.at(getNodesPos(x,y)).nodeType;
		}
		cout << endl;
	}
	cout << endl;

}

void Maze::generateMaze()
{
	generateNodes();
	generateStartPoint();
}

void Maze::generateNodes()
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

void Maze::generateStartPoint()
{
	
	
	int ch = (height - 1) / 2;
	int cw = (width - 1) / 2;
	
	MazeNode* mNode;
	for (int y = ch - 1; y < ch+ 1; y++) {
		for (int x = cw - 1; x < cw + 1; x++) {
			mNode = &nodes.at(getNodesPos(x, y));
			mNode->nodeType = (y == ch && x == cw) ? 'S' : ' ';
		

		}
	}

	


}




