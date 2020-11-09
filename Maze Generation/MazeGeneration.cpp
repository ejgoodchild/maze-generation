/*
* Author: Ethan Goodchild
*/

#include "MazeGeneration.h"

/**
 * Gets the string of the users input
 *
 * @return the string of what the user has typed
 */
string MazeGeneration::getUserInput()
{
	string str;
	cin >> str;
	return str;
}
/**
 * Outputs a message and requests a file name from the user,
 * the extension is checked and added if neccesary and then 
 * returned
 * 
 * @return the file name the user has specified with appropiate
 * extension
 */
string MazeGeneration::getUserFileName(string msg)
{
	outputln(msg);
	return getFileWithExt(getUserInput());
}

/**
 * Gets users input and tests to see if it is an integer, if 
 * so it is returned otherwise an error message is prompt ans
 * asks the user to try again
 *
 * @param the error message
 * @return integer value from user input
 */
int MazeGeneration::getUserInt(string errorMsg)
{
	string input = getUserInput();
	bool isValid = isIntValid(input);
	if (!isValid) { outputln(errorMsg); }
	return isValid ? stoi(input) : getUserInt(errorMsg);
}
/**
 * Gets users input and tests to see if it is an integer and in range, if
 * so it is returned otherwise an error message is prompt ans
 * asks the user to try again
 *
 * @param the error message, the minimum value and maximum value in range
 * @return integer value from user input
 */
int MazeGeneration::getUserInt(string errorMsg, int min, int max)
{
	int val = getUserInt(errorMsg);
	bool isValid = inRange(val, min, max);
	if (!isValid) { outputln("Must be between the range of " + to_string(min) + " and " + to_string(max)); }
	return isValid ? val : getUserInt(errorMsg, min, max);
}

/**
 * Outputs string and starts newline
 *
 * @param the string to be outputted
 */
void MazeGeneration::outputln(string out)
{
	cout << out << endl;
}

/**
 * Checks if each character in the string is a digit
 *
 * @param the string to check
 * @return true if an integer, false if not
 */
bool MazeGeneration::isIntValid(string val)
{
	for (int i = 0; i < val.length(); i++) 
		if (!isdigit(val[i])) return false;
	

	return true;
}
/**
 * Checks filename and adds extension if it is needed
 *
 * @param string of the filename to be checked
 * @return the filename with the extension
 */
string MazeGeneration::getFileWithExt(string filename)
{
	int size = filename.length();
	bool ext = size < 4 ? false : filename.substr(size - 4, size) == ".txt";
	return filename + (ext ? "" : ".txt");
}
