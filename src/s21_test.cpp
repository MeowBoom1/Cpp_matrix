#include "s21_test.h"

using namespace std;

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

TEST(Test, constructor_11) {
  S21Matrix a = S21Matrix();
  int r = a.Get_Rows();
  int c = a.Get_Cols();
  ASSERT_EQ(r, 1);
  ASSERT_EQ(c, 1);
  ASSERT_EQ(a.GetNumber(0, 0), 0);
}

TEST(TestGroupName, constructor_RC) {
  S21Matrix b = S21Matrix(2, 2);
  int r = b.Get_Rows();
  int c = b.Get_Cols();
  ASSERT_EQ(r, 2);
  ASSERT_EQ(c, 2);
}

TEST(TestGroupName, copy_constructor) {
  S21Matrix b = S21Matrix(2, 2);
  S21Matrix bcopy = S21Matrix(b);
  int r = bcopy.Get_Rows();
  int c = bcopy.Get_Cols();
  ASSERT_EQ(r, 2);
  ASSERT_EQ(c, 2);
}

// TEST(TestGroupName, copy_constructor_perenosa) {
//   S21Matrix a = S21Matrix(2, 2);
//   S21Matrix bcopy = S21Matrix(std::move(a));
//   int r = bcopy.GetRows();
//   int c = bcopy.GetCols();
//   ASSERT_EQ(r, 2);
//   ASSERT_EQ(c, 2);
// }

TEST(TestGroupName, mutators) {
  S21Matrix b = S21Matrix(2, 2);
  b.Set_Rows(3);
  b.Set_Cols(1);
  int r = b.Get_Rows();
  int c = b.Get_Cols();
  ASSERT_EQ(r, 3);
  ASSERT_EQ(c, 1);
  b.SetRowsAndCols(1, 3);
  r = b.Get_Rows();
  c = b.Get_Cols();
  ASSERT_EQ(r, 1);
  ASSERT_EQ(c, 3);
}

TEST(TestGroupName, operator_EQ) {
  S21Matrix a = S21Matrix(1, 1);
  S21Matrix b = S21Matrix(1, 1);
  int res = a == b;
  int res1 = a.EqMatrix(b);
  int res2 = b.EqMatrix(a);
  ASSERT_EQ(res, 1);
  ASSERT_EQ(res1, 1);
  ASSERT_EQ(res2, 1);
  a(0, 0) = 1;
  b(0, 0) = 21;
  res = a == b;
  res1 = a.EqMatrix(b);
  res2 = b.EqMatrix(a);
  ASSERT_EQ(res, 0);
  ASSERT_EQ(res1, 0);
  ASSERT_EQ(res2, 0);
  a.SetRowsAndCols(2, 3);
  res = a == b;
  res1 = a.EqMatrix(b);
  res2 = b.EqMatrix(a);
  ASSERT_EQ(res, 0);
  ASSERT_EQ(res1, 0);
  ASSERT_EQ(res2, 0);
}

TEST(TestGroupName, operator_SUM) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = 10;
      b(i, j) = -10;
    }
  }
  S21Matrix d = S21Matrix(3, 3);
  d = a + b;
  int c = d.Get_Cols();
  int r = d.Get_Rows();
  ASSERT_EQ(c, 2);
  ASSERT_EQ(r, 2);
  S21Matrix e = S21Matrix(3, 3);
  e = a;
  e += b;
  a.SumMatrix(b);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      int g = d(i, j);
      ASSERT_EQ(g, 0);
      g = a(i, j);
      ASSERT_EQ(g, 0);
      g = e(i, j);
      ASSERT_EQ(g, 0);
    }
  }
}

TEST(TestGroupName, operator_SUB) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = i + j;
      b(i, j) = i + j;
    }
  }
  S21Matrix d = S21Matrix(3, 3);
  d = a - b;
  int c = d.Get_Cols();
  int r = d.Get_Rows();
  ASSERT_EQ(c, 2);
  ASSERT_EQ(r, 2);
  a.SubMatrix(b);
  b -= b;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      int g = d(i, j);
      ASSERT_EQ(g, 0);
      g = a(i, j);
      ASSERT_EQ(g, 0);
      g = b(i, j);
      ASSERT_EQ(g, 0);
    }
  }
}

