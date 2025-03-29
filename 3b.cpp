#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>

using namespace std;

int multiply(int a, int b) {
    return a * b;
}

void sumMulWithConditions(string input) {
    ifstream file(input);
    string paragraph;

    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    // Define the regex pattern to match do(), don't(), and mul(x, y)
    regex reg(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");
    smatch match;

    bool isEnabled = true; // Initially, multiplication is enabled
    int total = 0;

    // Read the file line by line
    while (getline(file, paragraph)) {
        string::const_iterator searchStart(paragraph.cbegin()); // Iterator to traverse the line

        // Search for matches in the current line
        while (regex_search(searchStart, paragraph.cend(), match, reg)) {
            if (match[0] == "do()") {
                isEnabled = true; // Enable multiplication
            } else if (match[0] == "don't()") {
                isEnabled = false; // Disable multiplication
            } else if (match[0].str().find("mul(") == 0 && isEnabled) {
                // If it's a valid mul() and enabled, extract the numbers and multiply
                int num1 = stoi(match[1].str());
                int num2 = stoi(match[2].str());
                total += multiply(num1, num2); // Perform multiplication and add to total
            }
            searchStart = match.suffix().first; // Move to the next match in the line
        }
    }

    file.close(); // Close the file after processing

    // Print the final result
    cout << "Sum of enabled multiplications: " << total << endl;
}

int main() {
    string filename = "input3.txt";
    sumMulWithConditions(filename); // Process the file and compute the result
    return 0;
}
