#include <iostream>
#include <fstream>
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

int main() {
    std::ifstream ifs;
    ifs.open("../iinput.txt");
    assert(ifs.good());
    std::string line;

    std::string calculation, matrix_type;
    bool matrix_print;
    int nrows, ncols;

    while (getline(ifs, line)) {
        line_process(line);
        if (line.empty()) continue;//skip the empty line

        std::istringstream iss(line);
        std::string arg1;

        iss >> arg1;
        arg1 = convert_to_lower(arg1);
        if (arg1 == std::string("calculation")) {
            iss >> calculation;
            calculation = convert_to_lower(calculation);
        } else if (arg1 == std::string("matrix_type")) {
            iss >> matrix_type;
            matrix_type = convert_to_lower(matrix_type);
        } else if (arg1 == std::string("matrix_print")) {
            iss >> matrix_print;
        } else if (arg1 == std::string("nrows")) {
            iss >> nrows;
        } else {
            iss >> ncols;
        }
    }


    std::cout << "calculation = " << calculation << std::endl;
    std::cout << "mat type = " << matrix_type << std::endl;
    std::cout << "mat print = " << matrix_print << std::endl;
    std::cout << "cols = " << ncols << std::endl;
    std::cout << "rows = " << nrows << std::endl;

    return 0;
}