TEST(TestGroupName, operator_MulNumber) {
  S21Matrix a = S21Matrix(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 12;
  a(1, 0) = 21;
  a(1, 1) = 11;
  S21Matrix b = S21Matrix(2, 2);
  S21Matrix c = S21Matrix(2, 2);
  S21Matrix d = S21Matrix(2, 2);
  b = a;
  c = a;
  d = a;
  a.MulNumber(4);
  b *= 4;
  c = c * 4.0;
  d = 4 * d;
  int res = a(0, 0);
  ASSERT_EQ(res, 4);
  res = b(0, 0);
  ASSERT_EQ(res, 4);
  res = c(0, 0);
  ASSERT_EQ(res, 4);
  res = d(0, 0);
  ASSERT_EQ(res, 4);
  res = a(1, 0);
  ASSERT_EQ(res, 84);
  res = b(1, 0);
  ASSERT_EQ(res, 84);
  res = c(1, 0);
  ASSERT_EQ(res, 84);
  res = d(1, 0);
  ASSERT_EQ(res, 84);
  res = a(0, 1);
  ASSERT_EQ(res, 48);
  res = b(0, 1);
  ASSERT_EQ(res, 48);
  res = c(0, 1);
  ASSERT_EQ(res, 48);
  res = d(0, 1);
  ASSERT_EQ(res, 48);
  res = a(1, 1);
  ASSERT_EQ(res, 44);
  res = b(1, 1);
  ASSERT_EQ(res, 44);
  res = c(1, 1);
  ASSERT_EQ(res, 44);
  res = d(1, 1);
  ASSERT_EQ(res, 44);
}

TEST(TestGroupName, operator_MulMatrix) {
  S21Matrix a = S21Matrix(3, 4);
  S21Matrix b = S21Matrix(4, 5);
  for (int i = 0; i < a.Get_Rows(); i++) {
    for (int j = 0; j < a.Get_Cols(); j++) {
      a(i, j) = i + j;
    }
  }
  for (int i = 0; i < b.Get_Rows(); i++) {
    for (int j = 0; j < b.Get_Cols(); j++) {
      b(i, j) = i + j;
    }
  }
  a.MulMatrix(b);
  int res = 0;
  res = a(0, 0);
  ASSERT_EQ(res, 14);
  res = a(0, 1);
  ASSERT_EQ(res, 20);
  res = a(1, 0);
  ASSERT_EQ(res, 20);
  res = a(2, 0);
  ASSERT_EQ(res, 26);
  res = a(0, 2);
  ASSERT_EQ(res, 26);
  res = a(1, 1);
  ASSERT_EQ(res, 30);
  res = a(2, 1);
  ASSERT_EQ(res, 40);
  res = a(1, 2);
  ASSERT_EQ(res, 40);
  res = a(2, 2);
  ASSERT_EQ(res, 54);
  res = a(0, 3);
  ASSERT_EQ(res, 32);
  res = a(0, 4);
  ASSERT_EQ(res, 38);
  res = a(1, 3);
  ASSERT_EQ(res, 50);
  res = a(1, 4);
  ASSERT_EQ(res, 60);
  res = a(2, 3);
  ASSERT_EQ(res, 68);
  res = a(2, 4);
  ASSERT_EQ(res, 82);
  S21Matrix c = S21Matrix(5, 4);
  b *= c;
  for (int i = 0; i < b.Get_Rows(); i++) {
    for (int j = 0; j < b.Get_Cols(); j++) {
      res = b(i, j);
      ASSERT_EQ(res, 0);
    }
  }
  b.SetRowsAndCols(5, 5);
  for (int i = 0; i < b.Get_Rows(); i++) {
    for (int j = 0; j < b.Get_Cols(); j++) {
      if (i == j) {
        b(i, j) = 1;
      }
    }
  }
  c = a;
  a = a * b;
  for (int i = 0; i < a.Get_Rows(); i++) {
    for (int j = 0; j < a.Get_Cols(); j++) {
      res = a(i, j);
      int res_c = c(i, j);
      ASSERT_EQ(res, res_c);
    }
  }
}

TEST(TestGroupName, Transpose) {
  S21Matrix a = S21Matrix(1, 1);
  S21Matrix b = S21Matrix(5, 5);
  for (int i = 0; i < b.Get_Rows(); i++) {
    for (int j = 0; j < b.Get_Cols(); j++) {
      b(i, j) = i * 2 + j * 5 - 2;
    }
  }
  S21Matrix d = S21Matrix(12, 21);
  for (int i = 0; i < d.Get_Rows(); i++) {
    for (int j = 0; j < d.Get_Cols(); j++) {
      d(i, j) = i * 2 + j * 5 - 2;
    }
  }
  S21Matrix e = S21Matrix(21, 12);
  for (int i = 0; i < e.Get_Rows(); i++) {
    for (int j = 0; j < e.Get_Cols(); j++) {
      e(i, j) = i * 2 + j * 5 - 2;
    }
  }

  S21Matrix at = S21Matrix();
  S21Matrix bt = S21Matrix();
  S21Matrix dt = S21Matrix();
  S21Matrix et = S21Matrix();

  at = a.Transpose();
  bt = b.Transpose();
  dt = d.Transpose();
  et = e.Transpose();

  int res = 0;
  int asc = 0;

  res = at.Get_Cols();
  asc = a.Get_Rows();
  ASSERT_EQ(res, asc);
  res = at.Get_Rows();
  asc = a.Get_Cols();
  ASSERT_EQ(res, asc);

  res = bt.Get_Cols();
  asc = b.Get_Rows();
  ASSERT_EQ(res, asc);
  res = bt.Get_Rows();
  asc = b.Get_Cols();
  ASSERT_EQ(res, asc);

  res = dt.Get_Cols();
  asc = d.Get_Rows();
  ASSERT_EQ(res, asc);
  res = dt.Get_Rows();
  asc = d.Get_Cols();
  ASSERT_EQ(res, asc);

  res = et.Get_Cols();
  asc = e.Get_Rows();
  ASSERT_EQ(res, asc);
  res = et.Get_Rows();
  asc = e.Get_Cols();
  ASSERT_EQ(res, asc);

  res = at(0, 0);
  asc = a(0, 0);
  ASSERT_EQ(res, asc);

  for (int i = 0; i < bt.Get_Rows(); i++) {
    for (int j = 0; j < bt.Get_Cols(); j++) {
      res = bt(i, j);
      asc = b(j, i);
      ASSERT_EQ(res, asc);
    }
  }

  for (int i = 0; i < et.Get_Rows(); i++) {
    for (int j = 0; j < et.Get_Cols(); j++) {
      res = et(i, j);
      asc = e(j, i);
      ASSERT_EQ(res, asc);
    }
  }

  for (int i = 0; i < dt.Get_Rows(); i++) {
    for (int j = 0; j < dt.Get_Cols(); j++) {
      res = dt(i, j);
      asc = d(j, i);
      ASSERT_EQ(res, asc);
    }
  }
}

TEST(TestGroupName, Determinant) {
  double res = 0;
  S21Matrix a = S21Matrix(1, 1);
  a(0, 0) = 21;
  res = a.Determinant();
  ASSERT_EQ(res, 21);

  S21Matrix b = S21Matrix(2, 2);
  b(0, 0) = 10;
  b(0, 1) = 20;
  b(1, 0) = 30;
  b(1, 1) = 40;
  res = b.Determinant();
  ASSERT_EQ(res, -200);

  S21Matrix d = S21Matrix(6, 6);
  for (int i = 0; i < d.Get_Rows(); i++) {
    for (int j = 0; j < d.Get_Cols(); j++) {
      d(i, j) = i * 2 + j * 5 - 2;
    }
  }
  res = d.Determinant();
  ASSERT_EQ(res, 0);

  S21Matrix e = S21Matrix(5, 5);
  for (int i = 0; i < e.Get_Rows(); i++) {
    for (int j = 0; j < e.Get_Cols(); j++) {
      if (i == j) {
        e(i, j) = 1;
      }
    }
  }
  res = e.Determinant();
  ASSERT_EQ(res, 1);

  S21Matrix f = S21Matrix(5, 5);
  f(0, 0) = 1;
  f(0, 1) = 2;
  f(0, 2) = 3;
  f(0, 3) = 4;
  f(0, 4) = 5;

  f(1, 0) = 6;
  f(1, 1) = 7;
  f(1, 2) = 4;
  f(1, 3) = 9;
  f(1, 4) = 10;

  f(2, 0) = 20;
  f(2, 1) = 12;
  f(2, 2) = 13;
  f(2, 3) = 14;
  f(2, 4) = 15;

  f(3, 0) = 16;
  f(3, 1) = 17;
  f(3, 2) = 18;
  f(3, 3) = 4;
  f(3, 4) = 20;

  f(4, 0) = 1;
  f(4, 1) = 2;
  f(4, 2) = 5;
  f(4, 3) = 3;
  f(4, 4) = 1;

  res = f.Determinant();
  ASSERT_EQ(res, -16170);
}

TEST(TestGroupName, InverseMatrix) {
  double res = 0;

  S21Matrix a = S21Matrix(1, 1);
  a(0, 0) = 50;
  S21Matrix ares = S21Matrix();
  ares = a.InverseMatrix();
  res = ares(0, 0);
  ASSERT_DOUBLE_EQ(res, 0.02);
  ares.MulMatrix(a);
  res = ares(0, 0);
  ASSERT_DOUBLE_EQ(res, 01);

  S21Matrix f = S21Matrix(5, 5);
  f(0, 0) = 1;
  f(0, 1) = 2;
  f(0, 2) = 3;
  f(0, 3) = 4;
  f(0, 4) = 5;

  f(1, 0) = 6;
  f(1, 1) = 7;
  f(1, 2) = 4;
  f(1, 3) = 9;
  f(1, 4) = 10;

  f(2, 0) = 20;
  f(2, 1) = 12;
  f(2, 2) = 13;
  f(2, 3) = 14;
  f(2, 4) = 15;

  f(3, 0) = 16;
  f(3, 1) = 17;
  f(3, 2) = 18;
  f(3, 3) = 4;
  f(3, 4) = 20;

  f(4, 0) = 1;
  f(4, 1) = 2;
  f(4, 2) = 5;
  f(4, 3) = 3;
  f(4, 4) = 1;

  S21Matrix fres = S21Matrix();
  fres = f.InverseMatrix();
  fres.MulMatrix(f);

  for (int i = 0; i < fres.Get_Rows(); i++) {
    for (int j = 0; j < fres.Get_Cols(); j++) {
      res = fres(i, j);
      if (i == j) {
        ASSERT_DOUBLE_EQ(res, 1);
      } else {
        ASSERT_NEAR(res, 0, 0.0000001);
      }
    }
  }
}

TEST(TestGroupName, ERROR) {
  try {
    S21Matrix f = S21Matrix(-5, 5);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix f = S21Matrix(5, -5);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix f = S21Matrix(5, 5);
    f(-1, 2) = 10;
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix f = S21Matrix(5, 5);
    f(1, -2) = 10;
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix f = S21Matrix(5, 5);
    f.Set_Rows(-5);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix f = S21Matrix(5, 5);
    f.Set_Cols(-5);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix f = S21Matrix(5, 5);
    f.SetRowsAndCols(-5, 6);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix f = S21Matrix(5, 5);
    f.SetRowsAndCols(5, -6);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(5, 5);
    S21Matrix b = S21Matrix(1, 1);
    a.SumMatrix(b);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(5, 5);
    S21Matrix b = S21Matrix(1, 1);
    b.SumMatrix(a);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(5, 5);
    S21Matrix b = S21Matrix(1, 1);
    a.SubMatrix(b);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(5, 5);
    S21Matrix b = S21Matrix(1, 1);
    b.SubMatrix(a);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(5, 5);
    a.~S21Matrix();
    a.MulNumber(2);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(5, 5);
    S21Matrix b = S21Matrix(5, 5);
    a.~S21Matrix();
    a.MulMatrix(b);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(5, 5);
    S21Matrix b = S21Matrix(5, 5);
    a.~S21Matrix();
    b.MulMatrix(a);
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(2, 5);
    a.~S21Matrix();
    a.Transpose();
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(2, 5);
    a.Determinant();
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(2, 5);
    a.CalcComplements();
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(2, 5);
    a.InverseMatrix();
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }

  try {
    S21Matrix a = S21Matrix(2, 2);
    a.InverseMatrix();
    ASSERT_EQ(1, 0);
  } catch (const char* err) {
    ASSERT_EQ(1, 1);
  }
}