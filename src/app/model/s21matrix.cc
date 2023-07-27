#include "s21matrix.h"

namespace s21 {

S21Matrix::S21Matrix() : rows_(2), columns_(2) { InitMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), columns_(cols) {
  InitMatrix();
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    DeleteMatrix();
    rows_ = other.rows_;
    columns_ = other.columns_;
    InitMatrix();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < columns_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

double& S21Matrix::operator()(int row, int col) { return matrix_[row][col]; }

void S21Matrix::SubMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

int S21Matrix::get_columns() { return columns_; }

int S21Matrix::get_rows() { return rows_; }

void S21Matrix::InitMatrix() {
  matrix_.resize(rows_);
  for (int i = 0; i < rows_; ++i) {
    matrix_[i].resize(columns_);
  }
}

void S21Matrix::DeleteMatrix() {
  for (size_t i = 0; i < matrix_.size(); ++i) {
    matrix_[i].clear();
  }
  matrix_.clear();
  rows_ = 0;
  columns_ = 0;
}

void S21Matrix::FillTargetMatrix(int target) { matrix_[target - 1][0] = 1; }

void S21Matrix::VectorToMatrix(std::vector<double> input_vector) {
  for (size_t i = 0; i < input_vector.size(); ++i) {
    matrix_[i][0] = input_vector[i];
  }
}

std::vector<double> S21Matrix::OutputMatrixToVector() {
  std::vector<double> res_vector;
  for (int i = 0; i < get_rows(); ++i) {
    res_vector.push_back(matrix_[i][0]);
  }
  return res_vector;
}

}  // namespace s21
