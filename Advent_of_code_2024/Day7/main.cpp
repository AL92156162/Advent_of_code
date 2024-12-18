// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <bitset>

long long concatenate(long long a, long long b) {
    std::string stra = std::to_string(a);
    std::string strb = std::to_string(b);

    std::string str_concat = stra + strb;

    return stoll(str_concat);
}

int main() {
    std::string line;
    std::ifstream myfile("input.txt");
    std::regex reg(R"((\d+))");
    long long total_calibration_result = 0;
    long long total_calibration_result_2 = 0;
    
    // Part1
    if (myfile.is_open()) {
        while (getline(myfile, line)) {

            std::vector<long long> values;
            std::regex_token_iterator<std::string::iterator> rend;
            std::regex_token_iterator<std::string::iterator> a(line.begin(), line.end(), reg);

            while (a != rend) {
                std::string str = *a++;
                values.push_back(stoll(str));
            }
            int n_operation = values.size() - 2;

            // Part1
            /*std::vector<bool> operation_vec(n_operation);
            bool calculus_is_valid = false;

            for (int i = 0; i < pow(2,n_operation); ++i) {
                long long calculated_value = values[1];
                std::bitset<16> b(i);
                
                for (int j = 0; j < n_operation; ++j) {
                    
                    if (b[j] == 0) {
                        calculated_value += values[j + 2];
                    }
                    if (b[j] == 1) {
                        calculated_value *= values[j + 2];
                    }
                }
                if (calculated_value == values[0]) {
                    calculus_is_valid = true;
                    break;
                }
            }
            if (calculus_is_valid) {
                total_calibration_result += values[0];
            }*/

            // Part2
            std::vector<int> operation_vec(n_operation);
            bool calculus_is_valid = false;

            for (int i = 0; i < pow(3, n_operation); ++i) {
                int num = i;
                for (int j = n_operation - 1; j >= 0; --j) {
                    operation_vec[j] = (int)num / pow(3,j);
                    num = num % (int)pow(3, j);
                    //std::cout << j << ";" << operation_vec[j] << std::endl;
                }

                long long calculated_value = values[1];
                for (int j = 0; j < n_operation; ++j) {
                    
                    if (operation_vec[j] == 0) {
                        calculated_value += values[j + 2];
                    }
                    if (operation_vec[j] == 1) {
                        calculated_value *= values[j + 2];
                    }
                    if (operation_vec[j] == 2) {
                        calculated_value = concatenate(calculated_value,values[j + 2]);
                    }
                }
                //std::cout << calculated_value << std::endl;
                if (calculated_value == values[0]) {
                    calculus_is_valid = true;
                    break;
                }
                
            }
            if (calculus_is_valid) {
                total_calibration_result_2 += values[0];
            }

            
        }
    }

    std::cout << "Part1: " << total_calibration_result << std::endl;
    std::cout << "Part2: " << total_calibration_result_2 << std::endl;
}