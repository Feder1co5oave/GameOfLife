#include <functional>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Matrix {
  short **read, **write;
  int     w, h;
  cv::Mat screen;

public:

  Matrix(int h,
         int w);
  Matrix(int  h,
         int  w,
         bool graphic);
  ~Matrix();
  void  print();
  void  printG();
  short get(int i,
            int j);
  void  set(int   i,
            int   j,
            short v);
  void  swap();
  void  forEach(std::function<short(int, int, short, int)>f);
  void  forEach(int start,
                int end,
                std::function<short(int, int, short, int)>f);

private:

  short mod(int x,
            int y);
  int   countAlive(int x,
                   int y);
};
