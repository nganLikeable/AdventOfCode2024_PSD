#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>


using namespace std;

pair<vector<vector<int>>, vector<vector<int>>> parseData(string filename);
map<int, vector<int>> getRules(vector<vector<int>> rules);
vector<int> correctPageOrder(vector<int> line, map<int, vector<int>> rules);
int getCorrectOrderedPages(map<int, vector<int>> rules, vector<vector<int>> updates);

int main()
{
    string f = "input5.txt";
    pair<vector<vector<int>>, vector<vector<int>>> rules_updates = parseData(f);

    vector<vector<int>> rules = rules_updates.first;
    vector<vector<int>> updates = rules_updates.second;

    map <int, vector<int>> m = getRules(rules);
    int score = getCorrectOrderedPages(m, updates);

    cout << score << endl;

}

pair<vector<vector<int>>, vector<vector<int>>> parseData(string filename) {
    string line;
    ifstream file(filename);
    vector<vector<int>> rules;
    vector<vector<int>> updates;

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<int> r;
            stringstream ss(line);
            vector<int> u;

            if (line.find("|") != string::npos) {
                string first, second;
                getline(ss, first, '|');
                getline(ss, second);
                r.push_back(stoi(first));
                r.push_back(stoi(second));
                rules.push_back(r);
            }
            else if (!line.empty()) { // skip the empty line between rules and updates
                string val;
                while (getline(ss, val, ',')) {
                    u.push_back(stoi(val));
                }
                updates.push_back(u);
            }
        }
        file.close();
        return make_pair(rules, updates);
    }

    else {
        cerr << "Unable to open file" << endl;
        return make_pair(vector<vector<int>>(), vector<vector<int>>());
    }
}

map<int, vector<int>> getRules(vector<vector<int>> rules) {
    map<int, vector<int>> m; // return the key as the first page and the keys consisting of the pages that should be followed 

    for (const auto& rule : rules) {
        m[rule[0]].push_back(rule[1]);  // directly initialize a single element vector
    }
    return m;
}


// Part 2

vector<int> correctPageOrder(vector<int> line, map<int, vector<int>> rules) {
    vector<int> newLine;
    for (int num : line) {
        map<int, int> index;
        for (int i = 0; i < newLine.size(); ++i) {
            index[newLine[i]] = i;
        }

        int newInsertIndex = newLine.size();
        for (int rule : rules[num]) {
            if (index.find(rule) != index.end()) {
                newInsertIndex = min(newInsertIndex, index[rule]);
            }
        }

        vector<int> afterNum(newLine.begin() + newInsertIndex, newLine.end());
        newLine = vector<int>(newLine.begin(), newLine.begin() + newInsertIndex);
        newLine.push_back(num);
        newLine.insert(newLine.end(), afterNum.begin(), afterNum.end());
    }

    return newLine;
}

int getCorrectOrderedPages(map<int, vector<int>> rules, vector<vector<int>> updates) {
    int score = 0;
    for (auto& pageLine : updates) {
        bool ordered = true;
        for (size_t i = 0; i < pageLine.size(); ++i) {
            int num1 = pageLine[i];
            vector<int> rule = rules[num1];
            for (int num2 : rule) {
                auto it1 = find(pageLine.begin(), pageLine.end(), num1);
                auto it2 = find(pageLine.begin(), pageLine.end(), num2);
                if (it1 != pageLine.end() && it2 != pageLine.end() && it1 > it2) {
                    ordered = false;
                }
            }
        }

        if (!ordered) {
            vector<int> correctedLine = correctPageOrder(pageLine, rules);
            score += correctedLine[correctedLine.size() / 2]; // Add middle element
        }
    }
    return score;
}
