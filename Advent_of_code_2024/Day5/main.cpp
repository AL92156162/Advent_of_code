// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void DisplayVector(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ";";
    }
    std::cout << "\n";
}

int getNRule(std::string file_name) {
    std::string line;
    std::ifstream myfile(file_name);

    bool is_rule = true;
    int n_rule = -1;
    if (myfile.is_open()) {
        while (getline(myfile, line) && is_rule) {
            if (line.empty()) {
                is_rule = false;
            }
            n_rule += 1;
        }
    }

    myfile.close();

    return n_rule;
}

std::vector<std::vector<int>> getRules(const std::string file_name) {
    std::string line;
    std::ifstream myfile(file_name);

    bool is_rule = true;
    std::vector<std::vector<int>> rules(2);

    if (myfile.is_open()) {
        while (getline(myfile, line) && is_rule) {
            if (line.empty()) {
                is_rule = false;
            }
            else {
                rules[0].push_back(stoi(line.substr(0, 2)));
                rules[1].push_back(stoi(line.substr(3, 2)));
            }
        }
    }
    myfile.close();
    return rules;
}

std::vector<int> getUpdate(std::string line) {
    int n_val = line.size() / 3 + 1;
    std::vector<int> update(n_val);
    for (int i = 0; i < n_val; ++i) {
        update[i] = stoi(line.substr(i * 3, 2));
    }
    return update;
}

bool updateIsCorrect(std::vector<int> update, std::vector<std::vector<int>> rules) {
    int n_rule = rules[0].size();
    int n_val = update.size();

    bool update_is_correct = true;
    for (int i = 0; i < n_rule; ++i) {
        int rule_n1 = rules[0][i];
        int rule_n2 = rules[1][i];


        bool n2_found = false;
        for (int j = 0; j < n_val; ++j) {
            if (update[j] == rule_n2) {
                n2_found = true;
            }

            if (n2_found && update[j] == rule_n1) {
                update_is_correct = false;
            }
        }
    }
    return update_is_correct;
}

int main() {

    

    std::string line;
    std::string file_name = "input.txt";

    std::vector<std::vector<int>> rules = getRules(file_name);

    std::cout << rules[0].size() << std::endl;

    std::ifstream myfile(file_name);
    int n_rule = rules[0].size();

    ////int n_rule = getNRule(file_name);
    //std::vector<std::string> updates;
    
    int count_correct_update = 0;
    int result1 = 0;
    int result2 = 0;
    int result3 = 0;
    bool is_rule = true;
    if (myfile.is_open()){
        while (getline(myfile, line)) {
            
            if (not is_rule) {

                std::vector<int> update = getUpdate(line);
                bool update_is_correct = updateIsCorrect(update, rules);

                if (update_is_correct) {
                    count_correct_update += 1;
                    result1 += update[update.size() /2];
                }

                else {
                    int n_rule = rules[0].size();
                    int n_val = update.size();
                    int max_iter = 100;
                    int i = 0;

                    while (i < max_iter && not update_is_correct) {
                        int n_respected_rule = 0;
                        for (int i = 0; i < n_rule; ++i) {
                            bool rule_is_respected = true;
                            int rule_n1 = rules[0][i];
                            int rule_n2 = rules[1][i];

                            int n2_idx = -1;
                            int n1_idx = -1;
                            for (int j = 0; j < n_val; ++j) {
                                if (n2_idx == -1 && update[j] == rule_n2) {
                                    n2_idx = j;
                                }

                                if (n2_idx >= 0 && update[j] == rule_n1) {
                                    rule_is_respected = false;
                                    n1_idx = j;
                                }
                            }

                            //DisplayVector(update);
                            if (not rule_is_respected) {
                                //std::cout << n1_idx << ";" << n2_idx << std::endl;
                                std::swap(update[n1_idx], update[n2_idx]);
                            }
                            else {
                                n_respected_rule += 1;
                            }
                            //DisplayVector(update);

                        }
                        if (n_respected_rule == n_rule) {
                            update_is_correct = true;
                        }
                        i += 1;
                        //std::cout << n_respected_rule << std::endl;
                    }

                    update_is_correct = updateIsCorrect(update, rules);
                    if (update_is_correct) {
                        std::cout << update[n_val / 2] << std::endl;
                        result2 += update[n_val / 2];
                    }
                    else {
                        DisplayVector(update);
                        std::cout << "incorrect update" << std::endl;
                    }
                }

                /*DisplayVector(update);
                if (updateIsCorrect(update, rules)) {
                    result3 += update[update.size() / 2];
                }*/
            }

            if (line.empty()) {
                is_rule = false;
            }
        }
    }

    
    myfile.close();

    std::cout << "Part1:" << count_correct_update << ';' << result1 << std::endl;
    std::cout << "Part2:" << result2 << std::endl;
    std::cout << "Res3:" << result3 << std::endl;

}