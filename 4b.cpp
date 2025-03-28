// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <algorithm>
# include <sstream>

using namespace std;

vector<vector<string>> getGrid(string filename);
int traverseGrid2(vector<vector<string>>);
bool findMAS(int row, int col, vector<vector<string>>);

// Global variables
vector<vector<int>> directions = { // {row, col}
	{0, -1}, // up
	{0, 1}, // down
	{-1, 0}, // left
	{1, 0}, // right
	{-1, -1}, // up left
	{1, -1}, // up right
	{-1, 1}, // down left
	{1, 1} // down right
};

vector<string> wordList = { "X", "M", "A", "S" };

int main(){
	vector<vector<string>> grid = getGrid("input4.txt");
	cout << traverseGrid2(grid) << endl;
}

vector<vector<string>> getGrid(string filename) {
    string line;
    ifstream file(filename);

    vector<vector<string>> grid;

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> row;

            for (int i = 0; i < line.length(); i++) {
                row.push_back(string(1, line[i])); // Convert char to string
            }
            grid.push_back(row);
        }
        file.close();
    }
    else {
        cout << "Unable to open file" <<endl;
    }
    return grid;
}

int traverseGrid2(vector<vector<string>> grid) {
	int count = 0;

	// Skip row 0 and col 0 as A is in the middle => eliminate 4 edges by starting from 1 and ending just before the last element (stop at 138 < size - 1)
	for (int row = 1; row < grid.size() - 1; row++) {
		for (int col = 1; col < grid[row].size() - 1; col++) {
			// Check for 'A'
			if (grid[row][col] == wordList[2]) {
				if (findMAS(row, col, grid)) {
					count++;
				}
			}
		}
	}
	return count;
}

bool findMAS(int row, int col, vector<vector<string>> grid) {
	// Coordinates top-down-left-right
	int rowUp = row - 1;
	int colRight = col + 1;
	int rowDown = row + 1;
	int colLeft = col - 1;

	// Get X-shaped characters
	string topLeft = grid[rowUp][colLeft];
	string topRight = grid[rowUp][colRight];
	string bottomRight = grid[rowDown][colRight];
	string bottomLeft = grid[rowDown][colLeft];

	string charM = wordList[1];
	string charS = wordList[3];

	// 2 cases for each diagonal line: forward and backwards 
	if (((topLeft == charM && bottomRight == charS) || (topLeft == charS && bottomRight == charM)) &&
		((topRight == charM && bottomLeft == charS) || (topRight == charS && bottomLeft == charM))) {
		// cout << "Coordinates: " << "(" << row << ", " << col << ")" << endl;
		return true;
	}
	return false;
}