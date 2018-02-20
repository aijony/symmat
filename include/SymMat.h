#ifndef SYMMAT_H
#define SYMMAT_H

#include <Eigen/Core>

template <typename T>
class SymMat{
 public:

  SymMat(const Eigen::Ref<const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>& m);

  SymMat(int length);

  T& operator()(int x, int y);

  int length() const;
  int size() const;

  template <typename Func>
    SymMat<T> zipWith(const SymMat<T>& m, Func func);
  bool checkDim(const SymMat<T>& m);

  SymMat<T> operator+(const SymMat<T>& m);
  SymMat<T> operator-(const SymMat<T>& m);

 private:
  int m_length;
  int m_size;
  T** m_data;

};

#endif /* SYMMAT_H */
