//
// Created by Xtzzzz on 2023/4/11.
//

#ifndef HW7_MATRIX_H
#define HW7_MATRIX_H

#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>
#include "clapack.h"
#include "cblas.h"
#include <fstream>
#include <sstream>
#include "Timer.h"


template<typename T>
class Matrix {
public:

    Matrix();

    Matrix(std::vector<std::string> vec);

    Matrix(int row, int col);

    Matrix(int row, int col, T val);

    Matrix(int row, int col, T *val);

    ~Matrix() = default;

    int get_row() { return this->row; }

    int get_col() { return this->col; }

    bool isRSM();

    Matrix blas_mul(Matrix const &B);

    Matrix lapack_diago(const std::string &file, int out);

    Matrix &operator=(Matrix const &other);

    Matrix operator+(Matrix const &other) const;

    Matrix operator-(Matrix const &other) const;

    Matrix operator*(Matrix const &other) const;

    Matrix operator+=(Matrix const &other);

    Matrix operator-=(Matrix const &other);

    Matrix operator*=(Matrix const &other);

    bool operator==(Matrix const &other);

    bool operator!=(Matrix const &other) { return !*this == other; }

    T *operator[](int x) const;

    friend std::ostream &operator<<(std::ostream &out, Matrix &A) {
        for (int i = 0; i < A.get_row(); ++i) {
            for (int j = 0; j < A.get_col(); ++j) {
                out << std::setprecision(6) << std::fixed << A.p[i][j] << ' ';
            }
            out << std::endl;
        }
        return out;
    }


private:
    int row{0}, col{0};
    T **p{nullptr};

    void init();
};

template<typename T>
bool Matrix<T>::operator==(const Matrix &other) {
    if (this->row != other.row or this->col != other.col) {
        return false;
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (fabs(this->p[i][j] - other.p[i][j]) > 1e-4)
                return false;
        }
    }
    return true;
}

template<typename T>
Matrix<T>::Matrix(std::vector<std::string> vec) {
    std::istringstream iss;
    char del;
    for (int i = 0; i < vec.size(); ++i) {
        iss.str(vec[i]);
        if (i == 0) {
            iss >> row >> col;
            init();
        } else if (i == 1) {
            continue;
        } else {
            int j = i - 2;
            T temp;
            for (int k = 0; k < col; ++k) {
                if (k != col - 1)
                    iss >> temp >> del;
                else
                    iss >> temp;
                p[j][k] = temp;
            }
        }
        iss.clear();
    }
}


template<typename T>
Matrix<T>::Matrix() {
    this->row = 1;
    this->col = 1;
    init();
    p[0][0] = 0;
}

template<typename T>
Matrix<T>::Matrix(int row, int col) {
    this->col = col;
    this->row = row;
    init();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            p[i][j] = 0;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(int row, int col, T val) {
    this->col = col;
    this->row = row;
    init();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            p[i][j] = val;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(int row, int col, T *val) {
    this->col = col;
    this->row = row;
    init();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            p[i][j] = val[col * i + j];
        }
    }
}


template<typename T>
bool Matrix<T>::isRSM() {
    if (col != row) {
        return false;
    }
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            if (p[i][j] != p[j][i]) {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
Matrix<T> Matrix<T>::blas_mul(const Matrix &B) {
    Timer::begin("Matrix", "blas_matmul");
    T *a = new T[this->row * this->col], *b = new T[B.row * B.col];
    T *c = new T[this->row * B.col];

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            a[col * i + j] = this->p[i][j];
        }
    }
    for (int i = 0; i < B.row; ++i) {
        for (int j = 0; j < B.col; ++j) {
            b[col * i + j] = B.p[i][j];
        }
    }
    if constexpr (std::is_same<T, float>::value) {
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    this->row, B.col, this->col, 1,
                    a, this->col,
                    b, B.col,
                    0,
                    c, B.col);
    } else if constexpr (std::is_same<T, double>::value) {
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    this->row, B.col, this->col, 1,
                    a, this->col,
                    b, B.col,
                    0,
                    c, B.col);
    } else if constexpr (std::is_same<T, std::complex<float>>::value) {
        cblas_cgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    this->row, B.col, this->col, 1,
                    a, this->col,
                    b, B.col,
                    0,
                    c, B.col);
    } else if constexpr (std::is_same<T, std::complex<double>>::value) {
        cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    this->row, B.col, this->col, 1,
                    a, this->col,
                    b, B.col,
                    0,
                    c, B.col);
    } else {
        std::cerr << "type should be double/float/complex!" << std::endl;
        exit(-1);
    }
    Timer::end("Matrix", "blas_matmul");
    delete[] a, b, c;
    return Matrix<T>(this->row, B.col, c);
}


