// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;
vector<vector<int>> readData(string fileName);
void displayReport(vector<vector<int>> report);
bool isIncreasingValid(vector <int> report_level);
bool isDecreasingValid(vector <int> report_level);
bool checkDifference(vector <int> report_level, int index);
bool isSafe(vector <int> report_level);
bool canTolerate(vector <int> report_level);

int main()
{
    string fileName = "input2.txt";
    vector<vector<int>> report = readData(fileName);
    int safe = 0;

    for (int i = 0; i < report.size(); i++) {
        if (isSafe(report[i])) {
            safe++;
        }
        else {
            if (canTolerate(report[i])) {
                safe++;
            }
        }
    }

    cout << "Number of safe levels (including tolerable ones): " << safe << endl;

}

// Part 1
vector<vector<int>> readData(string fileName) {
    string level;
    ifstream file(fileName);

    vector<vector<int>> report;

    if (file.is_open()) {
        while (getline(file, level)) {
            istringstream  ss(level);
            string val;
            vector<int> row; // Store the row vector first

            // Iterate through the string level
            for (int i = 0; i < level.length(); i++) {
                if (ss >> val) {
                    row.push_back(stoi(val));
                }
                else {
                    ss.ignore(1, ' ');
                }
            }
            report.push_back(row); // Store the final into the 2d vector
        }
        file.close();
    }
    else {
        cout << "Error opening file" << endl;
    }
    return report;
}

void displayReport(vector<vector<int>> report) {
    for (int i = 0; i < report.size(); i++) {
        for (int j = 0; j < report[i].size(); j++) {
            cout << report[i][j] << " ";
        }
        cout << endl;
    }
}

// Convert vector to set
set<int> convertToSet(vector<int> vec) {
    set<int> s(vec.begin(), vec.end());
    return s;
}

bool checkDifference(vector<int> report_level, int index) {
    int max_dif = 3;
    int min_dif = 1;

    int diff = abs(report_level[index] - report_level[index + 1]);
    return diff >= min_dif && diff <= max_dif;
}

bool isIncreasingValid(vector<int> report_level) {

    for (int i = 0; i < report_level.size() - 1; i++) {
        if (report_level[i] <= report_level[i + 1]) {
            return false;
        }

        if (!(checkDifference(report_level, i))) {
            return false;
        }
    }
    return true;
}

bool isDecreasingValid(vector<int> report_level) {

    for (int i = 0; i < report_level.size() - 1; i++) {
        if (report_level[i] >= report_level[i + 1]) {
            return false;
		}
        if (!(checkDifference(report_level, i))) {
            return false;
        }
    }
    return true;
}

bool isSafe(vector<int> report_level) {
    return isIncreasingValid(report_level) || isDecreasingValid(report_level);
}

// Part 2


bool canTolerate(vector<int> report_level) {

    for (int i = 0; i < report_level.size(); i++) {
        int temp = report_level[i];
        report_level.erase(report_level.begin() + i);

        if (isSafe(report_level)) {
            return true;
        }
        else {
            report_level.insert(report_level.begin() + i, temp);
        }
    }
    return false;
}