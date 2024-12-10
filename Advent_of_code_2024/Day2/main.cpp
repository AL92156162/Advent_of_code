// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int getSeparatorNumber(string str, char separator) {
    int separator_number = 0;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator) {
            separator_number += 1;
        }
    }
    return separator_number;
}

std::vector<int> customSplit(string str, char separator, int &size)
{

    std::vector<int> report(size);

    int startIndex = 0;
    int endIndex = 0;

    int j = 0;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator || i == str.size()) {
            report[j] = stoi(str.substr(startIndex, i));
            startIndex = i + 1;
            j += 1;
        }
    }

    return report;

}

bool CheckSafe(std::vector<int> report)
{
    bool isSafe = true;
    int direction = 1;
    if (report[0] > report[1])
    {
        direction = -1;
    }

    int delta;
    int i = 0;
    while (isSafe && i < report.size() - 1)
    {
        delta = report[i+1] - report[i];
        if (direction == 1 && delta <= 0)
        {
            isSafe = false;
        }
        if (direction == -1 && delta >= 0)
        {
            isSafe = false;
        }
        if (delta<-3 || delta>3)
        {
            isSafe = false;
        }
        i += 1;
    }

    return isSafe;
}

void getVariation(std::vector<int> report) {
    int isIncreasing = 0;
    int isDecreasing = 0;
    int isConstant = 0;

    for (int i=0; i < report.size() - 1; ++i)
    {

        if (report[i + 1] > report[i])
        {
            isIncreasing += 1;
        }
        else if (report[i + 1] < report[i])
        {
            isDecreasing += 1;
        }
        else
        {
            isConstant += 1;
        }

    }

    std::cout << isIncreasing << isDecreasing << isConstant << std::endl;
}

int main() {
    string line;
    ifstream myfile("test_input.txt");
    int number_levels = 0;
    int number_safe_report = 0;
    int number_safe_report_2 = 0;
    if (myfile.is_open())
    {

        while (getline(myfile, line)) {
                
            int splitSize = getSeparatorNumber(line, ' ')+1;
            int& splitSizeRef = splitSize;
            auto report = customSplit(line, ' ', splitSizeRef);
            
            // Part 1
            //bool isSafe = CheckSafe(report);

            //if (isSafe)
            //{
            //    number_safe_report += 1;
            //}

            // Part2
            getVariation(report);



        }

        myfile.close();
    }

    else cout << "Unable to open file";

    std::cout << number_safe_report << std::endl;
    std::cout << number_safe_report_2 << std::endl;

    return 0;
}