template<typename T>
Matrix<T> Matrix<T>::lapack_diago(const std::string &file, int out) {
    Timer::begin("Matrix", "lapack_diago");
    if (!this->isRSM()) {
        std::cerr << "Not RSM!" << std::endl;
        exit(-1);
    }
    int info, lwork;
    T wkopt;
    T w[this->row];
    T a[this->row * this->col];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            a[col * i + j] = this->p[i][j];
        }
    }

    if constexpr (std::is_same<T, double>::value) {
        lwork = -1;
        dsyev_("V", "U", &row, a, &col, w, &wkopt, &lwork, &info);
        lwork = (int) wkopt;
        T work[(int) wkopt];
        /* Solve eigenproblem */
        dsyev_("V", "U", &row, a, &col, w, work, &lwork, &info);
        /* Check for convergence */
        if (info > 0) {
            std::cerr << "The algorithm failed to compute eigenvalues." << std::endl;
            exit(-1);
        }
    } else if constexpr (std::is_same<T, float>::value) {
        lwork = -1;
        ssyev_("V", "U", &row, a, &col, w, &wkopt, &lwork, &info);
        lwork = (int) wkopt;
        T work[(int) wkopt];
        /* Solve eigenproblem */
        ssyev_("V", "U", &row, a, &col, w, work, &lwork, &info);
        /* Check for convergence */
        if (info > 0) {
            std::cerr << "The algorithm failed to compute eigenvalues." << std::endl;
            exit(-1);
        }
    }
    Matrix ans(row, col, a);
    if (out) {
        std::ofstream ofs{file.empty() ? "out.txt" : file, std::ios::app};
        ofs << "Mat:" << std::endl;
        ofs << *this << std::endl;
        ofs << "Eigenvalues" << std::endl;
        for (auto i: w) {
            ofs << std::setprecision(6) << std::fixed << i << " ";
        }
        ofs << std::endl;
        ofs << std::endl;
        ofs << "Eigenvectors (stored columnwise)" << std::endl;
        ofs << ans << std::endl;

        std::cout << "Mat:" << std::endl;
        std::cout << *this << std::endl;
        std::cout << "Eigenvalues" << std::endl;
        for (auto i: w) {
            std::cout << std::setprecision(6) << std::fixed << i << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Eigenvectors (stored columnwise)" << std::endl;
        std::cout << ans << std::endl;
    }
    Timer::end("Matrix", "lapack_diago");
    return ans;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other) {
    if (this == &other) {
        return *this;
    }
    for (int i = 0; i < this->row; i++) {
        delete[] p[i];
    }
    delete[] p;
    this->row = other.row;
    this->col = other.col;
    init();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            p[i][j] = other.p[i][j];
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const {
    if (this->col != other.get_col() or this->row != other.get_row()) {
        std::cerr << "Sizes of Two Matrix are not equal!" << std::endl;
        std::cerr << "Stop op" << std::endl;
        return *this;
    }
    Matrix<T> ans(row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            ans[i][j] = this->p[i][j] + other.p[i][j];
        }
    }
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const {
    if (this->col != other.get_col() or this->row != other.get_row()) {
        std::cerr << "Sizes of Two Matrix are not equal!" << std::endl;
        std::cerr << "Stop op" << std::endl;
        return *this;
    }
    Matrix<T> ans(row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            ans[i][j] = this->p[i][j] - other.p[i][j];
        }
    }
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const {
    Timer::begin("Matrix", "*");
    if (this->col != other.row) {
        std::cerr << "Size not fit!" << std::endl;
        std::cerr << "mat 1 has " << this->col << " cols and mat2 has " << other.row << " rows";
        std::cerr << "Stop op" << std::endl;
        return *this;
    }
    Matrix<T> ans(row, other.col);
    for (int k = 0; k < col; ++k) {
        for (int i = 0; i < row; ++i) {
            T r = this->p[i][k];
            for (int j = 0; j < other.col; ++j) {
                ans[i][j] += r * other.p[k][j];
            }
        }
    }
    Timer::end("Matrix", "*");
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix<T> &other) {
    *this = *this + other;
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-=(const Matrix<T> &other) {
    *this = *this - other;
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*=(const Matrix<T> &other) {
    *this = *this * other;
    return *this;
}

template<typename T>
T *Matrix<T>::operator[](int x) const {
    return p[x];
}

template<typename T>
void Matrix<T>::init() {
    p = new T *[this->row];
    for (int i = 0; i < this->row; ++i) {
        p[i] = new T[this->col];
    }
}

#endif //HW7_MATRIX_H
