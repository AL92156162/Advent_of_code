#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

class Map {
    unsigned int m_width;
    unsigned int m_height;
    std::vector<int> m_vec;

public:
    Map() :
        m_width(0), m_height(0), m_vec(m_height* m_width)
    {
        //do nothing
    }

    Map(const unsigned int width, const unsigned int height, std::vector<int> vec) :
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

    std::vector<int> const& vec() const {
        return m_vec;
    }

    std::vector<int> & vec() {
        return m_vec;
    }

    int getValue(int x, int y) {

        if (x>=0 && y>=0 ) {
            if (x < m_width && y < m_height) {
                return m_vec[y * m_width + x];
            }
            else {
                return -1;
            }
        }
        else {
            return -1;
        }
    }

    void setValue(int x, int y, int new_val) {
        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            m_vec[y * m_width + x] = new_val;
        }
    }


    void display() {
        for (int i = 0; i < m_height; ++i) {
            for (int j = 0; j < m_width; ++j) {

                if (getValue(j, i) == 0) {
                    std::cout << ".";
                }
                else {
                    std::cout << getValue(j, i);
                }
            }
            std::cout << std::endl;
        }
    }
};