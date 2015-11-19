#ifndef Matrix_h_
#define Matrix_h_

#include <functional>

typedef unsigned char cell_t;

class Matrix {
  Matrix(Matrix const&) =delete;
  Matrix& operator=(Matrix const&) =delete;

public:

  Matrix(int h,
         int w);
  virtual ~Matrix();
  void print() const;
  inline cell_t get(int i, int j) const {
    i = mod(i,h);
    j = mod(j,w);
    return read[i][j];
  }
  inline void set(int i, int j, cell_t v) {
  	write[mod(i,h)][mod(j,w)] = v;
  }
  void         swap();
  void         forEach(std::function<cell_t(int, int, cell_t, int)> f);
  void         forEach(int start,
                       int end,
                       std::function<cell_t(int, int, cell_t, int)> f);
  int countAlive(int x, int y) const;
  inline int getWidth() { return w; }

protected:

  cell_t **read, **write;
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
