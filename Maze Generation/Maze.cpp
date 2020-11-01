#include "Maze.h"
#include <algorithm>
#include <random>
#include <chrono>       // std::chrono::system_clock
#include <array>        // std::array




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
	int len =  2;

	x += dir == Directions::EAST ? (curNode->x + len >= width - 1 ? 0 : len) : 0; // if direction is EAST and in range then x = len
	x += dir == Directions::WEST ? (curNode->x - len <= 0 ? 0 : -len) : 0; // if direction is WEST and in range then x = -len
	y += dir == Directions::NORTH ? (curNode->y - len <= 0 ? 0 : -len) : 0; // if direction is NORTH and in range then y = -len
	y += dir == Directions::SOUTH ? (curNode->y + len >= height - 1 ? 0 : len) : 0; // if direction is SOUTH and in range then y = len

	bool isXIncrementable = width % 2 == 0 ? (dir == Directions::EAST || dir == Directions::WEST) : false;
	bool isYIncrementable = height % 2 == 0 ? (dir == Directions::NORTH || dir == Directions::SOUTH) : false;
	//if x is incrementable then decrement if x is on left side of maze and if x is even otherwise if on right side then increment x if odd
	x += isXIncrementable ? (curNode->x < width / 2 ? (curNode->x % 2 == 0 ? -1 : 0) : (curNode->x % 2 == 1 ? 1 : 0)) : 0;
	//if y is incrementable then decrement if y is on top side of maze and if y is even otherwise if on bottom side then increment y if odd
	y += isYIncrementable ? (curNode->y < height / 2 ? (curNode->y % 2 == 0 ? -1 : 0) : (curNode->y % 2 == 1 ? 1 : 0)) : 0; 

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




