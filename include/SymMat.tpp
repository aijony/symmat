
/**
   Matrix Multiplication.
   Takes either a SymMat or an Eigen::Matrix.
   Always returns Eigen::Matrix.
 */
template <typename T>
template <typename Mat>
auto SymMat<T>::mult(const Mat& m){
  if(this->cols() != m.rows()){
    throw std::logic_error("Dimension mismatch");
  }

  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> outM(this->rows(), m.cols());

  for (int i = 0; i < this->rows(); i++){
    for (int j = 0; j < m.cols(); j++){
      outM(i,j) = 0;
      for (int k = 0; k < m.rows(); k++){
        outM(i,j) = outM(i,j) + (this->operator()(i,k) * m(k,j));
      }
    }
  }
  return outM;
}

/**
   Zips two SymMat's with a function,
   Returns a new SymMat.
 */
template <typename T>
template <typename Func>
SymMat<T> SymMat<T>::zipWith(const SymMat<T>& m, Func func){
  if(length() != m.length()){
    throw std::logic_error("Dimension mismatch");
  }

  SymMat<T> outM(length());

  for(int i = 0; i < length(); i++){
    for (int j = i; j < cols(); j++){
      outM.m_data[i][j] = func(this->m_data[i][j], m.m_data[i][j]);
    }
  }
  return outM;
}

/**
   Zips a SymMat with an Eigen::Matrix,
   Returns and Eigen::Matrix.
 */
template <typename T>
template <typename Func, typename EMat>
EMat SymMat<T>::zipWith(const EMat& m, Func func){
  if(this->length() != m.rows() || this->length() != m.cols()){
    throw std::logic_error("Dimension mismatch or not square");
  }

  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> outM(length(), length());

  for(int i = 0; i < outM.cols(); i++){
    for(int j = 0; j < outM.rows(); j++){
      outM(i, j) = func(this->operator()(i, j), m(i, j));
    }
  }
  return outM;
}

/**
   Maps a comparative function across SymMat
   and an Eigen::Matrix or another SymMat.
   Short-circuits to false if:
      - Dimensions don't match
      - The function returns false at least once
   TODO Make separate functions for SymMat and Eigen::Matrix
 */
template <typename T>
template <typename Func, typename Mat>
bool SymMat<T>::mapBool(const Mat& m, Func func){
  if(this->length() != m.rows() || this->length() != m.cols()){
    return false;
  }

  for(int i = 0; i < m.cols(); i++){
    for(int j = 0; j < m.rows(); j++){
      if(!func(this->operator()(i, j), m(i, j))){
        return false;
      }
    }
  }
  return true;
}

/**
   Equals to operator for a SymMat
   and an Eigen::Matrix or another SymMat
 */
template <typename T>
template <typename Mat>
bool SymMat<T>::operator==(const Mat& m){
  return mapBool(m, [] (T x, T y) -> T {return (x == y);});
}

/**
   Not equals to operator for a SymMat
   and an Eigen::Matrix or another SymMat
   Based off of equals to.
*/
template <typename T>
template <typename Mat>
bool SymMat<T>::operator!=(const Mat& m){
  return !(this->operator==(m));
}

/**
   Addition operator for a SymMat
   and an Eigen::Matrix or another SymMat
 */
template <typename T>
template <typename Mat>
Mat SymMat<T>::operator+(const Mat& m){
  return zipWith(m, [] (T x, T y) -> T {return (x + y);});
}

/**
   Subtraction operator for a SymMat
   and an Eigen::Matrix or another SymMat
 */
template <typename T>
template <typename Mat>
Mat SymMat<T>::operator-(const Mat& m){
  return zipWith(m, [] (T x, T y) -> T {return (x - y);});
}

/**
   Matrix Multiplication operator for a SymMat
   and an Eigen::Matrix or another SymMat.
   Cast input scalar if scalar multiplication is intended.
   TODO Don't require casting.
 */
template <typename T>
template <typename Mat>
auto SymMat<T>::operator*(const Mat& m){
  return mult(m);
}
