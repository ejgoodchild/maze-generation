#include "Maze.h"




/**
 * Constructor to instantiate the maze 
 * 
 * @param the width and height of the maze
 */
Maze::Maze(int w, int h)
{
	width = w;
	height = h;
	
	
}

Maze::Maze(int w, int h, string str) : Maze(w,h)
{
	
	MazeNode* mNode;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			mNode = new MazeNode(x, y, str.at(getNodesPos(x, y)));		
			nodes.emplace_back(*mNode);

			if (mNode->nodeType == 'E') exits.emplace_back(&*mNode);
		}
	}
	noOfExits = exits.size();
}

Maze::Maze(int w, int h, string mazeData, std::vector<string> progress) : Maze(w, h, mazeData)
{
	progression.originalMaze = mazeData;
	progression.progress = progress;
	cout << progression.toString();
}



Maze::~Maze()
{
	nodes.clear();
}

/**
 * Prints the maze size
 */
void Maze::printMazeSize()
{
	cout << "The maze is a size of " << width << "x" << height << endl;
}

/**
 * Calculates the maximum amount of exits possible
 */
int Maze::getMaxNumOfExits()
{
	return (width-2)*2 + (height-2)*2;
}

/**
 * Prints the maze 
 */
void Maze::printMaze()
{

	cout << toString();

}
string Maze::toString()
{
	string maze ="";
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			maze += nodes.at(getNodesPos(x, y)).nodeType;
		}
		maze += '\n';
	}
	return maze;
}
/**
 * Generates the maze by generating the nodes, paths, the start point and the walls
 */
void Maze::generateMaze()
{
	generateNodes();
	generatePaths();
	
	generateStartPoint();
	generateWalls();
	generateAdditionalPaths();
	generateExits();
	
}

void Maze::getBestExitPaths()
{
	progression.originalMaze = toString();

	for (int i = 0; i < exits.size(); i++) {
		std::vector <MazeNode*> path = getBestPath(exits.at(i), getStartNode());
		for (int j = 1; j < path.size(); j++) {

			path.at(j)->nodeType = 'o';
			progression.progress.emplace_back(toString());
		}
	}

	cout << progression.toString();
}

void Maze::clearSolutions()
{
	for (int i = 0; i < nodes.size(); i++) {
		char c = nodes.at(i).nodeType;
		nodes.at(i).nodeType = c == 'o' ? ' ' : c;
	}
	progression.progress.clear();
}





/**
 * Generates width*height number of maze nodes and gives them all x and y values
 */
void Maze::generateNodes()
{
	MazeNode* mNode;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			mNode = new MazeNode(x, y);
			nodes.emplace_back(*mNode);
			delete mNode;
		}
	}
}



/**
 * Generates a 3x3 area in the center of the maze
 * The start point is denoted with the character 'S'
 */
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

/**
 * Generates the walls on nodes that have not been assigned a node type
 * Wall node type is denoted with the character 'X'
 */
void Maze::generateWalls()
{
	MazeNode* mNode;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			mNode = &nodes.at(getNodesPos(x, y));
			if(!mNode->nodeType){ 
				mNode->nodeType = 'X';
				mNode->passable = false;
			}					
		}
	}
}

void Maze::generateExits()
{
	std::vector<MazeNode*> possibleExits = getPossibleExits();
	std::random_shuffle(possibleExits.begin(), possibleExits.end());

	for (int i = 0; i < noOfExits; i++) {
		possibleExits.at(i)->nodeType = 'E';
		possibleExits.at(i)->passable = true;
		exits.emplace_back(possibleExits.at(i));
	}

	
}

void Maze::generateAdditionalPaths()
{
	int exitsPossible = getPossibleExits().size();
	if (exitsPossible >= noOfExits) {
		return;
	}

	std::vector <MazeNode*> nodes;
	for (int y = 0; y < height; y++) {
		nodes.emplace_back(&this->nodes.at(getNodesPos(1, y)));
		nodes.emplace_back(&this->nodes.at(getNodesPos(width - 2, y)));
	}
	for (int x = 1; x < width - 1; x++) {		
			nodes.emplace_back(&this->nodes.at(getNodesPos(x, 1)));
			nodes.emplace_back(&this->nodes.at(getNodesPos(x, height - 2)));
	}

	std::random_shuffle(std::begin(nodes), std::end(nodes));
	int additionalRoutes = (noOfExits - exitsPossible) % nodes.size();
	int i = 0;
	while (additionalRoutes >= 0) {
		nodes.at(i)->nodeType == ' ' ? generatePaths(nodes.at(i)), (void)additionalRoutes-- : (void) i++ ;
	}
	
	

}

