#include <iostream>
#include <functional>
#include <cmath>
#include "Matrix.hpp"

Matrix::Matrix(int h, int w) {
  srand(time(0));
  this->h     = h;
  this->w     = w;
  this->read  = new unsigned short *[h];
  this->write = new unsigned short *[h];

  for (int i = 0; i < h; i++) {
    this->read[i]  = new unsigned short[w];
    this->write[i] = new unsigned short[w];

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

inline void Matrix::set(int i, int j, unsigned short v) {
  this->write[mod(i, this->h)][mod(j, this->w)] = v;
}

inline unsigned short Matrix::get(int i, int j) const {
  return this->read[mod(i,this->h)][mod(j,this->w)];
}

void Matrix::forEach(std::function<unsigned short(int, int, unsigned short, int)>f) {
  forEach(0, this->h, f);
}

void Matrix::forEach(int start,
                     int end,
                     std::function<unsigned short(int, int, unsigned short, int)>f) {
  for (int i = start; i < end; i++) {
    for (int j = 0; j < this->w; j++) {
      unsigned short r = f(i, j, this->read[i][j], countAlive(i, j));
      if (r!=-1) {
        set(i,j,r);
      }
    }
  }
}

void Matrix::swap() {
  this->tmp = this->read;
  this->read  = this->write;
  this->write = tmp;
}

int Matrix::countAlive(int x, int y) const{
  int count = 0;

  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (((i != x) || (j != y)) && (get(i, j) == 1)) {
        count++;
      }
    }
  }
  return count;
}

inline unsigned short Matrix::mod(int a, int b) const{
  return (a % b + b) % b;
}
