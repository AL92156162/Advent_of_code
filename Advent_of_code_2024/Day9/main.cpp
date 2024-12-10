// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void displayVector(std::vector<int> vec) {
    // Printing the elements of 
    // the set
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == -1) {
            std::cout << ".";
        }
        else {
            std::cout << vec[i];
        }
    }
    std::cout << std::endl;
}

std::string getLine(std::string file_name) {
    std::string line;
    std::ifstream myfile(file_name);

    if (myfile.is_open()) {
        getline(myfile, line);
    }
    myfile.close();
    return line;
}

std::vector<int> getBlockVector(std::string line) {
    std::vector<int> block_vec;
    int id = 0;
    for (unsigned int i = 0; i < line.size(); ++i) {
        int num = line[i] - '0';
        for (int j = 0; j < num; ++j) {
            if (i & 1) {
                block_vec.push_back(-1);
            }
            else {
                block_vec.push_back(id);

            }
        }
        if (i & 1) {
            id += 1;
        }
        //std::cout << id << ";" << line[i] << std::endl;
    }
    
    
    return block_vec;
}

std::vector<int> fragmente(std::vector<int> block_vec) {
    int idx = block_vec.size() - 1;
    for (int i = 0; i < idx; ++i) {
        if (block_vec[i] == -1) {
            while (block_vec[idx] == -1 && idx > i) {
                idx -= 1;
            }
            std::swap(block_vec[i], block_vec[idx]);
        }
    }
    return block_vec;
}

std::vector<int> getIDVector(std::string line) {
    std::vector<int> id_vec;
    int id = 0;

    for (unsigned int i = 0; i < line.size(); ++i) {

        if (i & 1) {
            id_vec.push_back(-1);
            id += 1;
        }
        else {
            id_vec.push_back(id);

        }
        //std::cout << id << ";" << line[i] << std::endl;
    }

    return id_vec;
}

std::vector<int> moveFile(std::vector<int> block_vec, const int file_id, const int new_idx) {

    int char_idx = 0;
    for (int i = 0; i < block_vec.size(); ++i) {
        if (block_vec[i] == file_id) {
            std::cout << i << ";" << new_idx << ";" << char_idx << std::endl;
            std::swap(block_vec[i], block_vec[new_idx+ char_idx]);
            char_idx += 1;
        }
    }

    return block_vec;
}

long long ChekSum(std::vector<int> vec) {
    long long checksum = 0;
    int id = 0;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != -1) {
            checksum += id * vec[i];
        }
        id += 1;
    }
    return checksum;
}

int main() {

    std::string line = getLine("input.txt");
    std::vector<int> block_vec = getBlockVector(line);
    //displayVector(block_vec);

    std::vector<int> fragmented_vec = fragmente(block_vec);
    //displayVector(fragmented_vec);

    //Part1
    long long checksum1 = ChekSum(fragmented_vec);
    

    //Part2
    std::vector<int> id_vec = getIDVector(line);
    int current_id=id_vec[id_vec.size() - 1];
    int file_size = 0;
    
    for (int i = block_vec.size() - 1; i >= 0; --i) {
        
        if (block_vec[i] == current_id) {
            file_size += 1;
        }
        else {
            int empty_size = 0;
            int j;
            for (j = 0; j <= i; ++j) {
                if (block_vec[j] == -1) {
                    empty_size += 1;
                }
                else {
                    if (empty_size < file_size) {
                        empty_size = 0;
                    }
                    else {
                        break;
                    }
                }
            }
            
            if (empty_size >= file_size && current_id >= 0) {
                //std::cout << i << ";" << current_id << ";" << j << ";" << file_size << ";" << empty_size << std::endl;
                for (int k = 0; k < file_size; ++k) {
                    std::swap(block_vec[i+k+1], block_vec[j+k-empty_size]);
                }
                
            }
            current_id = block_vec[i];
            file_size = 1;
        }
        
    }
    

    //displayVector(block_vec);
    long long checksum2 = ChekSum(block_vec);

    std::cout << "Part1 : " << checksum1 << std::endl;
    std::cout << "Part2 : " << checksum2 << std::endl;
    
}