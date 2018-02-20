#include <iostream>

#include <Eigen/Dense>
#include "SymMat.h"

int main(int argc, char *argv[]){
  Eigen::Matrix3f m1;
  m1 <<
    0, 1, 2,
    3, 4, 5,
    6, 7, 8;

  SymMat <float> s1(m1);
  s1(0,2);
  return 0;
}
