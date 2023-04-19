//
// Created by Xtzzzz on 2023/4/19.
//

#ifndef HW7_INPUT_H
#define HW7_INPUT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Input {
public:
    Input();

    ~Input();

    void init(const std::string &fn);

    std::vector<std::string> read_file(const std::string &fn);

    std::string cal, mat_type;
    int result_print, timer_print;
    std::string file1, file2;
private:
    friend std::ostream &operator<<(std::ostream &out, Input &A);

};


#endif //HW7_INPUT_H
