#include <iostream>
#include "Matrix.h"
#include "Input.h"

int main() {
    Input in = Input();
    in.init("iinput.txt");
    std::cout << "read from files" << std::endl;
    std::cout << in << std::endl;
    std::cout << std::endl;

    Matrix mat = Matrix(in.nr, in.nc, in.mat_type);

    if (in.cal == "max") {
        std::cout << "max = " << mat.mat_max() << std::endl;
    } else if (in.cal == "min") {
        std::cout << "min = " << mat.mat_min() << std::endl;
    }
    if (in.mat_print) {
        std::cout << mat << std::endl;
    }
}
