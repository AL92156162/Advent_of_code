// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include "Header.hpp"


std::tuple<int,int> getDimension(std::string file_name) {
    std::string line;
    std::ifstream myfile(file_name);

    int width = 0;
    int length = 1;

    if (myfile.is_open())
    {
        getline(myfile, line);
        width = line.size();
        while (getline(myfile, line)) {
            length += 1;
        }

        
    }
    myfile.close();
    return std::make_tuple(width, length);
    
}

bool isXMAS(std::vector<char> vec) {
    std::string target = "XMAS";
    bool res = true;
    for (int k = 0; k < 4; ++k) {
        if (vec[k] != target[k]) {
            res=false;
            break;
        }
    }
    return res;
}

std::vector<char> getSlidingWindow(const std::vector<char> vec, int x, int y, int length, int width) {
    std::vector<char> svec(9);
    int k = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            svec[k] = vec[(y+i) * width + (x+j)];
            k += 1;
        }
    }
    return svec;
}

bool findXMAS(const std::vector<char> vec) {
    bool x_mas = false;
    if (vec[4] == 'A') {
        if (vec[0] == 'M' && vec[2] == 'M' && vec[6] == 'S' && vec[8] == 'S') {
            x_mas = true;
        }
        if (vec[0] == 'M' && vec[2] == 'S' && vec[6] == 'M' && vec[8] == 'S') {
            x_mas = true;
        }
        if (vec[0] == 'S' && vec[2] == 'M' && vec[6] == 'S' && vec[8] == 'M') {
            x_mas = true;
        }
        if (vec[0] == 'S' && vec[2] == 'S' && vec[6] == 'M' && vec[8] == 'M') {
            x_mas = true;
        }
    }

    return x_mas;
}

int main() {
    
    std::string line;
    std::string file_name= "input.txt";
    std::tuple<int, int> dim = getDimension(file_name);
    int width = std::get<0>(dim);
    int length = std::get<1>(dim);
    std::cout << width << ";" << length << std::endl;

    std::ifstream myfile(file_name);
    std::vector<char> vec(length*width);

    int XMAS_occur = 0;

    if (myfile.is_open())
    {

        
        for (int i = 0; i < length; ++i) {
            getline(myfile, line);
            for (int j = 0; j < width; ++j) {
                vec[i * width + j] = line[j];
            }
            
        }

        // Part1
        /*for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {

                std::vector<char> vec1 = getVec1(vec, i, j, length, width);
                std::vector<char> vec2 = getVec2(vec, i, j, length, width);
                std::vector<char> vec3 = getVec3(vec, i, j, length, width);
                std::vector<char> vec4 = getVec4(vec, i, j, length, width);
                std::vector<char> vec5 = getVec5(vec, i, j, length, width);
                std::vector<char> vec6 = getVec6(vec, i, j, length, width);
                std::vector<char> vec7 = getVec7(vec, i, j, length, width);
                std::vector<char> vec8 = getVec8(vec, i, j, length, width);

                int occur = static_cast<int>(isXMAS(vec1)) +
                    static_cast<int>(isXMAS(vec2)) +
                    static_cast<int>(isXMAS(vec3)) +
                    static_cast<int>(isXMAS(vec4)) +
                    static_cast<int>(isXMAS(vec5)) +
                    static_cast<int>(isXMAS(vec6)) +
                    static_cast<int>(isXMAS(vec7)) +
                    static_cast<int>(isXMAS(vec8));

                XMAS_occur += occur;

                if (occur > 0) {
                    std::cout << i << ";" << j << ";" << occur << std::endl;
                }
            }
        }*/
        

        //Part2
        for (int i = 0; i < length-2; ++i) {
            for (int j = 0; j < width-2; ++j) {
                std::vector<char> svec = getSlidingWindow(vec, i, j, length, width);

                if (findXMAS(svec)) {
                    XMAS_occur += 1;
                }
                
            }
        }


    }

    myfile.close();
    std::cout << XMAS_occur << std::endl;


    
}