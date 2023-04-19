//
// Created by Xtzzzz on 2023/3/25.
//

#include "../include/Matrix.h"
#include "../include/Timer.h"
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
    Timer::begin("Matrix", "Matrix construct");
    //std::cout << "init the matrix" << std::endl;

    ncols = nc_in;
    nrows = nr_in;

    if (ncols <= 0) {
        std::cout << "Ncol Error!" << std::endl;
    }
    if (nrows <= 0) {
        std::cout << "Nrow Error!" << std::endl;
    }

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
    Timer::end("Matrix", "Matrix construct");
}

void Matrix::zero() {
    Timer::begin("Matrix", "zero 1");
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] = 0;
        }
    }
    Timer::end("Matrix", "zero 1");
}

void Matrix::zero(const int &nr_in, const int &nc_in) {
    Timer::begin("Matrix", "zero 2");
    for (int i = 0; i < nr_in; ++i) {
        for (int j = 0; j < nc_in; ++j) {
            d[i][j] = 0;
        }
    }
    Timer::end("Matrix", "zero 2");
}

void Matrix::operator*=(const double &s) {
    Timer::begin("Matrix", "Mat *= double");
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] *= s;
        }
    }
    Timer::end("Matrix", "Mat *= double");
}

double *Matrix::operator()(const int &i, const int &j) {
    double *p = &d[i][j];
    return p;
}

Matrix Matrix::operator+(const Matrix &m) {
    Timer::begin("Matrix", "Mat + Mat");
    if ((this->nrows != m.nr()) or this->ncols != m.nc()) {
        std::cout << "Cannot Add Matrix (Dimension Error)" << std::endl;
        exit(-1);
    }
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            this->d[i][j] += m.d[i][j];
        }
    }
    Timer::end("Matrix", "Mat + Mat");
    return *this;
}

Matrix Matrix::operator-(const Matrix &m) {
    Timer::begin("Matrix", "Mat - Mat");
    if ((this->nrows != m.nr()) or this->ncols != m.nc()) {
        std::cout << "Cannot Add Matrix (Dimension Error)" << std::endl;
        exit(-1);
    }
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            this->d[i][j] -= m.d[i][j];
        }
    }
    Timer::end("Matrix", "Mat - Mat");
    return *this;
}

std::ostream &operator<<(std::ostream &out, Matrix &A) {
    Timer::begin("Matrix", "<<");
    for (int i = 0; i < A.nr(); ++i) {
        for (int j = 0; j < A.nc(); ++j) {
            std::cout << std::setprecision(6) << std::fixed << A.d[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    Timer::end("Matrix", "<<");
    return out;
}

std::ofstream &operator<<(std::ofstream &out, Matrix &A) {
    Timer::begin("Matrix", "<<");
    for (int i = 0; i < A.nrows; ++i) {
        for (int j = 0; j < A.ncols; ++j) {
            std::cout << std::setw(6) << A.d[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    Timer::end("Matrix", "<<");
    return out;
}

void Matrix::operator+=(const double &s) {
    Timer::begin("Matrix", "plus_double");
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] += s;
        }
    }
    Timer::end("Matrix", "plus_double");
}

void Matrix::operator+=(const Matrix &A) {
    Timer::begin("Matrix", "plus_Mat");
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] += A.d[i][j];
        }
    }
    Timer::end("Matrix", "plus_Mat");
}

double Matrix::mat_max() {
    Timer::begin("Matrix", "mat_max");
    double a = *std::max_element(*d, *d + nrows * ncols);
    Timer::end("Matrix", "mat_max");
    return a;
}

double Matrix::mat_min() {
    Timer::begin("Matrix", "mat_min");
    double a = *std::min_element(*d, *d + nrows * ncols);
    Timer::end("Matrix", "mat_min");
    return a;
}
