// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "header.hpp"

void DisplayVec(std::vector<char> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
    }
}

Map RobotMovement(Map map, char move) {
    std::pair<int, int> robot_pos = map.getRobotPosition();
    std::pair<int, int> mvec = { 0,0 };

    if (move == '^') {
        mvec.second = -1;
    }
    if (move == '>') {
        mvec.first = 1;
    }
    if (move == 'v') {
        mvec.second = 1;
    }
    if (move == '<') {
        mvec.first = -1;
    }

    char next_val = map.getValue(robot_pos.first + mvec.first, robot_pos.second + mvec.second);
    if (next_val == '.') {
        map.setValue(robot_pos.first, robot_pos.second, '.');
        map.setValue(robot_pos.first + mvec.first, robot_pos.second + mvec.second, '@');
    }
    else if (next_val == 'O') {
        int push_attempt = 0;
        int i = 2;
        while (push_attempt == 0) {
            char next_val2 = map.getValue(robot_pos.first + i * mvec.first, robot_pos.second + i * mvec.second);

            if (next_val2 == '#') {
                push_attempt = -1;
            }
            else if (next_val2 == '.') {
                push_attempt = 1;
            }
            else {
                i += 1;
            }
        }
        
        if (push_attempt == 1) {
            for (int j = i - 1; j >= 0; --j) {
                char next_val2 = map.getValue(robot_pos.first + j * mvec.first, robot_pos.second + j * mvec.second);
                map.setValue(robot_pos.first + j * mvec.first, robot_pos.second + j * mvec.second, '.');
                map.setValue(robot_pos.first + (j+1) * mvec.first, robot_pos.second + (j+1) * mvec.second, next_val2);
            }
        }
        
    }
    

    return map;

}

void MoveTile(Map& map, int x, int y, std::pair<int, int> mvec) {
    char val = map.getValue(x, y);
    map.setValue(x, y, '.');
    map.setValue(x + mvec.first, y + mvec.second, val);
}

bool CheckHorizontalBoxMove(Map& map, int x, int y, std::pair<int, int> mvec) {
    bool possible_push = false;
    int push_attempt = false;
    int i = 1;
    while (push_attempt == 0) {
        char next_val2 = map.getValue(x + i * mvec.first, y + i * mvec.second);
        if (next_val2 == '#') {
            push_attempt = -1;
        }
        else if (next_val2 == '.') {
            push_attempt = 1;
        }
        else {
            i += 1;
        }
    }
    if (push_attempt == 1) {
        possible_push = true;
    }
    return possible_push;
}

void HorizontalPush(Map& map, int x, int y, std::pair<int, int> mvec) {
    char next_val = map.getValue(x + mvec.first, y + mvec.second);

    if (next_val == '.') {
        MoveTile(map, x, y, mvec);
    }
    else {
        HorizontalPush(map, x + mvec.first, y, mvec);
        MoveTile(map, x, y, mvec);
    }

}

bool CheckVerticalBoxMove(Map& map, int x, int y, std::pair<int, int> mvec) {
    bool box_moved = false;
    char val = map.getValue(x,y);
    int box_dir;
    if (val == '[') {
        box_dir = 1;
    }
    else {
        box_dir = -1;
    }

    char next_val1 = map.getValue(x + mvec.first, y + mvec.second);
    char next_val2 = map.getValue(x + box_dir + mvec.first, y + mvec.second);

    if (next_val1 == '.' && next_val2 == '.') {
        box_moved = true;
    }
    else if (next_val1 == '#' || next_val2 == '#') {
        box_moved = false;
    }
    else {
        bool c1 = true;
        bool c2 = true;
        if (next_val1 == '[' || next_val1 == ']') {
            c1 = CheckVerticalBoxMove(map, x + mvec.first, y + mvec.second, mvec);
        }
        if (next_val2 == '[' || next_val2 == ']') {
            c2 = CheckVerticalBoxMove(map, x + box_dir + mvec.first, y + mvec.second, mvec);
        }
        box_moved = c1 && c2;
    }
    return box_moved;
}

void VerticalPush(Map& map, int x, int y, std::pair<int, int> mvec) {
    
    char current_val1 = map.getValue(x, y);
    int box_dir;
    if (current_val1 == '[') {
        box_dir = 1;
    }
    else {
        box_dir = -1;
    }

    char next_val1 = map.getValue(x + mvec.first, y + mvec.second);
    
    if (next_val1 == '.' ) {
        MoveTile(map, x, y, mvec);
    }
    else {
        VerticalPush(map, x, y + mvec.second, mvec);
        MoveTile(map, x, y, mvec);
    }

    char next_val2 = map.getValue(x + box_dir + mvec.first, y + mvec.second);

    if (next_val2 == '.') {
        MoveTile(map, x + box_dir, y, mvec);
    }
    else {
        VerticalPush(map, x + box_dir, y + mvec.second, mvec);
        MoveTile(map, x + box_dir, y, mvec);
    }
}

