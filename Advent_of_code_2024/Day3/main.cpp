// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

bool isNumber(const std::string& s) {
    bool is_number = true;
    for (int i = 0; i < s.size(); ++i) {
        if (not std::isdigit(s[i])) {
            is_number = false;
        }
    }
    return is_number;
}

int main() {
    string line;
    ifstream myfile("test_input.txt");
    int number_levels = 0;
    int number_safe_report = 0;
    int number_safe_report_2 = 0;
    if (myfile.is_open())
    {
        getline(myfile, line);

        std::cout << line.size() << std::endl;

        /*for (int i = 0; i < line.size(); ++i) {
            
            string seq = line.substr(i, 4);
            
            if (seq == "mul(") {
                std::cout << seq << std::endl;
            }

            string num1 = line.substr(i + 4,1);
            std::cout << isNumber(num1) << std::endl;
            
        }*/

        if (regex_match(line, regex("mul")))
            cout << "string:literal => matched\n";



        myfile.close();
    }
}