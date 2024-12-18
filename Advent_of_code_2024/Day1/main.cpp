// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include "Header.hpp"

using namespace std;


int CountLines(string file_name)
{
    string line;
    ifstream myfile(file_name);
    int count = 0;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            count++;
        }

        myfile.close();
    }
    return count;
}


int main() {
    string file_name = "input.txt";
    int count= CountLines(file_name);

    cout << file_name << " contains " << count << " elements " << '\n';

    string line;
    ifstream myfile(file_name);
    int* right_array = new int[count];
    int* left_array = new int[count];

    if (myfile.is_open())
    {

        for (int i=0; i<count; i++)
        {
            getline(myfile, line);
            left_array[i] = stoi(line.substr(0, 5));
            right_array[i] = stoi(line.substr(8,13));
        }


        myfile.close();
    }

    else cout << "Unable to open file";

    //displayList(left_array, count);
    //displayList(right_array, count);

    // PART1

    /*bubbleSort(left_array, count);
    bubbleSort(right_array, count);

    int total_distance = 0;
    for (int i = 0; i < count; i++)
    {
        if (left_array[i] > right_array[i])
        {
            total_distance += left_array[i] - right_array[i];
        }
        else
        {
            total_distance += right_array[i] - left_array[i];
        }
        
    }
    std::cout << total_distance << std::endl;*/

    // PART2

    int left_max_idx = maximum(left_array, count);
    int right_max_idx = maximum(right_array, count);

    int left_max = left_array[left_max_idx];
    int right_max = right_array[right_max_idx];

    std::cout << left_max << ";" << right_max << std::endl;

    int* right_occur = new int[right_max+1]{0};
    int* left_occur = new int[left_max+1]{0};

    for (int i = 0; i < count; i++)
    {

        right_occur[right_array[i]] += 1;
        left_occur[left_array[i]] += 1;
    }

    //displayList(right_occur, right_max);
    //displayList(left_occur, left_max);

    int similarity_score = 0;
    for (int i = 0; i < left_max+1; i++)
    {
        similarity_score += i * right_occur[i] * left_occur[i];
    }

    std::cout << similarity_score << std::endl;

    delete[] right_occur;
    delete[] left_occur;

    delete[] right_array;
    delete[] left_array;

    return 0;
}