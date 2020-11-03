#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
enum class Directions {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
struct MazeNode {
	int x, y;
	char nodeType = NULL;
	float g, h;
	bool passable = true;
	void print() { cout << "[" <<x <<"," << y << "]"; };
	bool closed = false;
	MazeNode* bestParent = NULL;
};
struct MazeProgression {
	string originalMaze;
	std::vector<string> progress;
	string toString() {
		string str = originalMaze + "\n\n";
		for (int i = 0; i < progress.size(); i++) {
			str += "Step " + std::to_string(i+1) + "\n"+ progress.at(i) + "\n\n";			
		}
		return str;
	}
};


class Maze
{
	public:
		Maze(int, int);
		Maze(int, int, string);
		~Maze();
		void printMazeSize();
		int getMaxNumOfExits();
		void setExits(int exits) {
			this->noOfExits = exits;
		};
		void printMaze();
		string toString();
		void generateMaze();

		void getBestExitPaths();

		void clearSolutions();
		MazeProgression* getProgression() {
			return &progression;
		}


	private:
		int width, height;
		int noOfExits = 1;
		
		int getNodesPos(int x, int y) {
			return x + (y * width);
		}
		std::vector <MazeNode> nodes;
		std::vector <MazeNode*> exits;
		MazeProgression progression;


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


		void expandNode(std::vector<MazeNode*>& openList, MazeNode* bestNode, MazeNode* endNode, std::vector <MazeNode>& nodes);
		bool isNodeValid(int, int, std::vector<MazeNode>&);
		vector<MazeNode*> getPathResults(MazeNode*, MazeNode*);
		MazeNode* getBestNode(std::vector<MazeNode*>& openList);
		vector<MazeNode*> getBestPath(MazeNode* start, MazeNode* end);

		int ManhattanDistance(MazeNode* a, MazeNode* b) {
			return abs(a->x - b->x) + abs(a->y - b->y);
		}
		
		
};

