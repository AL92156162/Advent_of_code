// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <ranges>
#include <algorithm>
#include "header.hpp"

std::tuple<int, int> getDimension(std::string file_name) {
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


enum orientation {
    UP,RIGHT,DOWN,LEFT
};

orientation rotate(orientation o) {
    
    return static_cast<orientation>((static_cast<int>(o)+1)%4);
}

std::vector<int> move(std::vector<int> position, orientation o) {
    std::vector<int> new_pos = position;

    if (o == UP) {
        new_pos[1] -= 1;
    }
    else if (o == RIGHT) {
        new_pos[0] += 1;
    }
    else if (o == DOWN) {
        new_pos[1] += 1;
    }
    else if (o == LEFT) {
        new_pos[0] -= 1;
    }

    return new_pos;
}

char checkFront(Map map,  std::vector<int> position, orientation o) {
    std::vector<int> front_pos = move(position, o);
    char front_tile = map.getValue(front_pos[0], front_pos[1]);

    return front_tile;
}

std::vector<bool> getGuardPath(Map map, int max_iter, std::vector<int> guard_position, orientation o) {
    std::vector<bool> guard_path(map.width() * map.height());

    for (int i = 0; i < max_iter; ++i) {

        guard_path[guard_position[1] * map.width() + guard_position[0]] = true;

        guard_position = move(guard_position, o);

        if (checkFront(map, guard_position, o) == '#') {
            o = rotate(o);
        }

        if (checkFront(map, guard_position, o) == '0') {
            guard_path[guard_position[1] * map.width() + guard_position[0]] = true;
            guard_position = move(guard_position, o);
            break;
        }
    }
    return guard_path;

}

bool isGuardLooping(Map map, int max_iter, std::vector<int> guard_position, orientation o) {

    std::vector<bool> guard_path_up(map.width() * map.height());
    std::vector<bool> guard_path_right(map.width() * map.height());
    std::vector<bool> guard_path_down(map.width() * map.height());
    std::vector<bool> guard_path_left(map.width() * map.height());

    bool is_looping = false;
    int i;
    for (i = 0; i < max_iter; ++i) {

        if (o == UP) {
            if (!guard_path_up[guard_position[1] * map.width() + guard_position[0]]) {
                guard_path_up[guard_position[1] * map.width() + guard_position[0]] = true;
            }
            else {
                is_looping = true;
                break;
            }
        }
        if (o == RIGHT) {
            if (!guard_path_right[guard_position[1] * map.width() + guard_position[0]]) {
                guard_path_right[guard_position[1] * map.width() + guard_position[0]] = true;
            }
            else {
                is_looping = true;
                break;
            }
        }
        if (o == DOWN) {
            if (!guard_path_down[guard_position[1] * map.width() + guard_position[0]]) {
                guard_path_down[guard_position[1] * map.width() + guard_position[0]] = true;
            }
            else {
                is_looping = true;
                break;
            }
        }
        if (o == LEFT) {
            if (!guard_path_left[guard_position[1] * map.width() + guard_position[0]]) {
                guard_path_left[guard_position[1] * map.width() + guard_position[0]] = true;
            }
            else {
                is_looping = true;
                break;
            }
        }
        
        // Warning => Error if the guard is circled by walls
        while (checkFront(map, guard_position, o) == '#') {
            o = rotate(o);
        }

        if (checkFront(map, guard_position, o) == '0') {
            guard_position = move(guard_position, o);
            break;
        }

        guard_position = move(guard_position, o);

    }
    if (i == max_iter) {
        std::cout << "Max_iter reached" << std::endl;
    }
    return is_looping;
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

    Map map(width, height, vec);
    orientation o=UP;

    std::vector<int> guard_position(2);
    // Find starting point
    for (int i = 0; i < map.width(); ++i) {
        for (int j = 0; j < map.height(); ++j) {
            if (map.getValue(i, j) == '^') {
                guard_position[0] = i;
                guard_position[1] = j;
            }
        }
    }

    std::cout << "Initial position" << guard_position[0] << guard_position[1] << std::endl;

    int max_iter = map.width()*map.height();
    
    std::vector<bool> guard_path(map.width() * map.height());
    guard_path = getGuardPath(map, max_iter, guard_position, o);

    std::cout << "Guard position" << guard_position[0] << ";" << guard_position[1] << ";" << o << std::endl;
    std::cout << guard_path[guard_position[0] * map.width() + guard_position[1]] << std::endl;

    /*int npath = 0;
    for (int i = 0; i < map.width() * map.height(); ++i) {
        if (guard_path[i]) {
            npath += 1;
        }
    }*/
    int npath = std::ranges::count_if(guard_path, [](const bool x) { return x; });

    guard_path[guard_position[0] * map.width() + guard_position[1]] = false;

    int loop_count = 0;
    for (int i = 0; i < map.width(); ++i) {
        for (int j = 0; j < map.height(); ++j) {
            if (guard_path[j * map.width() + i]) {
                Map new_map = map;
                new_map.addWall(i, j);
                if (isGuardLooping(new_map, max_iter, guard_position, o)) {
                    //std::cout << i << ";" << j << std::endl;
                    loop_count += 1;
                }
            }
        }
    }


    std::cout << "Part1:" << npath << std::endl;
    std::cout << "Part2:" << loop_count << std::endl;
}