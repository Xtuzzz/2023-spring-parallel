//
// Created by Xtzzzz on 2023/3/25.
//

#ifndef HW5_MATRIX_H
#define HW5_MATRIX_H

#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>

class Matrix {
public:
    int nr() const { return nrows; }

    int nc() const { return ncols; }

    //指向矩阵的第一行第一个数字的地址
    double **d = nullptr;

    Matrix();

    //通过输入的行列和初始化类型来初始化矩阵
    Matrix(const int &nr_in, const int &nc_in, const std::string &type);


    ~Matrix();

    void zero();
    //将矩阵的前nr行nc列交集的范围内的数全部置0
    void zero(const int &nr_in, const int &nc_in);
    //利用max_element求最大值
    double mat_max();

    double mat_min() ;

    void operator*=(const double &s);

    void operator+=(const double &s);

    void operator+=(const Matrix &A);

    double *operator()(const int &i, const int &j);

    Matrix operator+(const Matrix &m);

    Matrix operator-(const Matrix &m);

    friend std::ostream &operator<<(std::ostream &out, Matrix &A);

    friend std::ofstream &operator<<(std::ofstream &out, Matrix &A);

private:
    int nrows = 0;
    int ncols = 0;


};


#endif //HW5_MATRIX_H
