#ifndef SYMMAT_H
#define SYMMAT_H

#include <Eigen/Core>
#include <iostream>

#define MATRIX(T) Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>

template <typename T>
class SymMat{
 public:

  SymMat(const Eigen::Ref<const MATRIX(T)>& m);

  SymMat(int length);

  T& operator()(int x, int y);

  int length() const;
  int size() const;

  template <typename Func>
    SymMat<T> zipWith(const SymMat<T>& m, Func func);

  SymMat<T> operator+(const SymMat<T>& m);
  SymMat<T> operator-(const SymMat<T>& m);

   template <typename Func> MATRIX(T)
     zipWith(const Eigen::Ref<const MATRIX(T)>& m, Func func);

   MATRIX(T) operator+(const Eigen::Ref<const MATRIX(T)>& m);
   MATRIX(T) operator-(const Eigen::Ref<const MATRIX(T)>& m);

 private:
  int m_length;
  int m_size;
  T** m_data;
};

#endif /* SYMMAT_H */
