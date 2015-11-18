#ifndef Matrix_h_
#define Matrix_h_

#include <functional>

class Matrix {
  Matrix(Matrix const&)            = delete;
  Matrix& operator=(Matrix const&) = delete;

public:

  Matrix(int h,
         int w);
  virtual ~Matrix();
  virtual void   print() const;
  unsigned short get(int i,
                     int j) const;
  virtual void   set(int            i,
                     int            j,
                     unsigned short v);
  void           swap();
  void           forEach(std::function<unsigned short(int, int,
                                                      unsigned short,
                                                      int)>f);
  void           forEach(int start,
                         int end,
                         std::function<unsigned short(int, int,
                                                      unsigned short,
                                                      int)>f);

protected:

  unsigned short **read, **write, **tmp;
  int w, h;

private:

  unsigned short mod(int x,
                     int y) const;
  int            countAlive(int x,
                            int y) const;
};

#endif // ifndef Matrix_h_
