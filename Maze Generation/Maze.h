#pragma once
#include <iostream>

using namespace std;
class Maze
{
	public:
		Maze(int, int );
		void printMazeSize();
		int getMaxNumOfEdges();
		void setEdges(int edges) {
			this->edges = edges;
		};

	private:
		int width, height;
		int edges = 1;
};

