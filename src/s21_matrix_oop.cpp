#include "s21_matrix_oop.hpp"

S21Matrix::S21Matrix() {
  rows_ = 1;
  cols_ = 1;
  matrix_ = new double *[rows_];
  matrix_[0] = new double[cols_];
  matrix_[0][0] = 0;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = 0;
      }
    }
  } else {
    throw "S21Matrix constructor ERROR";
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != NULL) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = NULL;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::CreateMatrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    if (rows != rows_ || cols != cols_) {
      if (matrix_[0] != NULL) {
        this->~S21Matrix();
      }
      rows_ = rows;
      cols_ = cols;
      matrix_ = new double *[rows_];
      for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_];
      }
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = 0;
      }
    }
  }
}

bool S21Matrix::CheckM() {
  return ((rows_ > 0) && (cols_ > 0) && matrix_ != NULL);
}

bool S21Matrix::CheckOther(const S21Matrix &other) {
  return ((rows_ == other.rows_) && (cols_ == other.cols_) && matrix_ != NULL);
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = 1;
  if (this->CheckM() && this->CheckOther(other)) {
    for (int i = 0; (i < rows_) && result; i++) {
      for (int j = 0; (j < cols_) && result; j++) {
        if (labs((matrix_[i][j] - other.matrix_[i][j])) > 1e-7) {
          result = 0;
        }
      }
    }
  } else {
    result = 0;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->CheckM() && this->CheckOther(other)) {
    for (int i = 0; (i < rows_); i++) {
      for (int j = 0; (j < cols_); j++) {
        matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
      }
    }
  } else {
    throw "SumMatrix ERROR";
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->CheckM() && this->CheckOther(other)) {
    for (int i = 0; (i < rows_); i++) {
      for (int j = 0; (j < cols_); j++) {
        matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
      }
    }
  } else {
    throw "SubMatrix ERROR";
  }
}

void S21Matrix::MulNumber(const double num) {
  if (this->CheckM()) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = matrix_[i][j] * num;
      }
    }
  } else {
    throw "MulNumber ERROR";
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->CheckM() && cols_ == other.rows_ && other.cols_ > 0) {
    S21Matrix temp = S21Matrix(*this);
    this->CreateMatrix(temp.rows_, other.cols_);
    for (int i = 0; i < temp.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        matrix_[i][j] = 0;
        for (int k = 0; k < temp.cols_; k++) {
          matrix_[i][j] += temp.matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
  } else {
    throw "MulMatrix ERROR";
  }
}

S21Matrix S21Matrix::Transpose() {
  if (!this->CheckM()) {
    throw "Transpose ERROR";
  }
  S21Matrix result = S21Matrix(cols_, rows_);
  if (this->CheckM()) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result.matrix_[j][i] = matrix_[i][j];
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double result = 0;
  if (this->CheckM() && rows_ == cols_) {
    if (rows_ == 1)
      result = matrix_[0][0];
    else if (rows_ == 2)
      result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    else {
      S21Matrix temp = S21Matrix(rows_ - 1, cols_ - 1);
      for (int i = 0; i < rows_; i++) {
        temp.Minor(*this, 0, i);
        result += pow(-1, i) * matrix_[0][i] * temp.Determinant();
      }
      temp.~S21Matrix();
    }
  } else {
    throw "Determinant ERROR";
  }
  return result;
}

void S21Matrix::Minor(const S21Matrix &other, int k, int l) {
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      if ((i < k) && (j < l)) {
        matrix_[i][j] = other.matrix_[i][j];
      } else if ((i > k) && (j < l)) {
        matrix_[i - 1][j] = other.matrix_[i][j];
      } else if ((i < k) && (j > l)) {
        matrix_[i][j - 1] = other.matrix_[i][j];
      } else if ((i > k) && (j > l)) {
        matrix_[i - 1][j - 1] = other.matrix_[i][j];
      }
    }
  }
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result = S21Matrix(rows_, cols_);
  if (this->CheckM() && rows_ == cols_ && rows_ > 1) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix temp = S21Matrix(rows_ - 1, cols_ - 1);
        temp.Minor(*this, i, j);
        result.matrix_[i][j] = pow(-1., i + j) * temp.Determinant();
      }
    }
  } else {
    throw "CalcComplements ERROR";
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix result = S21Matrix(rows_, cols_);
  if (this->CheckM() && rows_ == cols_) {
    double det = this->Determinant();
    if (det != 0) {
      if (rows_ != 1) {
        result = this->CalcComplements();
        result = result.Transpose();
        result.MulNumber(1 / det);
      } else {
        result.matrix_[0][0] = 1 / matrix_[0][0];
      }
    } else {
      throw "InverseMatrix ERROR: Determinant = 0";
    }
  } else {
    throw "InverseMatrix ERROR";
  }
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result = S21Matrix(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result = S21Matrix(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result = S21Matrix(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix operator*(double num, S21Matrix &other) {
  S21Matrix result = S21Matrix(other);
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(S21Matrix &other, double num) {
  S21Matrix result = S21Matrix(other);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      if (matrix_ != NULL) {
        this->~S21Matrix();
      }
      rows_ = other.rows_;
      cols_ = other.cols_;
      matrix_ = new double *[rows_];
      for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_];
      }
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return (*this);
}

void S21Matrix::operator+=(const S21Matrix &other) { this->SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix &other) { this->SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix &other) { this->MulMatrix(other); }

void S21Matrix::operator*=(const double num) { this->MulNumber(num); }

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw "operator() INDEX ERROR: INDEX IS OUT OF RANGE";
  }
  return matrix_[row][col];
}

int S21Matrix::Get_Rows() { return rows_; }
int S21Matrix::Get_Cols() { return cols_; }

void S21Matrix::Set_Rows(int rows) {
  S21Matrix result(rows, cols_);
  if (rows > rows_) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        if (i >= rows_)
          result.matrix_[i][j] = 0;
        else
          result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}
void S21Matrix::Set_Cols(int cols) {
  S21Matrix result(rows_, cols);
  if (cols > cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols; j++) {
        if (j >= cols_)
          result.matrix_[i][j] = 0;
        else
          result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::SetRowsAndCols(int row, int col) {
  if (row > 0 && col > 0) {
    S21Matrix temp = S21Matrix(*this);
    this->CreateMatrix(row, col);
    for (int i = 0; i < temp.rows_ && i < row; i++) {
      for (int j = 0; j < temp.cols_ && j < col; j++) {
        matrix_[i][j] = temp.matrix_[i][j];
      }
    }
  } else {
    throw "SetRowsAndCols ERROR";
  }
}

double S21Matrix::GetNumber(int row, int col) {
  if (row <= rows_ && col <= cols_) {
    return matrix_[row][col];
  } else
    throw "GetNumber INDEX ERROR: INDEX IS OUT OF RANGE";
}