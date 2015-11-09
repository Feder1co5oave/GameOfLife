#ifndef Matrix_h_
#define Matrix_h_

#include <functional>

class Matrix {
  Matrix(Matrix const&) =delete;
  Matrix& operator=(Matrix const&) =delete;

public:

  Matrix(int h,
         int w);
  virtual ~Matrix();
  virtual void print() const;
  short        get(int i,
                   int j) const;
  virtual void         set(int   i,
                   int   j,
                   short v);
  void         swap();
  void         forEach(std::function<short(int, int, short, int)>f);
  void         forEach(int start,
                       int end,
                       std::function<short(int, int, short, int)>f);

protected:

  short **read, **write;
  int     w, h;

private:
  short mod(int x,
            int y) const;
  int   countAlive(int x,
                   int y) const;
};

#endif // ifndef Matrix_h_
