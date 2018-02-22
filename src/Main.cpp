#include "SymMat.h"
#include <iostream>
#include <stdexcept>
#include <Eigen/Dense>

int main(int argc, char *argv[]){
  Eigen::Matrix3f m1;
  m1 <<
    0, 1, 2,
    1, 3, 5,
    2, 5, 8;

  // 1. A constructor to make a SymMat from an Eigen::Matrix
  SymMat<float> s1(m1);

  // 2. Accessors for S(i,j): S(j,i) should of course return the same as S(i,j)
  if(s1(1,1) != m1(1,1) or s1(2,0) != s1(0,2)){
    throw std::runtime_error("Failed 2");
  }

  // 3. Functions for matrix addition:
  SymMat<float> s2 = s1 + s1 + s1 - s1;
  Eigen::Matrix3f s3 = s1 + m1;
  if(s1 * (float)2 != s2 && s1 + s1 != s3){
    throw std::runtime_error("Failed 3");
  }

  // 3. Functions for matrix addition:
  Eigen::Matrix3f ma = s1 * s1;
  Eigen::Matrix3f mb = s1 * m1;
  Eigen::Matrix3f m2 = m1 * m1;
  if(m2 != mb){
    throw std::runtime_error("Failed 4");
  }

  // Oh no, a non-square matrix!
  Eigen::Matrix<float, 3, 4> mA;
  mA <<
    0, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11;

  Eigen::Matrix<float, 3, 4> mB = s1 * mA;
  Eigen::Matrix<float, 3, 4> mC = m1 * mA;
  if(m1 * mA != s1 * mA){
    throw std::runtime_error("Failed 4");
  }

  //If the dimensions of the matrices in these functions don’t match
  try {
    s1 + mA;
  }
  //You should throw an exception.
  catch (const std::logic_error& e) {
    std::cout << "Test Passed" << std::endl;
  }
  return 0;
}
