// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <regex>

int main() {
    std::string line;
    std::string file_name = "test2_input.txt";
    std::ifstream myfile(file_name);
    std::regex reg(R"((\d+))");

    std::vector<std::pair<int, int>> machines;

    int i = 0;
    if (myfile.is_open()) {

        while (getline(myfile, line)) {
            std::cout << line << std::endl;
            std::smatch m;

            std::pair<int, int> p;

            std::regex_search(line, m, reg);
            std::cout << m[1] << std::endl;
            std::string a = m[1];
            p.first = stoi(a);
            line = m.suffix();
            std::regex_search(line, m, reg);
            std::cout << m[1] << std::endl;
            //p.second = stoi(m[1]);
            machines.push_back(p);
            

            std::cout << p.first << ";" << p.second << std::endl;
        }
    }

    myfile.close();
    return 0;
}