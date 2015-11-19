#include <iostream>
#include <functional>
#include <cmath>
#include "Matrix.hpp"

Matrix::Matrix(long h, long w) {
  srand(time(0));
  this->h     = h;
  this->w     = w;
  this->read  = new cell_t *[h];
  this->write = new cell_t *[h];

  for (long i = 0; i < h; i++) {
    this->read[i]  = new cell_t[w];
    this->write[i] = new cell_t[w];

    for (long j = 0; j < w; j++) {
      this->read[i][j] = floor(rand() % 2);
    }
  }
}

Matrix::~Matrix() {
  for (long i = 0; i < h; i++) {
    delete[] this->read[i];
    delete[] this->write[i];
  }
  delete[] this->read;
  delete[] this->write;
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

void Matrix::forEach(std::function<cell_t(long, long, cell_t, long)>f) {
  forEach(0, this->h, f);
}

void Matrix::forEach(long start,
                     long end,
                     std::function<cell_t(long, long, cell_t, long)> f) {
  for (long i = start; i < end; i++) {
    for (long j = 0; j < w; j++) {
      set(i,j,f(i, j, this->read[i][j], countAlive(i, j)));
    }
  }
}

void Matrix::swap() {
  cell_t **tmp = this->read;

  this->read  = this->write;
  this->write = tmp;
}

long Matrix::countAlive(long x, long y) const {
  return  get(x-1,y-1) + get(x-1,y) + get(x-1,y+1)
         + get(x,  y-1)              + get(x,  y+1)
         + get(x+1,y-1) + get(x+1,y) + get(x+1,y+1);
}
