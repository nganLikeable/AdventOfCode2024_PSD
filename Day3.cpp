#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <regex> // https://www.studyplan.dev/pro-cpp/regex - regex in C++

#include <algorithm>

using namespace std;

// Prototype
int multiply(int a, int b);
int parseCalculateSum(string fileName);
int enabled(string fileName);

int main()
{
    string filename = "day3_real.txt";
    int sum = parseCalculateSum(filename);
    cout << "Sum of all multiplications: " << sum << endl; // Answer: 178538786
    cout << (sum == 178538786) << endl;

	int sum2 = enabled(filename);
	cout << "Sum of all multiplications: " << sum2 << endl; 
}

// Part 1

int multiply(int num1, int num2) {
    return num1 * num2;
}

int parseCalculateSum(string fileName) {
    ifstream file(fileName);
    string paragraph;
    regex reg(R"(mul\((\d{1,3})\s*,\s*(\d{1,3})\))");
    smatch match;


    int sum = 0;

    if (file.is_open()) {
        while (getline(file, paragraph)) {

            // Iterator is generalization of pointer 
            string::const_iterator searchStart(paragraph.cbegin());
			string::const_iterator searchEnd(paragraph.cend());

            while (regex_search(searchStart, searchEnd, match, reg)) {
                int num1 = stoi(match[1].str()); // match: return iterator => convert to string bc match is of type std::sub_match<std::string::const_iterator>
                int num2 = stoi(match[2].str());
                // match[0]: entire match, would be mul(107,760)
				// match[1]: first group, would be 107, same for match[2] = 760

                sum += multiply(num1, num2);

                // Points to the next position after the last match
                searchStart = match.suffix().first; 
            }
        }
        file.close();
    }
    else {
		cerr << "Unable to open file: " << fileName << endl;
    }
    return sum;
}

// Part 2

int enabled(string fileName) {
    ifstream file(fileName);
    string paragraph;
    regex reg(R"(mul\((\d{1,3})\s*,\s*(\d{1,3})\))");
    regex do_reg(R"(do\(\))");
    regex dont_reg(R"(don't\(\))");
    smatch match;
    bool isEnabled = true;
    int sum = 0;

    if (file.is_open()) {
        while (getline(file, paragraph)) {
            // Check for do() or don't() instructions first
            if (regex_search(paragraph, do_reg)) {
                isEnabled = true;
            }
            else if (regex_search(paragraph, dont_reg)) {
                isEnabled = false;
            }

            // Now check for mul instructions
            string::const_iterator searchStart(paragraph.cbegin());
            string::const_iterator searchEnd(paragraph.cend());

            while (regex_search(searchStart, searchEnd, match, reg)) {
                if (isEnabled) {
                    int num1 = stoi(match[1].str());
                    int num2 = stoi(match[2].str());
                    sum += multiply(num1, num2);
                }

                // Points to the next position after the last match
                searchStart = match.suffix().first;
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << fileName << endl;
    }
    return sum;
}

