#pragma once

#include "MazeGeneration.h"

using namespace std;
enum class Directions {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
enum class Outcome {SOLVABLE =0, PARTIAL = 1, UNSOLVABLE =2, UNKNOWN = 3};
struct MazeNode {
	int x, y;
	char nodeType = NULL;
	float g, h;
	bool passable = true;
	bool closed = false;
	MazeNode* bestParent = NULL;
	MazeNode(int x, int y);
	MazeNode(int x, int y, char nodeType);
};
struct MazeProgression {
	string originalMaze;
	Outcome outcome = Outcome::UNKNOWN;
	std::vector<string> progress;
	
	string toString() {
		string str = originalMaze + "\n\n";
		for (int i = 0; i < progress.size(); i++) {
			str += "Step " + std::to_string(i+1) + "\n"+ progress.at(i) + "\n\n";			
		}
		str += getOutcomeStatment(outcome) + "\n\n";
		return str;
	}
	string getOutcomeStatment(Outcome outcome);
};
struct Player {
	Player(MazeNode* curNode) {
		this->curNode = curNode;
		curNode->nodeType = 'P';
		curNode->passable = false;
	}
	MazeNode* curNode = NULL;
	bool hasMoved = false;
	bool isFirstNode = true;
	vector<MazeNode*> path;

};

class Maze : protected MazeGeneration
{
	public:
		/* Maze Constructors / Destructors */
		Maze(int, int);
		Maze(int, int, string);
		Maze(int, int, string, std::vector<string>);
		~Maze();

		/* Printing / toString Functions */
		void printMazeSize();
		void printMaze();
		string toString();

		/* Getters / Setters */
		int getMaxNumOfExits();
		void setExits(int exits) { this->noOfExits = exits;};
		int getNoOfExits() { return noOfExits; }
		void clearSolutions();
		MazeProgression* getProgression() { return &progression; }

		/* Maze Generation */
		void generateMaze();

		/* Pathfinding */
		void getBestExitPaths();
		void collabPathfinding(int noOfPlayers);

	private:
		/* Constants */

		
		/* Variables */
		int width, height;
		int noOfExits = 1;
		std::vector <MazeNode> nodes;
		std::vector <MazeNode*> exits;
		MazeProgression progression;

		/* Getters */
		int getNodesPos(int x, int y) { return x + (y * width); }
		MazeNode* getStartNode() { return &nodes.at(getNodesPos((width - 1) / 2, (height - 1) / 2)); }
		std::vector <MazeNode*> getPossibleExits();

		/* Maze Generation */
		void generateNodes();
		void generatePaths();
		void generatePaths(MazeNode* node);
		void generateStartPoint();
		void generateWalls();
		void generateExits();
		void generateAdditionalPaths();

		/* Pathfinding */
		MazeNode* getPathEndNode(MazeNode*, Directions);
		void fillPathNodes(MazeNode*, MazeNode*);
		void expandNode(std::vector<MazeNode*>& openList, MazeNode* bestNode, MazeNode* endNode, std::vector <MazeNode>& nodes);
		bool isNodeValid(int, int, std::vector<MazeNode>&);
		vector<MazeNode*> getPathResults(MazeNode*, MazeNode*);
		MazeNode* getBestNode(std::vector<MazeNode*>& openList);
		vector<MazeNode*> getBestPath(MazeNode* start, MazeNode* end);
		int ManhattanDistance(MazeNode* a, MazeNode* b) {return abs(a->x - b->x) + abs(a->y - b->y);}		
		
		/* Collab Pathfinding */
		void collabPathfinding(vector<Player*>*);
		void updateCPOutcome(vector<Player*>*);	
		void movePlayer(Player*);

		

};

