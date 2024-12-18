// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include "header.hpp"

void displaySet(std::set<char> s){
    // Printing the elements of 
    // the set
    for (auto itr : s)
    {
        std::cout << itr << " ";
    }
}

void displayMap(Map map) {
    for (int i = 0; i < map.height(); ++i) {
        for (int j = 0; j < map.width(); ++j) {
            std::cout << map.getValue(j, i);
        }
        std::cout << std::endl;
    }
}

int getAntinodeCount1(Map map, std::set<char> frequency_vec, std::vector<char> value_vec, std::vector<int> x_vec,std::vector<int> y_vec) {
    // Find antinodes positions
    std::vector<int> x_antinode;
    std::vector<int> y_antinode;

    for (auto freq : frequency_vec) {
        int antenna1 = 0;
        int antenna2 = 0;

        for (int i = 0; i < value_vec.size() - 1; ++i) {
            if (value_vec[i] == freq) {
                for (int j = i + 1; j < value_vec.size(); ++j) {
                    if (value_vec[j] == freq) {
                        x_antinode.push_back(2 * x_vec[i] - x_vec[j]);
                        y_antinode.push_back(2 * y_vec[i] - y_vec[j]);
                        x_antinode.push_back(2 * x_vec[j] - x_vec[i]);
                        y_antinode.push_back(2 * y_vec[j] - y_vec[i]);
                    }
                }
            }
        }
    }

    std::cout << "Antinode number : " << x_antinode.size() << std::endl;

    // Remove duplicates
    for (int i = 0; i < x_antinode.size() - 1; ++i) {
        for (int j = i + 1; j < x_antinode.size(); ++j) {
            if (x_antinode[i] == x_antinode[j] && y_antinode[i] == y_antinode[j]) {
                x_antinode.erase(x_antinode.begin() + i);
                y_antinode.erase(y_antinode.begin() + i);
                i -= 1;
                break;
            }
        }
    }

    std::cout << "Antinode number without duplicates: " << x_antinode.size() << std::endl;

    // Count antinodes inside map
    int antinode_count = 0;
    for (int i = 0; i < x_antinode.size(); ++i) {

        if (x_antinode[i] >= 0 && x_antinode[i] < map.width() && y_antinode[i] >= 0 && y_antinode[i] < map.height()) {
            //std::cout << x_antinode[i] << ";" << y_antinode[i] << std::endl;
            antinode_count += 1;
        }
    }
    return antinode_count;
}

int getAntinodeCount2(Map map, std::set<char> frequency_vec, std::vector<char> value_vec, std::vector<int> x_vec, std::vector<int> y_vec) {
    // Find antinodes positions
    std::vector<int> x_antinode;
    std::vector<int> y_antinode;


    for (auto freq : frequency_vec) {
        int antenna1 = 0;
        int antenna2 = 0;

        for (int i = 0; i < value_vec.size(); ++i) {
            if (value_vec[i] == freq) {
                for (int j = i; j < value_vec.size(); ++j) {
                    if (value_vec[j] == freq) {

                        std::vector<int> antennas_vec = { x_vec[i] - x_vec[j], y_vec[i] - y_vec[j] };

                        int x = x_vec[i];
                        int y = y_vec[i];
                        //direction1
                        for (int k = 0; k < map.width() + map.height(); ++k) {
                            x += antennas_vec[0];
                            y += antennas_vec[1];
                            if (x < 0 || x > map.width() || y < 0 || y > map.height()) {
                                break;
                            }
                            x_antinode.push_back(x);
                            y_antinode.push_back(y);
                        }
                        //direction2
                        x = x_vec[j];
                        y = y_vec[j];
                        for (int k = 0; k < map.width() + map.height(); ++k) {
                            x -= antennas_vec[0];
                            y -= antennas_vec[1];
                            if (x < 0 || x > map.width() || y < 0 || y > map.height()) {
                                break;
                            }
                            x_antinode.push_back(x);
                            y_antinode.push_back(y);
                        }
                    }
                }
            }
        }
    }

    std::cout << "Antinode number : " << x_antinode.size() << std::endl;

    // Remove duplicates
    for (int i = 0; i < x_antinode.size() - 1; ++i) {
        for (int j = i + 1; j < x_antinode.size(); ++j) {
            if (x_antinode[i] == x_antinode[j] && y_antinode[i] == y_antinode[j]) {
                x_antinode.erase(x_antinode.begin() + i);
                y_antinode.erase(y_antinode.begin() + i);
                i -= 1;
                break;
            }
        }
    }

    //Display map with antinode
    Map map2 = map;
    for (int i = 0; i < x_antinode.size(); ++i) {
        map2.add_antinode(x_antinode[i], y_antinode[i]);
    }
    displayMap(map2);

    std::cout << "Antinode number without duplicates: " << x_antinode.size() << std::endl;

    // Count antinodes inside map
    int antinode_count = 0;
    for (int i = 0; i < x_antinode.size(); ++i) {

        if (x_antinode[i] >= 0 && x_antinode[i] < map.width() && y_antinode[i] >= 0 && y_antinode[i] < map.height()) {
            //std::cout << x_antinode[i] << ";" << y_antinode[i] << std::endl;
            antinode_count += 1;
        }
    }
    return antinode_count;
}

int main() {

    std::string line;
    std::string file_name = "input.txt";
    std::tuple<int, int> dim = getDimension(file_name);
    int width = std::get<0>(dim);
    int height = std::get<1>(dim);
    std::cout << width << ";" << height << std::endl;

    std::ifstream myfile(file_name);
    std::vector<char> vec(height * width);

    if (myfile.is_open())
    {
        for (int i = 0; i < height; ++i) {
            getline(myfile, line);
            for (int j = 0; j < width; ++j) {
                vec[i * width + j] = line[j];
            }
        }
    }
    myfile.close();

    Map map(width, height, vec);
    displayMap(map);

    // Find antennas positions
    std::set<char> frequency_vec;
    std::vector<char> value_vec;
    std::vector<int> x_vec;
    std::vector<int> y_vec;

    for (int i = 0; i < map.width(); ++i) {
        for (int j = 0; j < map.height(); ++j) {
            char val = map.getValue(i, j);
            if ( val != '.') {
                value_vec.push_back(val);
                x_vec.push_back(i);
                y_vec.push_back(j);
                frequency_vec.insert(val);
            }
        }
    }
    //displaySet(frequency_vec);

    //std::cout << "Part1 : " << getAntinodeCount1(map, frequency_vec, value_vec, x_vec, y_vec) << std::endl;
    std::cout << "Part2 : " << getAntinodeCount2(map, frequency_vec, value_vec, x_vec, y_vec) << std::endl;
}