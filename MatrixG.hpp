#include <functional>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Matrix.hpp"

class MatrixG : public Matrix {
  cv::Mat screen;
};