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
  void print() const;
  inline short get(int i, int j) const {
    i = mod(i,h);
    j = mod(j,w);
    return read[i][j];
  }
  inline void set(int i, int j, short v) {
  	write[mod(i,h)][mod(j,w)] = v;
  }
  void         swap();
  void         forEach(std::function<short(int, int, short, int)> f);
  void         forEach(int start,
                       int end,
                       std::function<short(int, int, short, int)> f);
  int countAlive(int x, int y) const;
  inline int getWidth() { return w; }

protected:

  short **read, **write;
  int     w, h;

private:
  template<typename T>
  inline static T mod(T a, T b) {
    if (a == b) return 0;
    if (a == -1) return b-1;
    return a;
  }
};

#endif // ifndef Matrix_h_
