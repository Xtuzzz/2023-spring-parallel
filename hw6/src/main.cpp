#include <iostream>
#include "../include/Matrix.h"
#include "../include/Input.h"
#include "../include/Timer.h"

int main() {
    Timer t;

    Input in = Input();
    in.init("iinput.txt");
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
    Matrix mat1 = Matrix(3, 4, "one");
    Matrix mat2 = Matrix(3, 4, "random");
    mat2 *= 5;
    Matrix mat3 = mat1 + mat2;
    std::cout << mat3 << std::endl;


    std::cout << t;
}
