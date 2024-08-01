#ifndef S21_MATRIX_OOP_HPP
#define S21_MATRIX_OOP_HPP

#include <cmath>
#include <exception>
#include <iostream>

// #define SUCCES 1
// #define FAILURE 0
// #define PRECISION 1e-7

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  bool CheckM();
  bool CheckOther(const S21Matrix& other);

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  friend S21Matrix operator*(double num, S21Matrix& other);
  friend S21Matrix operator*(S21Matrix& other, double num);

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(const double num);
  double& operator()(int row, int col);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  void CreateMatrix(int rows, int cols);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  void Minor(const S21Matrix& other, int, int);
  S21Matrix InverseMatrix();

  double GetNumber(int row, int col);
  void SetRowsAndCols(int row, int col);
  int Get_Rows();
  int Get_Cols();
  void Set_Rows(int rows);
  void Set_Cols(int cols);
};

S21Matrix operator*(double, S21Matrix& other);
S21Matrix operator*(S21Matrix& other, double);

#endif