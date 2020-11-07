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
	progression.originalMaze = toString();
}

void Maze::getBestExitPaths()
{
	//progression.originalMaze = toString();

	for (int i = 0; i < exits.size(); i++) {
		std::vector <MazeNode*> path = getBestPath(exits.at(i), getStartNode());
		for (int j = 1; j < path.size(); j++) {

			path.at(j)->nodeType = 'o';
			progression.progress.emplace_back(toString());
		}
	}

	cout << progression.toString();
}

void Maze::collabPathfinding(int noOfPlayers)
{
	vector<Player*> players;
	getStartNode()->nodeType = 'F';
	std::random_shuffle(exits.begin(), exits.end());

	for (int i = 0; i < noOfPlayers; i++) {
		players.emplace_back(new Player(exits.at(i)));
		players.at(i)->path = getBestPath(players.at(i)->curNode, getStartNode());

	}
	collabPathfinding(&players);
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

void Maze::generatePaths()
{
	MazeNode* start = getStartNode();
	int x = (width % 2 == 1) ? (((width - 1) / 2) % 2 == 0 ? start->x + 1 : start->x) : start->x;
	int y = (height % 2 == 1) ? (((height - 1) / 2) % 2 == 0 ? start->y + 1 : start->y) : start->y;
	generatePaths(getNode(x, y));
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
			mNode = getNode(x, y);
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
			mNode = getNode(x, y);
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
	if (exitsPossible >= noOfExits) return;
	std::vector <MazeNode*> nodes = getPathInnerBorder();
	std::random_shuffle(std::begin(nodes), std::end(nodes));

	int additionalRoutes = (noOfExits - exitsPossible) % nodes.size();
	for (int i = additionalRoutes; i >= 0; i--) generatePaths(nodes.at(i));
}

/**
 * Recursively generates a random path around the maze until an invalid end node is found
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

vector<MazeNode*> Maze::getPossibleExits()
{
	std::vector <MazeNode*> possibleExits;
	findPossibleExits(getCol(1),getCol(0), &possibleExits);
	findPossibleExits(getCol(width-2),getCol(width-1), &possibleExits);
	findPossibleExits(getRow(1, 1, width-1), getRow(0, 1, width - 1), &possibleExits);
	findPossibleExits(getRow(height-2, 1, width-1), getRow(height-1, 1, width - 1), &possibleExits);

	return possibleExits;
}

vector<MazeNode*> Maze::getInnerBorder()
{
	vector <MazeNode*> nodes;
	for (int y = 0; y < height; y++) {
		nodes.emplace_back(getNode(1, y));
		nodes.emplace_back(getNode(width - 2, y));
	}
	for (int x = 1; x < width - 1; x++) {
		nodes.emplace_back(getNode(x, 1));
		nodes.emplace_back(getNode(x, height - 2));
	}
	return nodes;
}

vector<MazeNode*> Maze::getPathInnerBorder()
{
	vector <MazeNode*> inner = getInnerBorder();
	vector <MazeNode*> nodes;
	for (int i = 0; i < inner.size(); i++) 
		if (isPathNode(inner.at(i))) 
			nodes.emplace_back(inner.at(i));

	return nodes;
}

vector<MazeNode*> Maze::getRow(int y, int start, int end)
{
	vector <MazeNode*> nodes;
	for (int x = start; x < end; x++) 
		nodes.emplace_back(getNode(x, y));

	return nodes;
}

vector<MazeNode*> Maze::getCol(int x, int start, int end)
{
	vector <MazeNode*> nodes;
	for (int y = start; y < end; y++)
		nodes.emplace_back(getNode(x, y));

	return nodes;
}





/**
 * Finds where the end node will be positioned in a given the direction
 *
 * @param the starting node and the direction the path is travelling
 * @return MazeNode* of end node or NULL if end node is not valid.
 */
MazeNode* Maze::getPathEndNode(MazeNode* curNode, Directions dir)
{
	int x = getDirDistX(curNode, &dir, 2);
	int y = getDirDistY(curNode, &dir, 2);

	MazeNode* endNode = getNode(curNode->x + x, curNode->y + y);
	return isPathNode(endNode) ? NULL : curNode == endNode ? NULL : endNode; //if end node has already had its type defined then return null
}

int Maze::getDirDistX(MazeNode* curNode, Directions* dir, int step)
{
	if(!(*dir == Directions::EAST || *dir == Directions::WEST)) return 0;
	int x = *dir == Directions::EAST ? (inRange(curNode->x + step, 1, width-2) ? step : 0) :
		(inRange(curNode->x - step, 1, width - 2)? -step : 0); //if east and in range return step, if west and in range return -step, otherwise 0
	
	return x + getDirDistOffset(curNode->x, width);
}

int Maze::getDirDistY(MazeNode* curNode, Directions* dir, int step)
{
	if (!(*dir == Directions::NORTH || *dir == Directions::SOUTH)) return 0;
	int y = *dir == Directions::SOUTH ? (inRange(curNode->y + step, 1, height - 2) ? step : 0) :
		(inRange(curNode->y - step, 1, height - 2) ? -step : 0); //if east and in range return step, if west and in range return -step, otherwise 0

	return y + getDirDistOffset(curNode->y, height);
}

int Maze::getDirDistOffset(int val, int len)
{
	if (!isEven(len)) { return 0; } //if length not even return 0
	return val < len/2 ? (isEven(val) ? -1 : 0) : (!isEven(val) ? 1 : 0); 
	//if val if less than half the val and val is even return -1, if val is greater than half val and is odd return 1	
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

		if (best == to) return getPathResults(from, to);
	
		expandNode(openList, best, to, nodes);

	}

	return vector<MazeNode*>(); // returns empty if no path found
}



