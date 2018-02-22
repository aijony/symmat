#ifndef SYMMAT_H
#define SYMMAT_H

#include <Eigen/Core>

#define MATRIX(T) Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>

template <typename T>
class SymMat{
 public:

  /// Constructors
  SymMat(const Eigen::Ref<const MATRIX(T)>& m);

  SymMat(int length);

  /// Accessors
  T& operator()(int x, int y);
  T& operator()(int y, int x) const;

  /// General Functions
  template <typename Func>
  SymMat<T> map(Func func);

  template <typename Mat>
  auto mult(const Mat& m);

  template <typename Func>
  SymMat<T> zipWith(const SymMat<T>& m, Func func);

  template <typename Func, typename EMat>
  EMat zipWith(const EMat& m, Func func);

  template <typename Func, typename Mat>
  bool mapBool(const Mat& m, Func func);

  // Comparison Operators
  template <typename Mat>
  bool operator==(const Mat& m);
  template <typename Mat>
  bool operator!=(const Mat& m);

  // Arithmetic Operators
  template <typename Mat>
  Mat operator+(const Mat& m);

  template <typename Mat>
  Mat operator-(const Mat& m);

  template <typename Mat>
  auto operator*(const Mat& m);

  SymMat<T> operator*(T a);

  /// Getters
  int length() const;
  int rows() const;
  int cols() const;
  int size() const;

 private:
  int m_length;
  int m_size;
  T** m_data;
};

/// Initialization File
#include "SymMat.tpp"

#endif /* SYMMAT_H */
