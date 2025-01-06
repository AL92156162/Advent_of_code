// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <regex>

int main() {
    std::string line;
    std::string file_name = "input.txt";
    std::ifstream myfile(file_name);
    std::regex reg(R"((\d+))");

    std::vector<std::pair<unsigned long long, unsigned long long>> machines;
    int i = 0;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (!line.empty()) {
                std::smatch m;
                std::pair<unsigned long long, unsigned long long> p;
                std::regex_search(line, m, reg);
                p.first = stoll(m[1]);
                line = m.suffix();
                std::regex_search(line, m, reg);
                p.second = stoll(m[1]);
                //Part2 correction
                if (i % 3 == 2) {
                    p.first += 10000000000000;
                    p.second += 10000000000000;
                }
                /*std::cout << p.first << ';' << p.second << std::endl;*/
                machines.push_back(p);
                i += 1;
            }
        }
    }
    myfile.close();

    // Part1
    //int n_machine = machines.size() / 3;
    //int prize = 0;
    //for (int i = 0; i < n_machine; ++i) {
    //    std::pair<long, long> b1 = machines[i * 3];
    //    std::pair<long, long> b2 = machines[i * 3 + 1];
    //    std::pair<long, long> goal = machines[i * 3 + 2];
    //    int n1=0;
    //    int n2=0;
    //    for (int j = 0; j <= 100; ++j) {
    //        for (int k = 0; k <= 100; ++k) {
    //            if (b1.first * j + b2.first * k == goal.first && b1.second * j + b2.second * k == goal.second) {
    //                n1 = j;
    //                n2 = k;
    //            }
    //        }
    //    }
    //    prize += n1 * 3 + n2 * 1;
    //    //std::cout << n1 << ';' << n2 << std::endl;
    //}

    //std::cout << prize << std::endl;


    //Part2
    int n_machine = machines.size() / 3;
    unsigned long long prize = 0;
    for (int i = 0; i < n_machine; ++i) {
        std::pair<unsigned long long, unsigned long long> b1 = machines[i * 3];
        std::pair<unsigned long long, unsigned long long> b2 = machines[i * 3 + 1];
        std::pair<unsigned long long, unsigned long long> goal = machines[i * 3 + 2];

        //std::cout << b1.first << ';' << b1.second << "/";
        //std::cout << b2.first << ';' << b2.second << "/";
        //std::cout << goal.first << ';' << goal.second << std::endl;

        long long C = b1.first * goal.second - b1.second * goal.first;
        long long D = b1.first * b2.second - b1.second * b2.first;
        long long E = b2.second * goal.first - b2.first * goal.second;

        //std::cout << C << ';' << D << ';' << E << std::endl;

        if (D != 0 && b1.first != 0 && C % D == 0) {
            unsigned long long beta = C / D;
            unsigned long long alpha = E / D;
            //unsigned long long alpha = (goal.first - b2.first * beta) / b1.first;

            //std::cout << alpha << ';' << beta << std::endl;

            if (alpha > 0 && beta > 0) {
                prize += alpha * 3 + beta * 1;
            }
            
        }
    }
    std::cout << prize << std::endl;
    return 0;
}