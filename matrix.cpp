#include "matrix.h"
#include <algorithm>
#include <cmath>

// Конструктор по умолчанию (2x2 нулевая матрица)
Matrix::Matrix() {
    rows = 2;
    cols = 2;
    data.resize(rows, std::vector<int>(cols, 0));
}

// Конструктор с параметрами (матрица заданного размера со случайными значениями)
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
    data.resize(rows, std::vector<int>(cols));
    fillRandom();
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = other.data;
}

// Оператор сложения матриц
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }
    
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Оператор вычитания матриц
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
    }
    
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// Оператор умножения матрицы на скаляр
Matrix Matrix::operator*(int scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

// Оператор умножения матриц
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Number of columns in first matrix must equal number of rows in second matrix");
    }
    
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

// Оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }
    return *this;
}

// Оператор сравнения матриц
bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Matrix& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            is >> matrix.data[i][j];
        }
    }
    return is;
}

// Метод для нахождения максимального значения в матрице
int Matrix::getMaxValue() const {
    if (data.empty() || data[0].empty()) {
        throw std::runtime_error("Matrix is empty");
    }
    
    int max_val = data[0][0];
    for (const auto& row : data) {
        for (int val : row) {
            if (val > max_val) {
                max_val = val;
            }
        }
    }
    return max_val;
}

// Заполнение матрицы случайными значениями
void Matrix::fillRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 100);
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = distrib(gen);
        }
    }
}

// Изменение размера матрицы
void Matrix::resize(int new_rows, int new_cols) {
    if (new_rows <= 0 || new_cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
    
    data.resize(new_rows);
    for (auto& row : data) {
        row.resize(new_cols, 0);
    }
    rows = new_rows;
    cols = new_cols;
}

// Реализация методов SquareMatrix

// Конструктор по умолчанию (2x2)
SquareMatrix::SquareMatrix() : Matrix(2, 2) {}

// Конструктор с параметром размера
SquareMatrix::SquareMatrix(int size) : Matrix(size, size) {}

// Конструктор копирования
SquareMatrix::SquareMatrix(const SquareMatrix& other) : Matrix(other) {}

// Конструктор из обычной матрицы
SquareMatrix::SquareMatrix(const Matrix& other) : Matrix(other) {
    if (other.getRows() != other.getCols()) {
        throw std::invalid_argument("Matrix must be square to convert to SquareMatrix");
    }
}

// Вычисление определителя
int SquareMatrix::determinant() const {
    return calculateDeterminant(data);
}

// Проверка симметричности матрицы
bool SquareMatrix::isSymmetric() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < i; ++j) {
            if (data[i][j] != data[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// Возведение матрицы в степень
SquareMatrix SquareMatrix::power(int exponent) const {
    if (exponent < 0) {
        throw std::invalid_argument("Exponent must be non-negative");
    }
    
    SquareMatrix result(rows);
    SquareMatrix temp(*this);
    
    // Инициализация результата как единичной матрицы
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            result.setValue(i, j, (i == j) ? 1 : 0);
        }
    }
    
    // Алгоритм быстрого возведения в степень
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = result * temp;
        }
        temp = temp * temp;
        exponent /= 2;
    }
    
    return result;
}

// Вспомогательный метод для вычисления определителя (рекурсивный)
int SquareMatrix::calculateDeterminant(const std::vector<std::vector<int>>& mat) const {
    int n = mat.size();
    if (n == 1) {
        return mat[0][0];
    }
    
    if (n == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
    
    int det = 0;
    for (int col = 0; col < n; ++col) {
        std::vector<std::vector<int>> submat(n-1, std::vector<int>(n-1));
        
        for (int i = 1; i < n; ++i) {
            int sub_col = 0;
            for (int j = 0; j < n; ++j) {
                if (j == col) continue;
                submat[i-1][sub_col++] = mat[i][j];
            }
        }
        
        int sign = (col % 2 == 0) ? 1 : -1;
        det += sign * mat[0][col] * calculateDeterminant(submat);
    }
    
    return det;
}