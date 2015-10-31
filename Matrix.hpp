#include <functional>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Matrix {
  short **m;
  int     w, h;
  cv::Mat screen;

public:

  Matrix(int h,
         int w);
  void  print();
  void printG();
  short get(int i,
            int j);
  void  set(int   i,
            int   j,
            short v);
  void  forEach(std::function<void(int, int, short *, int, int)>f);

private:

  short mod(int x,
            int y);
  int   countAlive(int x,
                   int y);
};
