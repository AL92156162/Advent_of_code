// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "header.hpp"

void DisplayVec(std::vector<bool> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
    }
}

std::vector<bool> CheckAround(Map& map, int x, int y) {
    std::vector<bool> neighbors(4);

    if (map.getValue(x + 1, y) == '.') {
        neighbors[0] = true;
    }
    if (map.getValue(x, y + 1) == '.') {
        neighbors[1] = true;
    }
    if (map.getValue(x - 1, y) == '.') {
        neighbors[2] = true;
    }
    if (map.getValue(x, y - 1) == '.') {
        neighbors[3] = true;
    }
    return neighbors;
}

std::vector<int> MoveForward(int x, int y, int orientation) {
    std::vector<int> new_pos = { x,y,orientation };

    if (orientation == 0) {
        new_pos[0] += 1;
    }
    else if (orientation == 1) {
        new_pos[1] += 1;
    }
    else if (orientation == 2) {
        new_pos[0] -= 1;
    }
    else if (orientation == 3) {
        new_pos[1] -= 1;
    }

    return new_pos;
}

std::vector<int> Rotate(int x, int y, int orientation, int rotation_dir) {
    std::vector<int> new_pos = { x, y, orientation};

    if (rotation_dir == 1) {
        if (new_pos[2] == 3) {
            new_pos[2] = 0;
        }
        else {
            new_pos[2] += 1;
        }
    }
    else if (rotation_dir == -1) {
        if (new_pos[2] == 0) {
            new_pos[2] = 3;
        }
        else {
            new_pos[2] -= 1;
        }
    }

    return new_pos;
}

int FindVertex(std::vector<std::vector<int>> vertices, int x, int y, int orientation) {
    int i;
    bool vfund = false;
    for (i = 0; i < vertices.size(); ++i) {
        if (vertices[i][0] == x && vertices[i][1] == y && vertices[i][2] == orientation) {
            vfund = true;
            break;
        }
    }
    if (!vfund) {
        i = -1;
    }
    return i;
}

int FindMinDist(std::vector<int> Q, std::vector<unsigned long> dist) {
    unsigned long mini = INT32_MAX;
    int vertex = -1;
    int idx = 0;
    for (int i = 0; i < Q.size(); ++i) {
        int q = Q[i];

        if (dist[q] < mini) {
            mini = dist[q];
            vertex = q;
            idx = i;
        }
    }
    return idx;
}
bool ValueInVec(int val, std::vector<int> vec) {
    bool res = false;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == val) {
            res = true;
            break;
        }
    }
    return res;
}

unsigned long Dijkstra(std::vector<std::vector<int>> vertices, std::pair<int, int> spos, std::pair<int, int> epos) {
    // Initialization
    std::vector<unsigned long> dist(vertices.size(), INT32_MAX);
    int sidx = FindVertex(vertices, spos.first, spos.second, 0);
    dist[sidx] = 0;

    std::vector<int> Q(vertices.size());
    for (int i = 0; i < vertices.size(); ++i) {
        Q[i] = i;
    }


    for (int i = 0; i < vertices.size(); ++i) {
        int min_idx = FindMinDist(Q, dist);
        int iv = Q[min_idx];
        Q.erase(Q.begin() + min_idx);

        std::vector<int> v1 = MoveForward(vertices[iv][0], vertices[iv][1], vertices[iv][2]);
        int iv1 = FindVertex(vertices, v1[0], v1[1], v1[2]);
        if (iv1 >= 0  && dist[iv1] > dist[iv] + 1) {
            dist[iv1] = dist[iv] + 1;
        }

        std::vector<int> v2 = Rotate(vertices[iv][0], vertices[iv][1], vertices[iv][2], 1);
        int iv2 = FindVertex(vertices, v2[0], v2[1], v2[2]);
        if (iv2 >= 0 && dist[iv2] > dist[iv] + 1000) {
            dist[iv2] = dist[iv] + 1000;
        }

        std::vector<int> v3 = Rotate(vertices[iv][0], vertices[iv][1], vertices[iv][2], -1);
        int iv3 = FindVertex(vertices, v3[0], v3[1], v3[2]);
        if (iv3 >= 0 && dist[iv3] > dist[iv] + 1000) {
            dist[iv3] = dist[iv] + 1000;
        }

        if (Q.size() <= 0 || (vertices[iv][0] == epos.first && vertices[iv][1] == epos.second)) {
            break;
        }
    }
    
    unsigned long res = INT32_MAX;
    for (int i = 0; i < 4; ++i) {
        int eidx = FindVertex(vertices, epos.first, epos.second, i);

        if (dist[eidx] < res) {
            res = dist[eidx];
        }
    }
    return res;
}

std::vector<int> getBestTiles(std::vector<std::vector<int>> previous_vec, int idx, int sidx) {
    std::vector<int> tvec = {idx};
    if (idx != sidx) {
        for (int i = 0; i < previous_vec[idx].size(); ++i) {
            std::vector<int> pvec = getBestTiles(previous_vec, previous_vec[idx][i], sidx);
            for (int j = 0; j < pvec.size(); ++j) {
                tvec.push_back(pvec[j]);
            }
        }
    }
    return tvec;
}

