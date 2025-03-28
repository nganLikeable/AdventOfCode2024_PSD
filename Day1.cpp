#include <iostream>
#include <fstream> // Stream class to read and write file
#include <string> // String class to handle string
#include <vector> // Vector class to handle dynamic array
#include <sstream> // Stream class to operate on strings
#include <algorithm>

using namespace std;

// Function prototype: declare the function before using it (before the main function), otherwise, the compiler will throw an error. Declare it before without using the prototype.
// int calculateDistance(string fileName);
pair<vector<int>, vector<int>> readParseFile(string fileName);
int calculateDistance(vector<int> left, vector<int> right);
int calculateSimilarityScore(vector<int> left, vector<int> right);

int main(){
    string fileName = "input1.txt";
    pair<vector<int>, vector<int>> parsedData = readParseFile(fileName);

    vector<int> left = parsedData.first;
    vector<int> right = parsedData.second;

	if (left.size() == right.size()) {
        // Part 1
        cout << "The distance is " << calculateDistance(left, right) << endl; 
        // Part 2
	    cout << "The similarity score is " << calculateSimilarityScore(left, right) << endl; // 
	}
}

// Part 1

// Return 2 vectors of left and right numbers
pair<vector<int>, vector<int>> readParseFile(string fileName) {
   string line;
   ifstream file(fileName);

   vector<int> left;
   vector<int> right;

   if (file.is_open()) {
       while (getline(file, line)) {
           istringstream ss(line); // Initialize an input string stream with the line
           string left_val, right_val;

           if (ss >> left_val) { // Extract the value from the string stream
               // '>>' reads characters from the stream until it encounters whitespace
               left.push_back(stoi(left_val)); // Store the value in the left vector
               // stoi() converts the string to an integer
           }
           ss.ignore(2, ' '); // Ignore the comma

           if (ss >> right_val) { // Extract the value from the string stream
               right.push_back(stoi(right_val)); // Store the value in the right vector
           }
       }
       file.close();
       return make_pair(left, right);
   } else {
       cerr << "Unable to open file: " << fileName << endl; // Display error message
       return make_pair(vector<int>(), vector<int>()); // Return empty vectors
   }
}

int calculateDistance(vector<int> left, vector<int> right) {
    int distance = 0;
    
	sort(left.begin(), left.end());
	sort(right.begin(), right.end()); // Sort( first iterator, last iterator, comp (opt))

    for (int i = 0; i < left.size(); i++) {
        distance += abs(left[i] - right[i]);
    }
    return distance;
}

// Part 2
int calculateSimilarityScore(vector<int> left, vector<int> right) {

    int similarity_score = 0;

    for (int i = 0; i < left.size(); i++) {
        similarity_score += left[i] * count(right.begin(), right.end(), left[i]);
    }
	return similarity_score;
}
