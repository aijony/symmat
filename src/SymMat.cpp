#include "SymMat.h"
#include <stdexcept>
#include <Eigen/Core>

using Eigen::Ref;
using Eigen::MatrixBase;

/**
   Constructor for SymMat class.
   Takes an Eigen::Matrix as an input.
 */
template <typename T>
SymMat<T>::SymMat(const Ref<const MATRIX(T)>& m){
  if(m.cols() != m.rows()){
    throw std::logic_error("Matrix is not square");
  }
  m_length = m.cols();

  m_size = 0;
  m_data = new T*[m_length];
  for (int i = 0; i < length(); i ++){
    m_data[i] = new T[i];
    for (int j = i; j < length(); j++){
      m_data[i][j] = m(j, i);
      m_size++;
    }
  }
}

/**
   Default constructor for SymMat class.
   Just allocates the memory
 */
template <typename T>
SymMat<T>::SymMat(int length){
  m_length = length;

  m_size = 0;
  m_data = new T*[m_length];
  for (int i = 0; i < m_length; i ++){
    m_data[i] = new T[m_length - i];
    for (int j = i; j < m_length; j++){
      m_size++;
    }
  }
}

/**
   Non-const accessor for SymMat.
   Note: m(x, y) = m(y, x)
 */
template <typename T>
T& SymMat<T>::operator()(int y, int x){
  // Cast away const
  return const_cast<T&>(static_cast<const SymMat<T>*>(this)->operator()(y,x));
}

/**
   Const accessor for SymMat.
   Note: m(x, y) = m(y, x)
 */
template <typename T>
T& SymMat<T>::operator()(int y, int x) const{
  if(x >= length() || y >= length() || x < 0 || y < 0){
    throw std::out_of_range("One or more index is out of range");
  }
  // Flips coordinates to corresponding element
  if(x < y){
    return m_data[x][y];
  }
  return m_data[y][x];
}


/**
   Maps an function across every element in SymMat.
   Returns a new SymMat
 */
template <typename T>
template <typename Func>
SymMat<T> SymMat<T>::map(Func func){

  SymMat<T> outM(length());

  for(int i = 0; i < rows(); i++){
    for (int j = i; j < cols(); j++){
      outM.m_data[i][j] = func(this->m_data[i][j]);
    }
  }
  return outM;
}

/**
   Scaler Multiplication
   Input must be cast as matching the matrix type.
   Example:
     SymMat<float> m(1);
     m * (float)2;
 */
template <typename T>
SymMat<T> SymMat<T>::operator*(T a){
  return map([a] (T x) -> T {return (x * a);});
}


template <typename T>
int SymMat<T>::length() const{
  return m_length;
}

template <typename T>
int SymMat<T>::rows() const{
  return m_length;
}

template <typename T>
int SymMat<T>::cols() const{
  return m_length;
}

template <typename T>
int SymMat<T>::size() const{
  return m_size;
}

/// Instantiate all types of SymMat
template class SymMat<float>;
template class SymMat<double>;
template class SymMat<int>;
