//
// Created by Xtzzzz on 2023/4/19.
//


#include "Input.h"

// delete the comment, using find and erase
static void line_process(std::string &line, const std::string comment_str = "#") {
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
    std::ifstream ifs;
    if (fn.empty())
        ifs.open("iinput.txt");
    else
        ifs.open(fn);
    std::cout << "read from : " + fn << std::endl;
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
        } else if (arg1 == std::string("result_print")) {
            iss >> result_print;
        } else if (arg1 == std::string("timer_print")) {
            iss >> timer_print;
        } else if (arg1 == std::string("matrix_1")) {
            iss >> file1;
        } else if (arg1 == std::string("matrix_2") and cal == "matmul") {
            iss >> file2;
        }
    }
}

std::ostream &operator<<(std::ostream &out, Input &A) {
    std::cout << "calculation = " << A.cal << std::endl;
    std::cout << "mat_type = " << A.mat_type << std::endl;
    std::cout << "result_print = " << A.result_print << std::endl;
}

std::vector<std::string> Input::read_file(const std::string &fn) {
    std::string nc, nr, type;

    std::vector<std::string> vec{};
    std::ifstream ifs{fn};
    std::string line;

    if (!ifs.good()) {
        std::cout << "Cannot Find Input File!";
        exit(-1);
    }
    while (getline(ifs, line)) {
        line_process(line);
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string arg1, arg2;
        iss >> arg1;
        arg1 = convert_to_lower(arg1);
        if (arg1 == "nrows:") {
            iss >> nr;
        } else if (arg1 == "ncols:") {
            iss >> nc;
        } else if (arg1 == "type:") {
            iss >> type;
        } else {
            break;
        }
    }
    vec.push_back(nr + " " + nc);
    vec.push_back(type);
    for (int i = 0; i < std::stoi(nr); ++i) {
        getline(ifs, line);
        vec.push_back(line);
    }
    return vec;
}
