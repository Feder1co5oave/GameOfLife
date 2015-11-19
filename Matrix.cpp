#include <iostream>
#include <functional>
#include <cmath>
#include "Matrix.hpp"

Matrix::Matrix(int h, int w) {
  srand(time(0));
  this->h     = h;
  this->w     = w;
  this->read  = new short *[h];
  this->write = new short *[h];

  for (int i = 0; i < h; i++) {
    this->read[i]  = new short[w];
    this->write[i] = new short[w];

    for (int j = 0; j < w; j++) {
      this->read[i][j] = floor(rand() % 2);
    }
  }
}

Matrix::~Matrix() {
  for (int i = 0; i < this->h; i++) {
    delete[] this->read[i];
    delete[] this->write[i];
  }
  delete[] this->read;
  delete[] this->write;
}

void Matrix::print() const{
  // std::cout << "\n";
  int h = this->h;
  int w = this->w;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      std::cout << (this->read[i][j] ? "\u2588\u2588" : "  ");
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Matrix::forEach(std::function<short(int, int, short, int)>f) {
  forEach(0, this->h, f);
}

void Matrix::forEach(int start,
                     int end,
                     std::function<short(int, int, short, int)>f) {
  for (int i = start; i < end; i++) {
    for (int j = 0; j < this->w; j++) {
      set(i,j,f(i, j, this->read[i][j], countAlive(i, j)));
    }
  }
}

void Matrix::swap() {
  short **tmp = this->read;

  this->read  = this->write;
  this->write = tmp;
}

int Matrix::countAlive(int x, int y) const {
  return  get(x-1,y-1) + get(x-1,y) + get(x-1,y+1)
        + get(x,  y-1)              + get(x,  y+1)
        + get(x+1,y-1) + get(x+1,y) + get(x+1,y+1);
}