bool Maze::inRange(int val, int min, int max)
{
	return val <= max ? val >= min : false;
}

void Maze::findPossibleExits(vector<MazeNode*> inner, vector<MazeNode*> outer, vector<MazeNode*>* exits)
{
	for (int i = 0; i < inner.size(); i++) 
		if (inner.at(i)->passable) exits->emplace_back(outer.at(i));
	
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
	player->hasMoved = hasPlayerMoved(player);
	if (!player->hasMoved) return; 
		
	onPlayerLeaveNode(player);
	onPlayerEnterNode(player);
}

void Maze::onPlayerLeaveNode(Player* player)
{
	player->curNode->nodeType = player->isFirstNode ? 'E' : 'o';
	player->curNode->passable = true;
	player->isFirstNode = false;
	player->curNode = player->path.back();
	player->path.pop_back();
}

void Maze::onPlayerEnterNode(Player* player)
{
	bool isStart = getStartNode() == player->curNode;
	player->curNode->passable = isStart;
	player->curNode->nodeType = isStart ? 'F' : 'P';
}

MazeNode* Maze::getBestNode(std::vector<MazeNode*>& openList)
{
	MazeNode* bestNode = openList.at(0);
	float bestF = bestNode->g + bestNode->h;

	for (MazeNode* i : openList) {
		updateBestNode(i, bestNode, &bestF);
	}
	return bestNode;
}

void Maze::updateBestNode(MazeNode* node, MazeNode* bestNode, float* bestF)
{
	float iF = node->g + node->h;
	if (iF >= *bestF) return;
	bestNode = node;
	*bestF = iF;
}

void Maze::expandNode(std::vector<MazeNode*>& openList, MazeNode* bestNode, MazeNode* endNode, std::vector<MazeNode>& nodes)
{
	vector<MazeNode*> neighbours = getValidNeighbours(bestNode, nodes);
	for (MazeNode* i : neighbours) {
		i->bestParent = bestNode;
		i->g = i->bestParent->g;
		i->h = ManhattanDistance(i, endNode);
		openList.emplace_back(i);		
	}
}

vector<MazeNode*> Maze::getValidNeighbours(MazeNode* bestNode, std::vector<MazeNode>& nodes)
{
	vector<MazeNode*> neighbours;
	addNeighbour(bestNode->x + 1, bestNode->y, nodes, &neighbours);
	addNeighbour(bestNode->x - 1, bestNode->y, nodes, &neighbours);
	addNeighbour(bestNode->x, bestNode->y + 1, nodes, &neighbours);
	addNeighbour(bestNode->x, bestNode->y - 1, nodes, &neighbours);

	return neighbours;
}

void Maze::addNeighbour(int x, int y, vector<MazeNode>& nodes, vector<MazeNode*>* neighbours)
{
	if (!isNodeValid(x, y, nodes)) return;
	(*neighbours).emplace_back(&nodes.at(getNodesPos(x, y)));
}



bool Maze::isNodeValid(int x, int y, std::vector<MazeNode>& nodes)
{
	if (!inMazeRange(x, y)) return false; //if node out of range
	MazeNode* node = &nodes.at(getNodesPos(x, y));	//get node	
	return !node->closed ? node->passable : false;
}

vector<MazeNode*> Maze::getPathResults(MazeNode* start, MazeNode* end)
{
	std::vector<MazeNode*> path;
	MazeNode* m = end;
	while (m != start) {
		path.emplace_back(getNode(m->x, m->y));
		m = m->bestParent;
	}
	return path;
}

string MazeProgression::getOutcomeStatment(Outcome outcome){
	return outcome == Outcome::SOLVABLE ? "A maze is fully solvable as all players can reach the finishing point" :
	(outcome == Outcome::PARTIAL ? "A maze is partially solvable as some players can reach the finishing point" :
	(outcome == Outcome::UNSOLVABLE ? "A maze is not solvable due to all players blocking each other" : ""));
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