/**
 * Recursively generates a random path around the maze until an invalid end node is founf
 *
 * @param the starting node
 */
void Maze::generatePaths(MazeNode* curNode)
{
	Directions dir[]{ Directions::NORTH, Directions::EAST, Directions::SOUTH, Directions::WEST };
	MazeNode* endNode = NULL;

	std::random_shuffle(std::begin(dir), std::end(dir));
	for (int i = 0; i < 4; i++) {
		endNode = getPathEndNode(curNode, dir[i]);
		if (endNode) {
			fillPathNodes(curNode, endNode);
			generatePaths(endNode);
		}				
	}
}

std::vector<MazeNode*> Maze::getPossibleExits()
{
	std::vector <MazeNode*> possibleExits;

	for (int y = 0; y < height; y++) {
		if (nodes.at(getNodesPos(1, y)).passable) {
			possibleExits.emplace_back(&nodes.at(getNodesPos(0, y)));
		}
		if (nodes.at(getNodesPos(width - 2, y)).passable) {
			possibleExits.emplace_back(&nodes.at(getNodesPos(width - 1, y)));
		}
	}
	for (int x = 1; x < width - 1; x++) {
		if (nodes.at(getNodesPos(x, 1)).passable) {
			possibleExits.emplace_back(&nodes.at(getNodesPos(x, 0)));
		}
		if (nodes.at(getNodesPos(x, height -2)).passable) {
			possibleExits.emplace_back(&nodes.at(getNodesPos(x, height-1)));
		}
	}
	return possibleExits;
}



/**
 * Finds where the end node will be positioned in a given the direction
 *
 * @param the starting node and the direction the path is travelling
 * @return MazeNode* of end node or NULL if end node is not valid.
 */
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
	endNode = endNode->nodeType == ' ' ? NULL : endNode; //if end node has already had its type defined then return null

	return curNode == endNode ? NULL : endNode ;
}

/**
 * Fills nodes between start node and end node with the space character
 *
 * @param the starting node and the ending node
 */
void Maze::fillPathNodes(MazeNode* curNode, MazeNode* nextNode)
{

	for (int x = curNode->x; x != nextNode->x; x += curNode->x > nextNode->x ? -1 : 1) {
		
		nodes.at(getNodesPos(x, curNode->y)).nodeType = ' ';

	}
	for (int y = curNode->y; y != nextNode->y; y += curNode->y > nextNode->y ? -1 : 1) {

		nodes.at(getNodesPos(curNode->x, y)).nodeType = ' ';
	}
	
}



vector<MazeNode*> Maze::getBestPath(MazeNode* start, MazeNode* end)
{
	std::vector <MazeNode> nodes = this->nodes;
	MazeNode* from = &nodes.at(getNodesPos(start->x, start->y));
	MazeNode* to = &nodes.at(getNodesPos(end->x, end->y));

	from->g = 0;
	from->h = ManhattanDistance(from, to);

	std::vector<MazeNode*> openList;
	openList.emplace_back(from);

	while (openList.size() > 0) {
		MazeNode* best = getBestNode(openList);
		best->closed = true;
		openList.erase(std::remove(openList.begin(), openList.end(), best), openList.end());

		if (best == to) {
			return getPathResults(from, to);
		}
		expandNode(openList, best, to, nodes);

	}

	return vector<MazeNode*>(); // returns empty if no path found
}

void Maze::collabPathfinding(vector<Player*>* players)
{
	bool hasFinished = true;
	for (int i = 0; i < (*players).size(); i++) {
		movePlayer((*players).at(i));	
		hasFinished = hasFinished ? !(*players).at(i)->hasMoved : false;
		progression.progress.emplace_back(toString());
	}
	
	hasFinished ? updateCPOutcome(players) : collabPathfinding(players);
	
}

