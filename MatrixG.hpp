#ifndef MatrixG_h_
#define MatrixG_h_

#include <functional>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Matrix.hpp"

class MatrixG : public Matrix {
  MatrixG(MatrixG const&) =delete;
  MatrixG& operator=(MatrixG const&) =delete;

public:

  MatrixG(int h,
          int w);
  void  print() override;

private:
  cv::Mat screen;
};
#endif // ifndef MatrixG_h_
