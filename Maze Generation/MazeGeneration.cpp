#include "MazeGeneration.h"

string MazeGeneration::getUserInput()
{
	string str;
	cin >> str;
	return str;
}

string MazeGeneration::getUserFileName(string msg)
{
	outputln(msg);
	return getFileWithExt(getUserInput());
}

int MazeGeneration::getUserInt(string errorMsg)
{
	string input = getUserInput();
	bool isValid = isIntValid(input);
	if (!isValid) { outputln(errorMsg); }
	return isValid ? stoi(input) : getUserInt(errorMsg);
}

int MazeGeneration::getUserInt(string errorMsg, int min, int max)
{
	int val = getUserInt(errorMsg);
	bool isValid = val >= min && val <= max;
	if (!isValid) { outputln("Must be between the range of " + to_string(min) + " and " + to_string(max)); }
	return isValid ? val : getUserInt(errorMsg, min, max);
}


void MazeGeneration::outputln(string out)
{
	cout << out << endl;
}

bool MazeGeneration::isIntValid(string val)
{
	for (int i = 0; i < val.length(); i++) {
		if (!isdigit(val[i])) return false;
	}

	return true;
}

string MazeGeneration::getFileWithExt(string filename)
{
	int size = filename.length();
	bool ext = size < 4 ? false : filename.substr(size - 4, size) == ".txt";
	return filename + (ext ? "" : ".txt");
}
