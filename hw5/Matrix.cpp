//
// Created by Xtzzzz on 2023/3/25.
//

#include "Matrix.h"
#include <random>

Matrix::Matrix() {

}

Matrix::~Matrix() {
/*
    for (int i = 0; i < nrows; ++i) {
        delete[] this->d[i];
    }
    delete[]this->d;
    this->d = nullptr;
*/
    //std::cout << "delete complete" << std::endl;
    //手动delete会在执行类似于c=a+b之后多删除一次，导致内存出错
}

Matrix::Matrix(const int &nr_in, const int &nc_in, const std::string &type) {
    //std::cout << "init the matrix" << std::endl;
    ncols = nc_in;
    nrows = nr_in;

    assert(ncols > 0);
    assert(nrows > 0);

    this->d = new double *[nr_in];
    for (int i = 0; i < nr_in; ++i) {
        this->d[i] = new double[nc_in]();
    }

    if (type == "random") {
        std::default_random_engine e;
        for (int i = 0; i < nr_in; ++i) {
            for (int j = 0; j < nc_in; ++j) {
                std::uniform_real_distribution<double> u(0, 1);
                this->d[i][j] = u(e);
            }
        }
    } else if (type == "one") {
        for (int i = 0; i < nr_in; ++i) {
            for (int j = 0; j < nc_in; ++j) {
                this->d[i][j] = 1;
            }
        }
    }
}

void Matrix::zero() {
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] = 0;
        }
    }
}

void Matrix::zero(const int &nr_in, const int &nc_in) {
    for (int i = 0; i < nr_in; ++i) {
        for (int j = 0; j < nc_in; ++j) {
            d[i][j] = 0;
        }
    }
}

void Matrix::operator*=(const double &s) {
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] *= s;
        }
    }
}

double *Matrix::operator()(const int &i, const int &j) {
    double *p = &d[i][j];
    return p;
}

Matrix Matrix::operator+(const Matrix &m) {
    assert((this->nrows == m.nr()) and this->ncols == m.nc());
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            this->d[i][j] += m.d[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix &m) {
    assert((this->nrows == m.nr()) and this->ncols == m.nc());
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            this->d[i][j] -= m.d[i][j];
        }
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, Matrix &A) {
    for (int i = 0; i < A.nr(); ++i) {
        for (int j = 0; j < A.nc(); ++j) {
            std::cout << std::setprecision(6) << std::fixed << A.d[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return out;
}

std::ofstream &operator<<(std::ofstream &out, Matrix &A) {
    for (int i = 0; i < A.nrows; ++i) {
        for (int j = 0; j < A.ncols; ++j) {
            std::cout << std::setw(6) << A.d[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return out;
}

void Matrix::operator+=(const double &s) {
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] += s;
        }
    }
}

void Matrix::operator+=(const Matrix &A) {
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] += A.d[i][j];
        }
    }
}




