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
int addMiddlePages(vector<vector<int>> updates, map <int, vector<int>> m);
bool isOrdered(vector<int>u, map<int, vector<int>> m);

int main()
{
    string f = "input5.txt";
    pair<vector<vector<int>>, vector<vector<int>>> rules_updates = parseData(f);

    vector<vector<int>> rules = rules_updates.first;
    vector<vector<int>> updates = rules_updates.second;

    map <int, vector<int>> m = getRules(rules);
    int sum = addMiddlePages(updates, m);
    cout << sum << endl;

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

int addMiddlePages(vector<vector<int>> updates, map <int, vector<int>> m) {
    int sum = 0;
    for (size_t i = 0; i < updates.size(); i++) {
        if (isOrdered(updates[i], m)) {
            size_t mid = updates[i].size() / 2;
            sum += updates[i][mid];
        }
    }
    return sum;
}

// check each line
bool isOrdered(vector<int> u, map<int, vector<int>> m) {

    // compare one page with other pages => iterating over
    for (size_t i = 0; i < u.size(); ++i) {
        for (size_t j = i + 1; j < u.size(); ++j) {
            int before = u[i];
            int after = u[j];

            // search if after in a value in the vector of before key
            if (find(m[before].begin(), m[before].end(), after) == m[before].end()) {
                return false;
            }
        }
    }
    return true;
}
