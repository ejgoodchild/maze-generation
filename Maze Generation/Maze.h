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
		int getMaxNumOfExits();
		void setExits(int exits) {
			this->exits = exits;
		};
		void printMaze();
		string toString();
		void generateMaze();


	private:
		int width, height;
		int exits = 1;
		int getNodesPos(int x, int y){
			return x + (y * width);
		}	

		std::vector <MazeNode> nodes;
		
		
		void generateNodes();
		void generatePaths() {
			MazeNode* start = getStartNode();
			int x = (width % 2 == 1) ? (((width-1)/2) % 2 == 0 ? start->x + 1 : start->x): start->x;
			int y = (height % 2 == 1) ? (((height - 1) / 2) % 2 == 0 ? start->y + 1 : start->y) : start->y;
			generatePaths(&nodes.at(getNodesPos(x,y)));
		};
		void generatePaths(MazeNode* node);

		void generateStartPoint();
		void generateWalls();
		void generateExits();

		MazeNode* getStartNode(){
			return &nodes.at(getNodesPos((width - 1) / 2, (height - 1) / 2));
		}

		std::vector <MazeNode*> getPossibleExits();
		

		MazeNode* getPathEndNode(MazeNode*, Directions);
		void fillPathNodes(MazeNode*, MazeNode*);

};

