#include "matrix.h"
#include <iostream>

int main() {
    try {
        // Демонстрация работы с классом Matrix
        std::cout << "=== Matrix ===" << std::endl;

        Matrix m10;
        
        // Создание матриц
        Matrix m1(2, 3);
        Matrix m2(2, 3);
        Matrix m3(3, 2);
        
        std::cout << "Matrix m1 (2x3):" << std::endl << m1;
        std::cout << "Matrix m2 (2x3):" << std::endl << m2;
        std::cout << "Matrix m3 (3x2):" << std::endl << m3;
        
        // Операции с матрицами
        Matrix sum = m1 + m2;
        std::cout << "m1 + m2:" << std::endl << sum;
        
        Matrix diff = m1 - m2;
        std::cout << "m1 - m2:" << std::endl << diff;
        
        Matrix scaled = m1 * 5;
        std::cout << "m1 * 5:" << std::endl << scaled;
        
        Matrix product = m1 * m3;
        std::cout << "m1 * m3:" << std::endl << product;
        
        // Максимальное значение
        std::cout << "Max value in m1: " << m1.getMaxValue() << std::endl;
        
        // Сравнение матриц
        std::cout << "m1 == m2: " << (m1 == m2) << std::endl;
        
        // Демонстрация работы с классом SquareMatrix
        std::cout << "\n=== SquareMatrix ===" << std::endl;
        
        // Создание квадратных матриц
        SquareMatrix sm1(3);
        SquareMatrix sm2(3);
        
        std::cout << "SquareMatrix sm1 (3x3):" << std::endl << sm1;
        std::cout << "SquareMatrix sm2 (3x3):" << std::endl << sm2;
        
        // Операции с квадратными матрицами
        std::cout << "Determinant of sm1: " << sm1.determinant() << std::endl;
        std::cout << "Is sm1 symmetric? " << sm1.isSymmetric() << std::endl;
        
        SquareMatrix sm_pow = sm1.power(3);
        std::cout << "sm1^3:" << std::endl << sm_pow;
        
        // Преобразование Matrix в SquareMatrix
        Matrix m4(4, 4);
        SquareMatrix sm3(m4);
        std::cout << "Converted SquareMatrix sm3 (4x4):" << std::endl << sm3;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}