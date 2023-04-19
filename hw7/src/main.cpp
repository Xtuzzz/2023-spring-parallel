#include <iostream>
#include "Matrix.h"
#include "Input.h"
#include "Timer.h"

int main() {
    Timer t;

    Input my_input{};
    my_input.init("input.txt");
    if (my_input.cal == "rsmdiago") {
        std::vector<std::string> vec1 = my_input.read_file(my_input.file1);
        if (vec1[1] == "float") {
            Matrix<float> mat1(vec1);
            mat1.lapack_diago("../diago_float_out.txt", my_input.result_print);
        } else {
            Matrix<double> mat1(vec1);
            mat1.lapack_diago("../diago_double_out.txt", my_input.result_print);
        }
    } else {
        std::vector<std::string> vec1 = my_input.read_file(my_input.file1);
        std::vector<std::string> vec2 = my_input.read_file(my_input.file2);
        if (vec1[1] == "float") {
            Matrix<float> mat1(vec1);
            Matrix<float> mat2(vec2);
            Matrix<float> mat3 = mat1 * mat2;
            Matrix<float> mat4 = mat1.blas_mul(mat2);
            if (my_input.result_print) {
                std::cout << "my matmul" << std::endl;
                std::cout << mat3 << std::endl;
                std::cout << "BLAS matmul" << std::endl;
                std::cout << mat4 << std::endl;
                bool a{mat4 == mat3};
                std::cout << "same answer :" << a << std::endl;
            }
        } else {
            Matrix<double> mat1(vec1);
            Matrix<double> mat2(vec2);
            Matrix mat3 = mat1 * mat2;
            Matrix mat4 = mat1.blas_mul(mat2);
            if (my_input.result_print) {
                std::cout << "my matmul" << std::endl;
                std::cout << mat3 << std::endl;
                std::cout << "BLAS matmul" << std::endl;
                std::cout << mat4 << std::endl;
                bool a{mat4 == mat3};
                std::cout << "same answer :" << a << std::endl;
            }
        }
    }

    if (my_input.timer_print) {
        std::cout << t << std::endl;
    }
    return 0;
}

