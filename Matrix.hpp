#ifndef Matrix_h_
#define Matrix_h_

#include <functional>

typedef unsigned char cell_t;

extern cell_t _lifeLogic[][9];

class Matrix {
  Matrix(Matrix const&)            = delete;
  Matrix& operator=(Matrix const&) = delete;

public:

  Matrix(long h, long w, bool random = false);
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
  void swap();

  typedef std::function <cell_t(long, long, cell_t, long)> lambda;
  void forEach(lambda f);
  void forEach(long start, long end, lambda f);
  long countAlive(long x, long y) const;
  inline long getWidth() { return w; }
  inline static cell_t lifeLogic(cell_t cell, long liveNeighbors) {
    return _lifeLogic[cell][liveNeighbors];
  }

protected:

  cell_t **read, **write, **tmp;
  long     w, h;

  inline long dumbCountAlive(long x, long y) const {
    return read[x-1][y-1] + read[x-1][ y ] + read[x-1][y+1] +
           read[ x ][y-1]                  + read[ x ][y+1] +
           read[x+1][y-1] + read[x+1][ y ] + read[x+1][y+1];
  }

private:
  template<typename T>
  inline static T mod(T a, T b) {
    if (a == b) return 0;
    if (a == -1) return b-1;
    return a;
  }
};

#endif // ifndef Matrix_h_
