#include <iostream>
#include <functional>
#include <cmath>
#include "Matrix.hpp"
#include "Patterns.cpp"


Matrix::Matrix(long h, long w, bool random) {
  srand(time(0));
  this->h     = h;
  this->w     = w;
  cell_t **rowsR = new cell_t *[h+2];
  this->read  = rowsR + 1;
  cell_t **rowsW = new cell_t *[h+2];
  this->write = rowsW + 1;
  this->read[0] = new cell_t[w*h];
  this->write[0] = new cell_t[w*h];

  for (long i = 1; i < h; i++) {
    this->read[i]  = this->read[i-1] + w;
    this->write[i] = this->write[i-1] + w;

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
  delete[] this->read[0];
  delete[] this->write[0];
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

void Matrix::updateRows(long start, long end) {
  for (long i = start; i < end; i++) {
    for (long j = 1, _w = w - 1; j < _w; j++) {
      write[i][j] = lifeLogic(read[i][j], dumbCountAlive(i, j));
    }
    // defer the read to the last cache block until the end of the row
    write[i][0]   = lifeLogic(read[i][0],   countAlive(i, 0));
    write[i][w-1] = lifeLogic(read[i][w-1], countAlive(i, w-1));
  }
}

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

void Matrix::draw(enum configuration conf, long x, long y) {
  cell_t *model = NULL;
  long H = -1, W = -1;
  switch (conf) {
    case GLIDER:
      drawMatrix(glider, 5, x, y);
      break;
    case BOTTLE:
      drawMatrix(bottle, 20, x, y);
      break;
    case SCHICKENGINE:
      drawMatrix(schickengine, 13, x, y);
      break;
    case HAMMERHEAD:
      drawMatrix(hammerhead, 18, x, y);
      break;
    case GOSPERSGUN:
      drawMatrix(gospersgun, 11, x, y);
  }
}

template <long W>
void Matrix::drawMatrix(cell_t model[][W], long H, long x, long y) {
  for (long i = 0; i < H; i++)
    for (long j = 0; j < W; j++)
      set(x + i, y + j, model[i][j]);
}