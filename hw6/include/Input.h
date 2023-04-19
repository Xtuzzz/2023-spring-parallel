//
// Created by Xtzzzz on 2023/3/17.
//

#ifndef HW5_INPUT_H
#define HW5_INPUT_H

#include <iostream>
#include <string>
#include <fstream>

class Input {
public:
    Input();

    ~Input();

    void init(const std::string &fn);

    std::string cal, mat_type;
    int nr, nc, mat_print;
private:
    friend std::ostream &operator<<(std::ostream &out, Input &A);

    friend std::ofstream &operator<<(std::ofstream &out, Input &A);

};


#endif //HW5_INPUT_H
