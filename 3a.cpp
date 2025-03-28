#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

using namespace std;

// Prototype
int multiply(int a, int b);
void sumMul(string input);

int main()
{
    string filename = "input3.txt";
    sumMul(filename);
    return 0;
}

int multiply(int a, int b) {
    return a * b;
}

void sumMul(string input) {
    ifstream file(input);
    string paragraph;
    regex reg(R"(mul\((\d{1,3})\s*,\s*(\d{1,3})\))");
    smatch match;
    int sum = 0;

    if (file.is_open()) {
        while (getline(file, paragraph)) {
            string::const_iterator searchStart(paragraph.cbegin());
            while (regex_search(searchStart, paragraph.cend(), match, reg)) {
                int num1 = stoi(match[1].str());
                int num2 = stoi(match[2].str());
                sum += multiply(num1, num2);
                searchStart = match.suffix().first;
            }
        }
    }
    file.close();
    cout << "Sum of all multiplications: " << sum << endl;
}