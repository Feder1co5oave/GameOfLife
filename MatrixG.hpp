#ifndef MatrixG_h_
#define MatrixG_h_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Matrix.hpp"

class MatrixG : public Matrix {
  MatrixG(MatrixG const&) =delete;
  MatrixG& operator=(MatrixG const&) =delete;

public:

  MatrixG(long h, long w, bool random = false);
  void print() const;
  void set (long i, long j, cell_t v) override;
  void updateRows(long start, long end);
private:
  cv::Mat screen;
};

#endif // ifndef MatrixG_h_
