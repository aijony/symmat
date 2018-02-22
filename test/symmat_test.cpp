#include <Eigen/Dense>
#include "SymMat.h"

#include <stdexcept>

void testIndex();
void testSum();

int main(int argc, char **argv){
  testIndex();
  testSum();
  return 0;
}

void testIndex(){
  Eigen::Matrix3f m1;
  m1 <<
    1, 2, 3,
    2, 5, 6,
    3, 6, 7;

  SymMat<float> s1(m1);
  if(s1(0,1) != s1(1,0) || m1(0,1) != s1(1,0)){
    throw std::runtime_error("FAIL: SymMat not properly constructed");
  }
  s1(0,1) = m1(0,1) + 1;
  if(s1(0,1) == m1(0,1)){
    throw std::runtime_error("FAIL: SymMat not mutable");
  }
}

void testSum(){
  Eigen::Matrix3f m1;
  m1 <<
    1, 2, 3,
    2, 4, 5,
    3, 5, 6;

  SymMat<float> s1(m1);

  SymMat<float> s2 = s1 + s1 + s1 - s1;
  if(!(s1 * (float)2 == s2)){
    throw std::runtime_error("FAIL: SymMat arithmetic error");
  }

  Eigen::MatrixXf sa = s1 + m1;

  if(m1(0,1) * 2 != sa(0,1)){
    throw std::runtime_error("FAIL: SymMat arithmetic error");
  }
}

void testMult(){
  Eigen::Matrix3f m1;
  m1 <<
    1, 2, 3,
    2, 4, 5,
    3, 5, 6;

  SymMat<float> s1(m1);

  Eigen::Matrix3f s2 = s1 * m1;
  Eigen::Matrix3f m2 = m1 * m1;

  if(s2 != m2){
    throw std::runtime_error("FAIL: Matrix Multiplication Failed");
  }

}
