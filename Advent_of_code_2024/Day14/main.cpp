// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <regex>
#include "header.hpp"

void DisplayVec(std::vector<std::pair<int, int>> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i].first << ";" << vec[i].second << std::endl;
    }
}

bool checkXmaxTree(Map map, int n) {
    bool is_tree = false;
    for (int j = 0; j < map.height(); ++j) {
        for (int i = 0; i < map.width(); ++i) {
            if (map.getValue(i, j) > 0) {
                bool valid_stage = true;
                for (int k = 1; k < n; ++k) {
                    for (int l = -k; l <= k; ++l) {
                        if (map.getValue(i + l, j + k) <= 0) {
                            valid_stage = false;
                            break;
                        }
                    }
                    if (!valid_stage) {
                        break;
                    }
                }
                if (valid_stage) {
                    is_tree = true;
                    break;
                }
            }
        }
        if (is_tree) {
            break;
        }
    }
    return is_tree;
}

int main() {

    std::string line;
    std::string file_name = "input.txt";
    std::ifstream myfile(file_name);

    std::regex reg(R"((-?\d+))");
    std::smatch matches;

    std::vector<std::pair<int, int>> pos_vec;
    std::vector<std::pair<int, int>> vel_vec;


    if (myfile.is_open())
    {
        while (getline(myfile, line)) {
            std::vector<int> v;
            while (std::regex_search(line, matches, reg)) {
                v.push_back(stoi(matches[1]));
                line = matches.suffix().str();
            }

            std::pair<int, int> pos = { v[0], v[1] };
            std::pair<int, int> vel = { v[2], v[3] };

            pos_vec.push_back(pos);
            vel_vec.push_back(vel);
        }        
    }
    myfile.close();
    
    //Part1

    // Creating map
    int width = 101;
    int height = 103;
    std::vector<int> map_vec(width*height);
    for (int i = 0; i < width * height; ++i) {
        map_vec[i] = 0;
    }
    Map map(width, height, map_vec);

    for (int i = 0; i < pos_vec.size(); ++i) {
        int current_val = map.getValue(pos_vec[i].first, pos_vec[i].second);
        map.setValue(pos_vec[i].first, pos_vec[i].second, current_val + 1);
    }

    //map.display();
    //std::cout << std::endl;

    /*int n_iter = 100;

    for (int i = 0; i < n_iter; ++i) {

        for (int j = 0; j < pos_vec.size(); ++j) {
            std::pair<int, int> initial_pos = pos_vec[j];
            int initial_val = map.getValue(initial_pos.first, initial_pos.second);
            map.setValue(initial_pos.first, initial_pos.second, initial_val - 1);

            std::pair<int, int> new_pos = initial_pos;
            new_pos.first += vel_vec[j].first;
            new_pos.second += vel_vec[j].second;

            if (new_pos.first < 0) {
                new_pos.first += map.width();
            }
            else if (new_pos.first >= map.width()) {
                new_pos.first -= map.width();
            }

            if (new_pos.second < 0) {
                new_pos.second += map.height();
            }
            else if (new_pos.second >= map.height()) {
                new_pos.second -= map.height();
            }

            int current_val = map.getValue(new_pos.first, new_pos.second);
            map.setValue(new_pos.first, new_pos.second, current_val + 1);
            pos_vec[j] = new_pos;
        }

        map.display();
        std::cout << std::endl;
    }

    map.display();
    std::cout << std::endl;
    
    std::vector<int> qscore(4);
    for (int i = 0; i < map.width(); ++i) {
        for (int j = 0; j < map.height(); ++j) {
            if (i < map.width() / 2 && j < map.height() / 2) {
                qscore[0] += map.getValue(i, j);
            }
            if (i < map.width() / 2 && j > map.height() / 2) {
                qscore[1] += map.getValue(i, j);
            }
            if (i > map.width() / 2 && j < map.height() / 2) {
                qscore[2] += map.getValue(i, j);
            }
            if (i > map.width() / 2 && j > map.height() / 2) {
                qscore[3] += map.getValue(i, j);
            }
        }
    }

    std::cout << qscore[0] << ';' << qscore[1] << ';' << qscore[2] << ';' << qscore[3] << ';' << std::endl;
    int safety_factor = qscore[0] * qscore[1] * qscore[2] * qscore[3];

    std::cout << safety_factor << std::endl;*/


    // Tree detection test
    /*int width = 7;
    int height = 4;
    std::vector<int> mvec(width* height);
    for (int i = 0; i < width * height; ++i) {
        mvec[i] = 0;
    }
    Map tree_map(width, height, mvec);

    tree_map.setValue(4, 0, 1);

    tree_map.setValue(3, 1, 1);
    tree_map.setValue(4, 1, 1);
    tree_map.setValue(5, 1, 1);

    tree_map.setValue(2, 2, 1);
    tree_map.setValue(3, 2, 1);
    tree_map.setValue(4, 2, 1);
    tree_map.setValue(5, 2, 1);
    tree_map.setValue(6, 2, 1);

    tree_map.display();

    
    bool is_tree = checkXmaxTree(tree_map, 4);

    std::cout << is_tree << std::endl;*/


    int n_iter = 10000;
    bool is_tree;
    int i;
    for (i = 0; i < n_iter; ++i) {

        for (int j = 0; j < pos_vec.size(); ++j) {
            std::pair<int, int> initial_pos = pos_vec[j];
            int initial_val = map.getValue(initial_pos.first, initial_pos.second);
            map.setValue(initial_pos.first, initial_pos.second, initial_val - 1);

            std::pair<int, int> new_pos = initial_pos;
            new_pos.first += vel_vec[j].first;
            new_pos.second += vel_vec[j].second;

            if (new_pos.first < 0) {
                new_pos.first += map.width();
            }
            else if (new_pos.first >= map.width()) {
                new_pos.first -= map.width();
            }

            if (new_pos.second < 0) {
                new_pos.second += map.height();
            }
            else if (new_pos.second >= map.height()) {
                new_pos.second -= map.height();
            }

            int current_val = map.getValue(new_pos.first, new_pos.second);
            map.setValue(new_pos.first, new_pos.second, current_val + 1);
            pos_vec[j] = new_pos;
        }

        is_tree = checkXmaxTree(map, 4);
        if (is_tree) {
            break;
        }
    }

    map.display();
    std::cout << i << std::endl;
}