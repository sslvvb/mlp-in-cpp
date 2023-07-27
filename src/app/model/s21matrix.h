#ifndef CPP7_MLP_0_SRC_MODEL_S21MATRIX_H_
#define CPP7_MLP_0_SRC_MODEL_S21MATRIX_H_

#include <vector>

namespace s21 {

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other) = default;
  S21Matrix(S21Matrix&& other) = default;
  ~S21Matrix() = default;

  double& operator()(int row, int col);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);

  int get_columns();
  int get_rows();

  void SubMatrix(const S21Matrix& other);
  void FillTargetMatrix(int target);
  void VectorToMatrix(std::vector<double> input_vector);
  std::vector<double> OutputMatrixToVector();

 private:
  std::vector<std::vector<double>> matrix_{};
  int rows_{}, columns_{};

  void InitMatrix();
  void DeleteMatrix();
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_MODEL_S21MATRIX_H_
