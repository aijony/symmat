#include "SymMat.h"

#include <Eigen/Core>
#include <stdexcept>
#include <iostream>

using Eigen::Ref;
using Eigen::MatrixBase;

template <typename T>
SymMat<T>::SymMat(const Ref<const MATRIX(T)>& m){
  if(m.cols() != m.rows()){
    std::logic_error("Matrix is not square");
  }
  m_length = m.cols();

  m_size = 0;
  m_data = new T*[m_length];
  for (int i = 0; i < length(); i ++){
    m_data[i] = new T[m_length - i];
    for (int j = 0; j + i < m_length; j++){
      m_data[i][j] = m(i, j + i);
      m_size++;
    }
  }
}

template <typename T>
SymMat<T>::SymMat(int length){
  m_length = length;

  m_size = 0;
  m_data = new T*[m_length];
  for (int i = 0; i < m_length; i ++){
    m_data[i] = new T[m_length - i];
    for (int j = 0; j + i < m_length; j++){
      m_size++;
    }
  }
}

template <typename T>
T& SymMat<T>::operator()(int y, int x){
  if(x >= length() || y >= length() || x < 0 || y < 0){
    throw std::out_of_range("One or more index is out of range");
  }
  if(y > x){
    return m_data[x][y];
  }
  return m_data[y][x];
}

template <typename T>
int SymMat<T>::length() const{
  return m_length;
}

template <typename T>
int SymMat<T>::size() const{
  return m_size;
}

template <typename T>
template <typename Func>
SymMat<T> SymMat<T>::zipWith(const SymMat<T>& m, Func func){
  if(length() != m.length()){
    std::logic_error("Dimension mismatch");
  }

  SymMat<T> outM(length());

  for(int i = 0; i < length(); i++){
    for(int j = 0; j + i < length(); j++){
      outM.m_data[i][j] = func(this->m_data[i][j], m.m_data[i][j]);
    }
  }
  return outM;
}

template <typename T>
SymMat<T> SymMat<T>::operator+(const SymMat<T>& m){
  return zipWith(m, [] (T x, T y) -> T {return (x + y);});
}

template <typename T>
SymMat<T> SymMat<T>::operator-(const SymMat<T>& m){
  return zipWith(m, [] (T x, T y) -> T {return (x - y);});
}

template <typename T>
template <typename Func>
MATRIX(T)
  SymMat<T>::zipWith(const  Eigen::Ref<const MATRIX(T)>& m, Func func){
  if(this->length() != m.rows() || this->length() != m.cols()){
    std::logic_error("Dimension mismatch or not square");
  }

  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> outM(length(), length());

   for(int i = 0; i < outM.cols(); i++){
     for(int j = 0; j < outM.rows(); j++){
       outM(i, j) = func(this->operator()(i, j), m(i, j));
     }
   }
  return outM;
}

template <typename T>
MATRIX(T) SymMat<T>::operator+(const Eigen::Ref<const MATRIX(T)>& m){
  return zipWith(m, [] (T x, T y) -> T {return (x + y);});
}

template <typename T>
MATRIX(T) SymMat<T>::operator-(const Eigen::Ref<const MATRIX(T)>& m){
  return zipWith(m, [] (T x, T y) -> T {return (x - y);});
}

template class SymMat<int>;
template class SymMat<float>;
template class SymMat<double>;