Map RobotMovement2(Map map, char move) {
    std::pair<int, int> robot_pos = map.getRobotPosition();
    std::pair<int, int> mvec = { 0,0 };

    if (move == '^') {
        mvec.second = -1;
    }
    if (move == '>') {
        mvec.first = 1;
    }
    if (move == 'v') {
        mvec.second = 1;
    }
    if (move == '<') {
        mvec.first = -1;
    }

    char next_val = map.getValue(robot_pos.first + mvec.first, robot_pos.second + mvec.second);
    if (next_val == '.') {
        map.setValue(robot_pos.first, robot_pos.second, '.');
        map.setValue(robot_pos.first + mvec.first, robot_pos.second + mvec.second, '@');
    }

    else if (next_val == '[' || next_val == ']') {
        Map& map_ref = map;
        bool bm = false;
        if (move == '^' || move == 'v') {
            bm = CheckVerticalBoxMove(map_ref, robot_pos.first + mvec.first, robot_pos.second + mvec.second, mvec);
            
            if (bm) {
                VerticalPush(map_ref, robot_pos.first + mvec.first, robot_pos.second + mvec.second, mvec);
                MoveTile(map_ref, robot_pos.first, robot_pos.second, mvec);
            }
        }
        else {
            bm = CheckHorizontalBoxMove(map_ref, robot_pos.first + mvec.first, robot_pos.second + mvec.second, mvec);
            if (bm) {
                HorizontalPush(map_ref, robot_pos.first, robot_pos.second, mvec);
            }
        }
    }


    return map;

}

int main() {

    std::string line;
    std::string file_name = "input.txt";
    std::ifstream myfile(file_name);

    int width = 0;
    int height = 0;
    std::vector<char> mvec;
    std::vector<char> moves;
    bool is_map = true;
    if (myfile.is_open())
    {
        while (getline(myfile, line)) {
            if (line.empty()) {
                is_map = false;
            }
            if (is_map) {
                for (int i = 0; i < line.size(); ++i) {
                    mvec.push_back(line[i]);
                }
                height += 1;
                width = line.size();
            }
            else {
                for (int i = 0; i < line.size(); ++i) {
                    moves.push_back(line[i]);
                }
            }
        }
    }
    myfile.close();


    Map map(width, height, mvec);
    map.display();

    //DisplayVec(moves);
    //std::cout << std::endl;

    // Part1

    //std::pair<int, int> robot_pos = map.getRobotPosition();
    //std::cout << robot_pos.first << ";" << robot_pos.second << std::endl;

    //for (int i = 0; i < moves.size(); ++i) {
    //    //std::cout << moves[i] << std::endl;
    //    map = RobotMovement(map, moves[i]);
    //    //map.display();
    //}
    //map.display();

    //int GPS_score = 0;
    //for (int i = 0; i < map.width(); ++i) {
    //    for (int j = 0; j < map.height(); ++j) {
    //        if (map.getValue(i, j) == 'O') {
    //            GPS_score += 100 * j + i;
    //        }
    //    }
    //}

    //std::cout << GPS_score << std::endl;


    // Part2
    Map map2(width*2, height);

    for (int i = 0; i < map.width(); ++i) {
        for (int j = 0; j < map.height(); ++j) {
            if (map.getValue(i, j) == '#') {
                map2.setValue(2 * i, j, '#');
                map2.setValue(2 * i + 1, j, '#');
            }

            else if (map.getValue(i, j) == 'O') {
                map2.setValue(2 * i, j, '[');
                map2.setValue(2 * i + 1, j, ']');
            }
            else if (map.getValue(i, j) == '@') {
                map2.setValue(2 * i, j, '@');
            }
        }
    }

    map2.display();

    for (int i = 0; i < moves.size(); ++i) {
        //std::cout << i << moves[i] << ";" << std::endl;
        map2 = RobotMovement2(map2, moves[i]);
        //map2.display();
    }

    map2.display();

    int GPS_score2 = 0;
    for (int i = 0; i < map2.width(); ++i) {
        for (int j = 0; j < map2.height(); ++j) {
            if (map2.getValue(i, j) == '[') {
                GPS_score2 += 100 * j + i;
            }
        }
    }

    std::cout << GPS_score2 << std::endl;

}