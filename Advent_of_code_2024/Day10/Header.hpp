#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

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

class Map {
    unsigned int m_width;
    unsigned int m_height;
    std::vector<char> m_vec;

public:
    Map() :
        m_width(0), m_height(0), m_vec(m_height* m_width)
    {
        //do nothing
    }

    Map(const unsigned int width, const unsigned int height, std::vector<char> vec) :
        m_width(width), m_height(height), m_vec(vec)
    {
        if (m_vec.size() != m_width * m_height) {
            throw std::logic_error("Wrong vec size");
        }
    }

    unsigned int width() const {
        return m_width;
    }

    unsigned int height() const {
        return m_height;
    }

    std::vector<char> const& vec() const {
        return m_vec;
    }

    std::vector<char> & vec() {
        return m_vec;
    }

    char getValue(int x, int y) {

        if (x>=0 && x < m_width && y>=0 && y < m_height) {
            return m_vec[y * m_width + x];
        }
        else {
            return '-1';
        }
    }


    void display() {
        for (int i = 0; i < m_height; ++i) {
            for (int j = 0; j < m_width; ++j) {
                std::cout << getValue(j, i);
            }
            std::cout << std::endl;
        }
    }
};


class Node {
    unsigned int m_x;
    unsigned int m_y;
    char m_val;
    bool m_is_fork;
    std::vector<bool> m_neighbor_vec;

public:
    Node() :
        m_x(0), m_y(0), m_val('-1'), m_is_fork(false), m_neighbor_vec(4)
    {
        //do nothing
    }

    Node(const unsigned int x, const unsigned int y, const char value) :
        m_x(x), m_y(y), m_val(value), m_is_fork(false), m_neighbor_vec(4)
    {
        // do nothing
    }

    Node(const unsigned int x, const unsigned int y, const char value, const bool is_fork, const std::vector<bool> neighbor_vec) :
        m_x(x), m_y(y), m_val(value), m_is_fork(is_fork), m_neighbor_vec(neighbor_vec)
    {
        // do nothing
    }

    int x() {
        return m_x;
    }

    int y() {
        return m_y;
    }

    char value() {
        return m_val;
    }

    bool is_fork() {
        return m_is_fork;
    }

    std::vector<bool> neighbor_vec() {
        return m_neighbor_vec;
    }

    void set_x(const int new_x) {
        m_x = new_x;
    }

    void set_y(const int new_y) {
        m_y = new_y;
    }

    void set_is_fork(const bool new_is_fork) {
        m_is_fork = new_is_fork;
    }

    void set_neighbor_vec(const std::vector<bool> new_neighbor_vec) {
        m_neighbor_vec = new_neighbor_vec;
    }
};