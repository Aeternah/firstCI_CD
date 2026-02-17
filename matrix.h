#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>

class Matrix {
protected:
    std::vector<std::vector<int>> data;
    int rows;
    int cols;

public:
    // Конструкторы
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);

    // Деструктор
    virtual ~Matrix() = default;

    // Операторы
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(int scalar) const;
    Matrix operator*(const Matrix& other) const;
    Matrix& operator=(const Matrix& other);
    bool operator==(const Matrix& other) const;

    // Дружественные операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);

    // Методы
    int getMaxValue() const;
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getValue(int row, int col) const { return data[row][col]; }
    void setValue(int row, int col, int value) { data[row][col] = value; }

    // Вспомогательные методы
    void fillRandom();
    void resize(int new_rows, int new_cols);
};

class SquareMatrix : public Matrix {
public:
    // Конструкторы
    SquareMatrix();
    SquareMatrix(int size);
    SquareMatrix(const SquareMatrix& other);
    SquareMatrix(const Matrix& other);

    // Методы квадратной матрицы
    int determinant() const;
    bool isSymmetric() const;
    SquareMatrix power(int exponent) const;

private:
    // Вспомогательный метод для вычисления определителя
    int calculateDeterminant(const std::vector<std::vector<int>>& mat) const;
};

#endif