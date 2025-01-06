#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <utility>

//int Dijkstra_v1(std::vector<std::vector<int>> vertices, std::vector<std::vector<int>> edges, std::pair<int, int> spos, std::pair<int, int> epos) {
//    // Initialization
//    std::vector<int> dist(vertices.size(), INT16_MAX);
//    int sidx = FindVertex(vertices, spos.first, spos.second, 0);
//    std::cout << sidx << std::endl;
//    dist[sidx] = 0;
//
//    std::vector<int> Q(vertices.size());
//    for (int i = 0; i < vertices.size(); ++i) {
//        Q[i] = i;
//    }
//
//    for (int i = 0; i < edges.size(); ++i) {
//        int min_idx = FindMinDist(Q, dist);
//        int v = Q[min_idx];
//        Q.erase(Q.begin() + min_idx);
//
//        for (int j = 0; j < edges.size(); ++j) {
//            if (edges[j][0] == v && ValueInVec(edges[j][1], Q)) {
//                if (dist[edges[j][1]] > dist[edges[j][0]] + edges[j][2]) {
//                    dist[edges[j][1]] = dist[edges[j][0]] + edges[j][2];
//                }
//            }
//        }
//        if (Q.size() <= 0) {
//            break;
//        }
//        std::cout << i << std::endl;
//    }
//
//    int res = INT16_MAX;
//
//    for (int i = 0; i < 4; ++i) {
//        int eidx = FindVertex(vertices, epos.first, epos.second, i);
//
//        if (dist[eidx] < res) {
//            res = dist[eidx];
//        }
//    }
//
//
//    return res;
//}


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

    Map(const unsigned int width, const unsigned int height) :
        m_width(width), m_height(height), m_vec(m_height* m_width, '.')
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

        if (x>=0 && y>=0 && x < m_width && y < m_height) {
            return m_vec[y * m_width + x];
        }
        else {
            return '-1';
        }
    }

    void setValue(int x, int y, char new_val) {
        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            m_vec[y * m_width + x] = new_val;
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

    std::pair<int, int> getRobotPosition() {
        std::pair<int, int> robot_pos;

        for (int i = 0; i < m_width; ++i) {
            for (int j = 0; j < m_height; ++j) {
                if (getValue(i, j) == '@') {
                    robot_pos.first = i;
                    robot_pos.second = j;
                }
            }
        }
        return robot_pos;
    }

};