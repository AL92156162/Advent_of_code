#pragma once
#include <stdexcept>
#include <string>
#include <vector>

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
            return '0';
        }
    }

    void addWall(const int x, const int y) {
        m_vec[y * m_width + x] = '#';
    }
};