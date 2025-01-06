// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

void DisplayVec(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ";";
    }
    std::cout << std::endl;
}

void DisplayVec(std::vector<unsigned long long> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ";";
    }
    std::cout << std::endl;
}

void adv(std::vector<unsigned long long>& vec, unsigned long long combo_op) {
    vec[0] /= pow(2, combo_op);
}

void bxl(std::vector<unsigned long long>& vec, int lit_op) {
    vec[1] = vec[1] ^ lit_op;
}

void bst(std::vector<unsigned long long>& vec, unsigned long long combo_op) {
    vec[1] = combo_op % 8;
}

int jnz(std::vector<unsigned long long>& vec, int lit_op, int idx) {
    idx += 2;
    if (vec[0] > 0) {
        idx = lit_op;
    }
    return idx;
}

void bxc(std::vector<unsigned long long>& vec, int lit_op) {
    vec[1] = vec[1] ^ vec[2];
}

int out(std::vector<unsigned long long>& vec, unsigned long long combo_op) {
    return combo_op % 8;
}

void bdv(std::vector<unsigned long long>& vec, unsigned long long combo_op) {
    vec[1] = vec[0] / pow(2, combo_op);
}

void cdv(std::vector<unsigned long long>& vec, unsigned long long combo_op) {
    vec[2] = vec[0] / pow(2, combo_op);
}

unsigned long long get_combo_op(std::vector<unsigned long long>& vec, int idx) {
    unsigned long long res = idx;

    if (idx >= 7) {
        std::cout << "Literal operand equals to 7" << std::endl;
    }
    else if (idx > 3) {
        res = vec[idx - 4];
    }
    return res;

}

std::vector<int> compute_program(std::vector<unsigned long long>& vec_ref, std::vector<int> program) {
    unsigned long long max_iter = pow(10,16);
    int idx = 0;
    std::vector<int> program_output;
    for (int i = 0; i < max_iter; ++i) {

        int ins = program[idx];
        int lit_op = program[idx + 1];
        unsigned long long combo_op = get_combo_op(vec_ref, lit_op);

        //std::cout << idx << ";" << ins << ";" << lit_op << ";" << combo_op << std::endl;


        if (ins == 0) {
            adv(vec_ref, combo_op);
            idx += 2;
        }

        else if (ins == 1) {
            bxl(vec_ref, lit_op);
            idx += 2;
        }

        else if (ins == 2) {
            bst(vec_ref, combo_op);
            idx += 2;
        }

        else if (ins == 3) {
            idx = jnz(vec_ref, combo_op, idx);

        }

        else if (ins == 4) {
            bxc(vec_ref, lit_op);
            idx += 2;

        }

        else if (ins == 5) {
            program_output.push_back(out(vec_ref, combo_op));
            idx += 2;

        }

        else if (ins == 6) {
            bdv(vec_ref, combo_op);
            idx += 2;

        }

        else if (ins == 7) {
            cdv(vec_ref, combo_op);
            idx += 2;

        }

        else {
            std::cout << "Error: instruction > 7" << std::endl;
        }

        if (idx >= program.size() - 1) {
            break;
        }


    }

    //std::cout << "Register : " << vec_ref[0] << "," << vec_ref[1] << "," << vec_ref[2] << std::endl;

    return program_output;
}


//int compare_vec(std::vector<int> v1, std::vector<int> v2) {
//    std::cout << v1.size() << ";" << v2.size() << std::endl;
//    int res = 0;
//    if (v1.size() > v2.size()) {
//        res = 1;
//    }
//    else if (v1.size() < v2.size()) {
//        res = -1;
//    }
//    else if (v1.size() == v2.size()){
//        for (int i = v1.size()-1; i >=0 ; --i) {
//            if (v1[i] < v2[i]) {
//                res = -1;
//                break;
//            }
//            else if (v1[i] > v2[i]) {
//                res = 1;
//                break;
//            }
//        }
//    }
//    return res;
//}

