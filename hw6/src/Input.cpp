//
// Created by Xtzzzz on 2023/3/17.
//

#include "../include/Input.h"
#include "../include/Timer.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

// delete the comment, using find and erase
void line_process(std::string &line, const std::string comment_str = "#") {
    int n_comment_start = line.find_first_of(comment_str);
    if (n_comment_start != std::string::npos) {
        line.erase(n_comment_start);
    }
}

// convert string to lower string
std::string convert_to_lower(std::string a) {
    std::string ans;
    std::transform(a.begin(), a.end(), std::back_inserter(ans), ::tolower);
    return ans;
}


Input::Input() {
}

Input::~Input() {
}

void Input::init(const std::string &fn) {
    Timer::begin("Input", "init");
    std::ifstream ifs;
    if (fn.empty())
        ifs.open("iinput.txt");
    else
        ifs.open(fn);
    std::cout << "read from file " + fn << std::endl;
    if (!ifs.good()) {
        std::cout << "Cannot Find Input File!";
        exit(-1);
    }
    std::string line;


    while (getline(ifs, line)) {
        line_process(line);
        if (line.empty()) continue;//skip the empty line

        std::istringstream iss(line);
        std::string arg1;

        iss >> arg1;
        arg1 = convert_to_lower(arg1);
        if (arg1 == std::string("calculation")) {
            iss >> cal;
            cal = convert_to_lower(cal);
        } else if (arg1 == std::string("matrix_type")) {
            iss >> mat_type;
            mat_type = convert_to_lower(mat_type);
        } else if (arg1 == std::string("matrix_print")) {
            iss >> mat_print;
        } else if (arg1 == std::string("nrows")) {
            iss >> nr;
        } else if (arg1 == std::string("ncols")) {
            iss >> nc;
        } else {
            std::cout << "Check The Arg Name!" << std::endl;
            exit(-1);
        }
    }
    Timer::end("Input", "init");
}

std::ostream &operator<<(std::ostream &out, Input &A) {
    Timer::begin("Input", "<<");
    std::cout << "calculation = " << A.cal << std::endl;
    std::cout << "mat_type = " << A.mat_type << std::endl;
    std::cout << "mat_print = " << A.mat_print << std::endl;
    std::cout << "cols = " << A.nc << std::endl;
    std::cout << "rows = " << A.nr << std::endl;
    Timer::end("Input", "<<");
    return out;
}

std::ofstream &operator<<(std::ofstream &out, Input &A) {
    Timer::begin("Input", "<<");
    std::cout << "calculation = " << A.cal << std::endl;
    std::cout << "mat_type = " << A.mat_type << std::endl;
    std::cout << "mat_print = " << A.mat_print << std::endl;
    std::cout << "cols = " << A.nc << std::endl;
    std::cout << "rows = " << A.nr << std::endl;
    Timer::end("Input", "<<");
    return out;
}



