#include <Eigen/Dense>

using Eigen::Matrix3f;

int main(int argc, char **argv)
{
  Matrix3f m1;
  m1 <<
    0, 1, 2,
    3, 4, 5,
    6, 7, 8;
  int out = m1.minCoeff();
  return out;
}
