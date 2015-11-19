#ifndef Matrix_h_
#define Matrix_h_

#include <functional>

typedef unsigned char cell_t;

class Matrix {
  Matrix(Matrix const&) =delete;
  Matrix& operator=(Matrix const&) =delete;

public:

  Matrix(long h,
         long w);
  virtual ~Matrix();
  void print() const;
  inline cell_t get(long i, long j) const {
    i = mod(i,h);
    j = mod(j,w);
    return read[i][j];
  }
  inline void set(long i, long j, cell_t v) {
  	write[mod(i,h)][mod(j,w)] = v;
  }
  void         swap();
  void         forEach(std::function<cell_t(long, long, cell_t, long)> f);
  void         forEach(long start,
                       long end,
                       std::function<cell_t(long, long, cell_t, long)> f);
  long countAlive(long x, long y) const;
  inline long getWidth() { return w; }

protected:

  cell_t **read, **write;
  long     w, h;

private:
  template<typename T>
  inline static T mod(T a, T b) {
    if (a == b) return 0;
    if (a == -1) return b-1;
    return a;
  }
};

#endif // ifndef Matrix_h_
