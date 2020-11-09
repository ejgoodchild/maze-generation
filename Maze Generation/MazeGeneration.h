#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>       // std::chrono::system_clock
#include <array>        // std::array
#include <string>

using namespace std;
class MazeGeneration
{
	protected:
		string getUserInput();
		string getUserFileName(string);
		int getUserInt(string);
		int getUserInt(string, int, int);
		void outputln(string);
		bool inRange(int val, int min, int max) { return val <= max ? val >= min : false; }
		bool isEven(int val) { return val % 2 == 0; }
	private:
		bool isIntValid(string val);
		string getFileWithExt(string filename);
};

