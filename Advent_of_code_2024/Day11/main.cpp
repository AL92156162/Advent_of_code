// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <array>
#include "header.hpp"


std::vector<unsigned long long> getInputVec(std::string file_name) {
    std::string line;
    std::ifstream myfile(file_name);
    if (myfile.is_open()) {
        getline(myfile, line);
    }
    myfile.close();

    std::cout << line << std::endl;

    std::smatch matches;
    std::regex reg(R"((\d+))");

    std::vector<unsigned long long> vec;

    while (std::regex_search(line, matches, reg)) {
        vec.push_back(stoll(matches[0]));
        line = matches.suffix().str();
    }
    return vec;
}

void displayVector(std::vector<unsigned long long> vec) {
    // Printing the elements of 
    // the set
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == -1) {
            std::cout << ".";
        }
        else {
            std::cout << vec[i] << " ";
        }
    }
    std::cout << std::endl;
}

void displayLookupTable(std::array<std::vector<int>, 1000> lookup_table) {
    for (int i = 0; i < 1000; ++i) {
        std::vector<int> vec = lookup_table[i];
        if (vec.size() > 0) {
            std::cout << i << ":";
            for (int j = 0; j < vec.size(); ++j) {
                std::cout << vec[j] << ";";
            }
            std::cout << std::endl;
        }
        
    }
}

std::vector<unsigned long long> split(const unsigned long long num) {
    std::vector<unsigned long long> res(2);
    std::string num_str = std::to_string(num);

    //std::cout << num_str << ";" << num_str.substr(0, num_str.size() / 2) << std::endl;
    //std::cout << num_str.substr(num_str.size() / 2, num_str.size()) << std::endl;

    res[0] = std::stoll(num_str.substr(0, num_str.size() / 2));
    res[1] = std::stoll(num_str.substr(num_str.size() / 2, num_str.size()));
    
    return res;
}

//std::vector<unsigned long long> blink(unsigned long long num, int idx, int max_iter, unsigned long long& total_stone, std::array<std::vector<int>, 10>& lookup_table) {
//    idx += 1;
//    std::vector<unsigned long long> new_vec;
//    if (idx >= max_iter) {
//        total_stone += 1;
//        //std::cout << num << ";";
//        new_vec.push_back(num);
//        return new_vec;
//    }
//    else {
//        
//        if (num == 0) {
//            new_vec.push_back(1);
//        }
//        else {
//            int ndigit = numDigits(num);
//            if (!(ndigit % 2)) {
//                std::vector<unsigned long long> new_stones = split(num);
//                int decim = pow(10, ndigit / 2);
//                new_vec.push_back(num / decim);
//                new_vec.push_back(num % decim);
//            }
//            else {
//                new_vec.push_back(2024 * num);
//            }
//        }
//        for (int j = 0; j < new_vec.size(); ++j) {
//            blink(new_vec[j], idx, max_iter, total_stone, lookup_table);
//        }
//    }
//}

std::vector<unsigned long long> blink(unsigned long long num, int idx, std::array<std::vector<int>, 1000>& lookup_table) {
    std::vector<unsigned long long> new_vec;

    if (num < 1000 && lookup_table[num][idx] != 0) {
        new_vec.resize(lookup_table[num][idx]);
        return new_vec;
    }
    else {
        
        if (idx <= 0) {
            new_vec.push_back(num);
            return new_vec;
        }
        else if (num == 0) {
            new_vec = blink(1, idx - 1, lookup_table);
        }

        else {
            int ndigit = numDigits(num);
            if (!(ndigit % 2)) {
                std::vector<unsigned long long> new_stones = split(num);
                int decim = pow(10, ndigit / 2);
                unsigned long long num_left = num / decim;
                unsigned long long num_right = num % decim;

                std::vector<unsigned long long> left_vec = blink(num_left, idx - 1, lookup_table);
                std::vector<unsigned long long> right_vec = blink(num_right, idx - 1, lookup_table);
                new_vec = left_vec;
                new_vec.insert(new_vec.end(), right_vec.begin(), right_vec.end());

            }
            else {
                new_vec = blink(num * 2024, idx - 1, lookup_table);
            }
        }
        if (num < 1000) {
            lookup_table[num][idx] = new_vec.size();
        }
    }

    return new_vec;
}

int main() {

    std::string file_name = "test2_input.txt";
    std::vector<unsigned long long> vec = getInputVec(file_name);

    displayVector(vec);
    // Part 1
    /*int n_iter = 25;

    for (int i = 0; i < n_iter; ++i) {
        std::vector<unsigned long long> new_vec;
        for (int j = 0; j < vec.size(); ++j) {
            if (vec[j] == 0) {
                new_vec.push_back(1);
            }
            else {
                int ndigit = numDigits(vec[j]);
                if (!(ndigit % 2)) {
                    std::vector<unsigned long long> new_stones = split(vec[j]);
                    int decim = pow(10, ndigit/2);
                    new_vec.push_back(vec[j] / decim);
                    new_vec.push_back(vec[j] % decim);
                }
                else {
                    new_vec.push_back(2024 * vec[j]);
                }
            }    
        }
        vec = new_vec;
        std::cout << i << ";";
    }

    std::cout << "Result : " << vec.size() << std::endl;*/

    // Part 2
    

    int max_iter = 7;

    int lookup_table_size = 1000;
    std::array<std::vector<int>, 1000> lookup_table;
    std::vector<int> init_vec(max_iter+1);
    for (int i = 0; i < lookup_table.size(); ++i) {
        lookup_table[i] = init_vec;
    }

    std::array<std::vector<int>, 1000>& lookup_table_ref = lookup_table;

    unsigned long long total_stone = 0;
    for (int i = 0; i < vec.size(); ++i) {
        std::vector<unsigned long long> res = blink(vec[i], max_iter, lookup_table_ref);
        total_stone += res.size();
        std::cout << vec[i] << ";";
    }
    std::cout << std::endl;
    //std::vector<unsigned long long> vec1;
    //std::vector<unsigned long long> vec2;
    //unsigned long long num = 125;
    //vec1 = blink(num, max_iter, lookup_table_ref);
    //num = 17;
    //vec2 = blink(num, max_iter, lookup_table_ref);

    displayLookupTable(lookup_table_ref);

    std::cout << total_stone << std::endl;

}