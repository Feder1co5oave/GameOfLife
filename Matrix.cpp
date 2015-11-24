#include <iostream>
#include <functional>
#include <cmath>
#include "Matrix.hpp"


Matrix::Matrix(long h, long w, bool random) {
  srand(time(0));
  this->h     = h;
  this->w     = w;
  cell_t **rowsR = new cell_t *[h+2];
  this->read  = rowsR + 1;
  cell_t **rowsW = new cell_t *[h+2];
  this->write = rowsW + 1;

  for (long i = 0; i < h; i++) {
    this->read[i]  = new cell_t[w];
    this->write[i] = new cell_t[w];

    if (random)
    for (long j = 0; j < w; j++) {
      this->read[i][j] = rand() % 2;
      this->write[i][j] = 0;
    }
    else
    for (long j = 0; j < w; j++) {
      this->read[i][j] = 0;
      this->write[i][j] = 0;
    }
  }
  // wrap-around
  read[-1] = read[h-1];
  read[h] = read[0];
  write[-1] = write[h-1];
  write[h] = write[0];
}

Matrix::~Matrix() {
  for (long i = 0; i < h; i++) {
    delete[] this->read[i];
    delete[] this->write[i];
  }
  delete[] (this->read - 1);
  delete[] (this->write - 1);
}

void Matrix::print() const {
  for (long i = 0; i < h; i++) {
    for (long j = 0; j < w; j++) {
      std::cout << (this->read[i][j] ? "\u2588\u2588" : "  ");
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

cell_t _lifeLogic[2][9] = {
  {0, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0, 0}
};

void Matrix::forEach(std::function<cell_t(long, long, cell_t, long)>f) {
  forEach(0, this->h, f);
}

void Matrix::forEach(long start,
                     long end,
                     std::function<cell_t(long, long, cell_t, long)> f) {
  for (long i = start; i < end; i++) {
    for (long j = 0; j < w; j++) {
      cell_t r = f(i, j, this->read[i][j], countAlive(i, j));
      if (r != -1) set(i,j,r);
    }
  }
}

void Matrix::swap() {
  tmp   = read;
  read  = write;
  write = tmp;
}

long Matrix::countAlive(long x, long y) const {
  if (y == 0)
    return  read[x-1][w-1] + read[x-1][ 0 ] + read[x-1][ 1 ]
          + read[ x ][w-1]                  + read[ x ][ 1 ]
          + read[x+1][w-1] + read[x+1][ 0 ] + read[x+1][ 1 ];
  else if (y == w-1)
    return  read[x-1][w-2] + read[x-1][w-1] + read[x-1][ 0 ]
          + read[ x ][w-2]                  + read[ x ][ 0 ]
          + read[x+1][w-2] + read[x+1][w-1] + read[x+1][ 0 ];
  else return dumbCountAlive(x, y);
}