std::vector<int> Dijkstra2(std::vector<std::vector<int>> vertices, std::pair<int, int> spos, std::pair<int, int> epos) {
    // Initialization
    std::vector<unsigned long> dist(vertices.size(), INT32_MAX);
    int sidx = FindVertex(vertices, spos.first, spos.second, 0);
    dist[sidx] = 0;

    std::vector<int> Q(vertices.size());
    for (int i = 0; i < vertices.size(); ++i) {
        Q[i] = i;
    }

    std::vector<std::vector<int>> previous_vec(vertices.size());

    for (int i = 0; i < vertices.size(); ++i) {
        int min_idx = FindMinDist(Q, dist);
        int iv = Q[min_idx];
        Q.erase(Q.begin() + min_idx);

        std::vector<int> v1 = MoveForward(vertices[iv][0], vertices[iv][1], vertices[iv][2]);
        int iv1 = FindVertex(vertices, v1[0], v1[1], v1[2]);
        if (iv1 >= 0 && dist[iv1] >= dist[iv] + 1) {
            if (dist[iv1] >= dist[iv] + 1) {
                dist[iv1] = dist[iv] + 1;
            }
            previous_vec[iv1].push_back(iv);
        }

        std::vector<int> v2 = Rotate(vertices[iv][0], vertices[iv][1], vertices[iv][2], 1);
        int iv2 = FindVertex(vertices, v2[0], v2[1], v2[2]);
        if (iv2 >= 0 && dist[iv2] >= dist[iv] + 1000) {
            if (dist[iv2] > dist[iv] + 1000) {
                dist[iv2] = dist[iv] + 1000;
            }
            previous_vec[iv2].push_back(iv);
        }

        std::vector<int> v3 = Rotate(vertices[iv][0], vertices[iv][1], vertices[iv][2], -1);
        int iv3 = FindVertex(vertices, v3[0], v3[1], v3[2]);
        if (iv3 >= 0 && dist[iv3] >= dist[iv] + 1000) {
            if (dist[iv3] > dist[iv] + 1000) {
                dist[iv3] = dist[iv] + 1000;
            }
            previous_vec[iv3].push_back(iv);
        }

        if (Q.size() <= 0 || (vertices[iv][0] == epos.first && vertices[iv][1] == epos.second)) {
            break;
        }
    }

    unsigned long mini = INT32_MAX;
    int eidx;
    for (int i = 0; i < 4; ++i) {
        int ie = FindVertex(vertices, epos.first, epos.second, i);

        if (dist[ie] < mini) {
            mini = dist[ie];
            eidx = ie;
        }
    }

    std::cout << "End distance: " << dist[eidx] << ";" << mini << std::endl;
    std::vector<int> res = getBestTiles(previous_vec, eidx, sidx);

    return res;
}


int main() {

    std::string line;
    std::string file_name = "input.txt";
    std::ifstream myfile(file_name);

    int width = 0;
    int height = 0;
    std::vector<char> mvec;
    if (myfile.is_open())
    {
        while (getline(myfile, line)) {

            for (int i = 0; i < line.size(); ++i) {
                mvec.push_back(line[i]);
            }
            height += 1;
            width = line.size();
        }
    }
    myfile.close();

    Map map(width, height, mvec);
    Map& map_ref = map;
    map.display();


    std::vector<std::vector<int>> vertices;

    std::pair<int, int> spos;
    std::pair<int, int> epos;
    int orientation = 0;
    for (int i = 0; i < map.width(); ++i) {
        for (int j = 0; j < map.height(); ++j) {
            
            if (map.getValue(i, j) == 'S') {
                spos.first = i;
                spos.second = j;
            }
            else if (map.getValue(i, j) == 'E') {
                epos.first = i;
                epos.second = j;
            }
            if (map.getValue(i, j) != '#') {
                for (int k = 0; k < 4; ++k) {
                    std::vector<int> cpos = { i, j, k};
                    vertices.push_back(cpos);
                }
                
            }
        }
    }
    
    std::cout << vertices.size() << std::endl;

    /*std::vector<std::vector<int>> edges;
    int j;
    std::vector<int> e;
    for (int i = 0; i < vertices.size(); ++i) {

        std::vector<int> v1 = MoveForward(vertices[i][0], vertices[i][1], vertices[i][2]);
        j = FindVertex(vertices, v1[0], v1[1], v1[2]);
        if (j >= 0) {
            e = { i, j, 1 };
            edges.push_back(e);
        }
        
        std::vector<int> v2 = Rotate(vertices[i][0], vertices[i][1], vertices[i][2], 1);
        j = FindVertex(vertices, v2[0], v2[1], v2[2]);
        if (j >= 0) {
            e = { i, j, 1000 };
            edges.push_back(e);
        }

        std::vector<int> v3 = Rotate(vertices[i][0], vertices[i][1], vertices[i][2], -1);
        j = FindVertex(vertices, v3[0], v3[1], v3[2]);
        if (j >= 0) {
            e = { i, j, 1000 };
            edges.push_back(e);
        }

    }

    std::cout << edges.size() << std::endl;*/

    //for (int i = 0; i < edges.size(); ++i) {
    //    std::cout << edges[i][0] << ";" << edges[i][1] << ";" << edges[i][2] << std::endl;
    //    std::vector<int> v1 = vertices[edges[i][0]];
    //    std::vector<int> v2 = vertices[edges[i][1]];

    //    std::cout << v1[0] << ";" << v1[1] << ";" << v1[2] << "/";
    //    std::cout << v2[0] << ";" << v2[1] << ";" << v2[2] << std::endl;
    //}

    std::cout << "Start Dijkstra algorithm" << std::endl;

    //unsigned long min_dist = Dijkstra(vertices, spos, epos);
    //std::cout << "Part1:" << min_dist << std::endl;

    std::vector<int> best_tiles = Dijkstra2(vertices, spos, epos);
    int n_tile = 0;
    for (int i = 0; i < best_tiles.size(); ++i) {
        char val = map.getValue(vertices[best_tiles[i]][0], vertices[best_tiles[i]][1]);
        if (val == '.' || val == 'S' || val == 'E') {
            n_tile += 1;
        }
        map.setValue(vertices[best_tiles[i]][0], vertices[best_tiles[i]][1], 'O');
    }
    map.display();

    std::cout << "Part2:" << n_tile << std::endl;

}