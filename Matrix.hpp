#include <functional>

class Matrix {
  short **read, **write;
  int     w, h;

public:

  Matrix(int h,
         int w);
  ~Matrix();
  void  print();
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
