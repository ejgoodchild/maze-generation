#include "Maze.h"
#include <algorithm>




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
	generatePaths();
	generateStartPoint();
	generateWalls();
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
	MazeNode* startPoint = getStartNode();
	MazeNode* mNode;
	for (int y = startPoint->y - 1; y <= startPoint->y + 1; y++) {
		for (int x = startPoint->x - 1; x <= startPoint->x + 1; x++) {
			mNode = &nodes.at(getNodesPos(x, y));
			mNode->nodeType = mNode == startPoint ? 'S' : ' ';
		

		}
	}

	


}

void Maze::generateWalls()
{
	MazeNode* mNode;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			mNode = &nodes.at(getNodesPos(x, y));
			if(mNode->nodeType == NULL){
				mNode->nodeType = 'X';
				mNode->passable = false;
			}

			
			
		}
	}
}
void Maze::generatePaths(MazeNode* curNode)
{
	Directions dir[]{ Directions::NORTH, Directions::EAST, Directions::SOUTH, Directions::WEST };
	MazeNode* endNode = NULL;

	std::random_shuffle(std::begin(dir), std::end(dir));
	for (int i = 0; i < 4; i++) {
		endNode = getPathEndNode(curNode, dir[i]);
		if (endNode != NULL) {
			//endNode->print();
			fillPathNodes(curNode, endNode);
			generatePaths(endNode);
		}				
	}
}


MazeNode* Maze::getPathEndNode(MazeNode* curNode, Directions dir)
{
	int x = 0, y = 0;
	
	switch (dir) {
	case Directions::NORTH:
		y = curNode->y - 2 <= 0 ? 0 : -2;
		break;
	case Directions::EAST:
		x = curNode->x + 2 >= width - 1 ? 0 : 2;
		break;

	case Directions::SOUTH:
		y = curNode->y + 2 >= height - 1 ? 0 : 2;
		break;

	case Directions::WEST:
		x = curNode->x - 2 <= 0 ? 0 : -2;
		break;

	}

	MazeNode* endNode = &nodes.at(getNodesPos(curNode->x + x, curNode->y + y));
	endNode = endNode->nodeType ? NULL : endNode;

	return curNode == endNode ? NULL : endNode ;
}

void Maze::fillPathNodes(MazeNode* curNode, MazeNode* nextNode)
{

	for (int x = curNode->x; x != nextNode->x; x += curNode->x > nextNode->x ? -1 : 1) {
		
		nodes.at(getNodesPos(x, curNode->y)).nodeType = ' ';

	}
	for (int y = curNode->y; y != nextNode->y; y += curNode->y > nextNode->y ? -1 : 1) {

		nodes.at(getNodesPos(curNode->x, y)).nodeType = ' ';
	}
	
}




