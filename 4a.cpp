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
int traverseGrid(vector<vector<string>> grid);
bool findXMAS(int row, int col, int pos, vector<int> direction, vector<vector<string>> grid);

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
	cout << traverseGrid(grid) << endl;

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

// Recursive approach 
int traverseGrid(vector<vector<string>> grid) {
	int count = 0;

	for (int row = 0; row < grid.size(); row++) {
		for (int col = 0; col < grid[row].size(); col++) {
			// cout << "Checking: " << row << ", " << col << endl;
			// Check for 'X'
			if (grid[row][col] == wordList[0]) {
				// cout << "Found X at: " << row << ", " << col << endl;
				// Check all directions
				for (int dir = 0; dir < directions.size(); dir++) {
					// cout << "Checking" << endl;
					if (findXMAS(row, col, 1, directions[dir], grid)) {
						count++;
						cout << count << " Coordinates: " << "(" << row << ", " << col << ")" << endl;
					}				
				}
			}
		}
	}
	return count;
}

bool findXMAS(int row, int col, int pos, vector<int> direction, vector<vector<string>> grid) {
	int row_next = row + direction[0];
	int col_next = col + direction[1];

	// Base case
	if (pos > wordList.size() - 1) {
		return true;
	}

	// Check if the next cell is within the grid
	if (row_next < 0 || row_next >= grid.size() || col_next < 0 || col_next >= grid[row].size()) {
		return false;
	}

	// Check if the next cell contains the next letter in the word - Recursion
	if (grid[row_next][col_next] == wordList[pos]) {
		return findXMAS(row_next, col_next, pos + 1, direction, grid);
	}
	return false;
}