void Maze::updateCPOutcome(vector<Player*>* players)
{
	int playersAtEnd = 0;
	for (int i = 0; i < (*players).size(); i++) {
		playersAtEnd += (*players).at(i)->curNode == getStartNode() ? 1 : 0;
	}
	progression.outcome = playersAtEnd == (*players).size() ? Outcome::SOLVABLE :
		(playersAtEnd > 0 ? Outcome::PARTIAL : Outcome::UNSOLVABLE);
	
}

void Maze::movePlayer(Player* player)
{
	player->hasMoved = player->path.size() > 0 ? (player->path.back()->passable) : false;
	if (player->hasMoved) {
		player->curNode->nodeType = player->isFirstNode ? 'E' : 'o';
		player->curNode->passable = true;
		player->isFirstNode = false;
		player->curNode = player->path.back();
		player->path.pop_back();
		
		player->curNode->passable = getStartNode() == player->curNode ? true : false ;
		player->curNode->nodeType = getStartNode() == player->curNode ? 'F':'P';
	}
}

MazeNode* Maze::getBestNode(std::vector<MazeNode*>& openList)
{
	MazeNode* bestNode = openList.at(0);
	float bestF = bestNode->g + bestNode->h;

	for (MazeNode* i : openList) {
		float iF = i->g + i->h;
		bestNode = iF < bestF ? i: bestNode ;
		bestF = iF < bestF ? iF : bestF ;
	}
	return bestNode;
}

void Maze::expandNode(std::vector<MazeNode*>& openList, MazeNode* bestNode, MazeNode* endNode, std::vector<MazeNode>& nodes)
{

	std::vector<MazeNode*> neighbours;
	neighbours.emplace_back(isNodeValid(bestNode->x + 1, bestNode->y, nodes) ? &nodes.at(getNodesPos(bestNode->x + 1, bestNode->y)) : NULL);
	neighbours.emplace_back(isNodeValid(bestNode->x, bestNode->y +1, nodes) ? &nodes.at(getNodesPos(bestNode->x, bestNode->y + 1)) : NULL);
	neighbours.emplace_back(isNodeValid(bestNode->x - 1, bestNode->y, nodes) ? &nodes.at(getNodesPos(bestNode->x - 1, bestNode->y)) : NULL);
	neighbours.emplace_back(isNodeValid(bestNode->x, bestNode->y -1, nodes) ? &nodes.at(getNodesPos(bestNode->x, bestNode->y - 1)) : NULL);


	for (MazeNode* i : neighbours) {
		if (i) {
			i->bestParent = bestNode;
			i->g = i->bestParent->g;
			i->h = ManhattanDistance(i, endNode);
			openList.emplace_back(i);
		}
	}

}

bool Maze::isNodeValid(int x, int y, std::vector<MazeNode>& nodes)
{
	bool inXRange = 0 <= x ? (x < width ? true : false) : false;
	bool inYRange = 0 <= y ? (y < height ? true : false) : false;
	if (inXRange && inYRange) {
		MazeNode* node = &nodes.at(getNodesPos(x, y));
		
		return !node->closed ? node->passable : false;
	}

	return false;
}

vector<MazeNode*> Maze::getPathResults(MazeNode* start, MazeNode* end)
{
	std::vector<MazeNode*> path;
	MazeNode* m = end;
	while (m != start) {
		path.emplace_back(&nodes.at(getNodesPos(m->x, m->y)));
		m = m->bestParent;
	}
	return path;
}

string MazeProgression::getOutcomeStatment(Outcome outcome)

	{
		return outcome == Outcome::SOLVABLE ? "A maze is fully solvable as all players can reach the finishing point" :
			(outcome == Outcome::PARTIAL ? "A maze is partially solvable as some players can reach the finishing point" :
				(outcome == Outcome::UNSOLVABLE ? "A maze is not solvable due to all players blocking each other" :
					""));
	}

MazeNode::MazeNode(int x, int y)
{
	this->x = x;
	this->y = y;
}

MazeNode::MazeNode(int x, int y, char nodeType) : MazeNode(x, y)
{
	this->nodeType = nodeType;
	this->passable = nodeType == 'X' ? false : true;

}
