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
		/* Variables */
		int width, height;
		int noOfExits = 1;
		std::vector <MazeNode> nodes;
		std::vector <MazeNode*> exits;
		MazeProgression progression;

		/* Getters */
		vector <MazeNode*> getPossibleExits();
		vector <MazeNode*> getInnerBorder();
		vector <MazeNode*> getPathInnerBorder();
		vector <MazeNode*> getRow(int y, int start, int end);
		vector <MazeNode*> getRow(int y) { return getRow(y, 0, width); };
		vector <MazeNode*> getCol(int x, int start, int end);
		vector <MazeNode*> getCol(int x) { return getCol(x, 0, height); };


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
		int getDirDistX(MazeNode*, Directions*, int);
		int getDirDistY(MazeNode*, Directions*, int);
		int getDirDistOffset(int,int);
		void fillPathNodes(MazeNode*, MazeNode*);
		void expandNode(std::vector<MazeNode*>& openList, MazeNode* bestNode, MazeNode* endNode, std::vector <MazeNode>& nodes);
		std::vector<MazeNode*> getValidNeighbours(MazeNode* bestNode, std::vector<MazeNode>& nodes);
		void addNeighbour(int x, int y, vector<MazeNode>& nodes, vector<MazeNode*>* neighbours);
		bool isNodeValid(int, int, std::vector<MazeNode>&);
		vector<MazeNode*> getPathResults(MazeNode*, MazeNode*);
		MazeNode* getBestNode(std::vector<MazeNode*>& openList);
		void updateBestNode(MazeNode* node, MazeNode* bestNode, float* bestF);
		vector<MazeNode*> getBestPath(MazeNode* start, MazeNode* end);
		int ManhattanDistance(MazeNode* a, MazeNode* b) {return abs(a->x - b->x) + abs(a->y - b->y);}		


		/* Math */
		bool inRange(int val, int min, int max);
		bool isEven(int val) { return val % 2 == 0; }
		bool inMazeRange(int x, int y) {	return inRange(x, 0, width - 1) && inRange(y, 0, height - 1);}

		/* Nodes */
		bool isPathNode(MazeNode* node) { return node->nodeType == ' ';  }
		int getNodesPos(int x, int y) { return x + (y * width); }
		MazeNode* getNode(int x, int y) { return  &nodes.at(getNodesPos(x, y)); }
		MazeNode* getStartNode() { return getNode((width - 1) / 2, (height - 1) / 2); }
		void findPossibleExits(vector<MazeNode*> inner, vector<MazeNode*> outer, vector<MazeNode*>* exits);

		/* Collab Pathfinding */
		void collabPathfinding(vector<Player*>*);
		void updateCPOutcome(vector<Player*>*);	
		void movePlayer(Player*);

		/* Player */
		bool hasPlayerMoved(Player* player) { return player->path.size() > 0 ? (player->path.back()->passable) : false; };
		void onPlayerLeaveNode(Player* player);
		void onPlayerEnterNode(Player* player);
};

