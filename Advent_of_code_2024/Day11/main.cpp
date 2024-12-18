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

void displayLookupTable(std::array<std::vector<int>, 100> lookup_table) {
    for (int i = 0; i < 100; ++i) {
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
    std::array<std::vector<int>, 100> lookup_table;
    displayLookupTable(lookup_table);
    unsigned int stone_number = 0;
    int lookup_table_size = 20;
    for (int k = 0; k < 100; ++k) {
        std::vector<unsigned long long> vec;
        vec.push_back(k);
        for (int i = 0; i < lookup_table_size; ++i) {
            std::vector<unsigned long long> new_vec;
            for (int j = 0; j < vec.size(); ++j) {
                int stone_number = 1;
                if (vec[j] == 0) {
                    new_vec.push_back(1);
                }
                else {
                    int ndigit = numDigits(vec[j]);
                    if (!(ndigit % 2)) {
                        std::vector<unsigned long long> new_stones = split(vec[j]);
                        int decim = pow(10, ndigit / 2);
                        new_vec.push_back(vec[j] / decim);
                        new_vec.push_back(vec[j] % decim);
                        stone_number = 2;
                    }
                    else {
                        new_vec.push_back(2024 * vec[j]);
                    }
                }
            }
            lookup_table[k].push_back(new_vec.size());
            vec = new_vec;
        }
    }
    
    displayLookupTable(lookup_table);

    int n_iter = 40;
    for (int k = 0; k < 100; ++k) {
        std::vector<unsigned long long> vec;
        vec.push_back(k);
        for (int i = 0; i < n_iter; ++i) {
            std::vector<unsigned long long> new_vec;
            for (int j = 0; j < vec.size(); ++j) {
                int stone_number = 1;

                if (i >= n_iter - lookup_table_size && vec[j]<100) {
                    //std::cout << i << std::endl;
                }

                if (vec[j] == 0) {
                    new_vec.push_back(1);
                }
                else {
                    int ndigit = numDigits(vec[j]);
                    if (!(ndigit % 2)) {
                        std::vector<unsigned long long> new_stones = split(vec[j]);
                        int decim = pow(10, ndigit / 2);
                        new_vec.push_back(vec[j] / decim);
                        new_vec.push_back(vec[j] % decim);
                        stone_number = 2;
                    }
                    else {
                        new_vec.push_back(2024 * vec[j]);
                    }
                }
            }
            lookup_table[k].push_back(new_vec.size());
            vec = new_vec;
        }
    }

    std::cout << stone_number << std::endl;
}