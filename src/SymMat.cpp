#include "SymMat.h"

#include <Eigen/Core>
#include <stdexcept>

using namespace Eigen;

template <typename T>
SymMat<T>::SymMat(const Ref<const Matrix<T, Dynamic, Dynamic>>& m){
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
int SymMat<T>::length(){
  return m_length;
}

template <typename T>
int SymMat<T>::size(){
  return m_size;
}

template class SymMat<float>;
