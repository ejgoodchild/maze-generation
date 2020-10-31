#pragma once
#include <iostream>
#include <vector>

using namespace std;
enum class Directions {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
struct MazeNode {
	int x, y;
	char nodeType = NULL;
	float g, h;
	bool passable = true;
	void print() { cout << "[" <<x <<"," << y << "]"; };
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
		void generatePaths() {
			generatePaths(getStartNode());
		};
		void generatePaths(MazeNode* node);


		void generateStartPoint();
		void generateWalls();

		MazeNode* getStartNode(){
			return &nodes.at(getNodesPos((width - 1) / 2, (height - 1) / 2));
		}


		

		MazeNode* getPathEndNode(MazeNode*, Directions);
		void fillPathNodes(MazeNode*, MazeNode*);

};