int compare_vec(std::vector<int> v1, std::vector<int> v2) {
    
    for (int i = v1.size() - 1; i >= 0; --i) {
        if (v1[i] == 0) {
            v1.erase(v1.begin() + i);
        }
        else {
            break;
        }
    }

    for (int i = v2.size() - 1; i >= 0; --i) {
        if (v2[i] == 0) {
            v2.erase(v2.begin() + i);
        }
        else {
            break;
        }
    }

    int res = 0;
    if (v1.size() > v2.size()) {
        res = 1;
    }
    else if (v1.size() < v2.size()) {
        res = -1;
    }
    else if (v1.size() == v2.size()) {
        for (int i = v1.size() - 1; i >= 0; --i) {
            if (v1[i] < v2[i]) {
                res = -1;
                break;
            }
            else if (v1[i] > v2[i]) {
                res = 1;
                break;
            }
        }
    }
    return res;
}

int main(){

    std::string line;
    std::string file_name = "input.txt";
    std::ifstream myfile(file_name);

    std::regex reg(R"((\d+))");
    std::smatch matches;

    std::vector<unsigned long long> vec;
    std::vector<int> program;

    if (myfile.is_open())
    {
        while (getline(myfile, line)) {
            while (std::regex_search(line, matches, reg)) {
                if (vec.size() < 3) {
                    vec.push_back(std::stoll(matches[0]));
                }
                else {
                    program.push_back(std::stoll(matches[0]));
                }
                line = matches.suffix();
            }
        }
    }
    myfile.close();

    std::vector<unsigned long long>& vec_ref = vec;
    DisplayVec(vec);
    DisplayVec(program);


    // Brute force
    /*int max_iter = 1000000;
    bool is_program_copy;
    std::vector<int> program_output;
    int i;
    for (i = 0; i < max_iter; ++i) {
        is_program_copy = true;
        program_output = compute_program(vec_ref, program);

        if (program.size() != program_output.size()) {
            is_program_copy = false;
        }
        else {
            for (int j = 0; j < program_output.size(); ++j) {
                if (program_output[j] != program[j]) {
                    is_program_copy = false;
                    break;
                }
            }
        }

        if (is_program_copy) {
            break;
        }
        else {
            vec_ref[0] = i;
        }
    }
    
    std::cout << "A initial value: " << i - 1 << std::endl;

    std::cout << "Register : " << vec_ref[0] << "," << vec_ref[1] << "," << vec_ref[2] << std::endl;

    for (int i = 0; i < program_output.size(); ++i) {
        std::cout << program_output[i] << ",";
    }*/

    // Dichotomy
    unsigned long long target = 0;
    for (int j = 0; j < program.size(); ++j) {
        target += program[j] * pow(10, j);
    }

    int max_iter = 100;
    unsigned long long a = 0;
    unsigned long long b = LLONG_MAX;
    unsigned long long mval;
    bool is_program_copy;
    std::vector<int> program_output;
    
    for (int i = 0; i < max_iter; ++i) {
        is_program_copy = true;

        vec_ref[0] = (a+b)/2;
        std::cout << a << ";" << b << ";" << (a + b) / 2 << std::endl;

        program_output = compute_program(vec_ref, program);

        
        DisplayVec(program);
        DisplayVec(program_output);

        int vcompare = compare_vec(program_output, program);
        std::cout << vcompare << std::endl;
        if (vcompare == 0) {
            std::cout << "Program ended" << std::endl;
            break;
        }
        else if (vcompare > 0) {
            b = (a + b) / 2;
        }
        else {
            a = (a + b) / 2;
        }
    }

    unsigned long long a_val = ((a + b) / 2) / 10;
    std::cout << "A initial value: " << a_val * 10 << ";" << std::endl;

    vec_ref[0] = a_val * 10;
    std::cout << "Register : " << vec_ref[0] << "," << vec_ref[1] << "," << vec_ref[2] << std::endl;
    program_output = compute_program(vec_ref, program);

    DisplayVec(program);
    DisplayVec(program_output);


	return 0;
}