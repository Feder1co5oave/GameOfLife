#include <iostream>
#include <functional>
#include <cmath>
#include "Matrix.hpp"

Matrix::Matrix(int h, int w) {
  srand(time(NULL));
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
  std::cout << "mi sono costruito" << std::endl;
}

Matrix::~Matrix() {
  for (int i = 0; i < this->h; i++) {
    delete[] this->read[i];
    delete[] this->write[i];
  }
  delete[] this->read;
  delete[] this->write;
}

void Matrix::print(){
  // std::cout << "\n";
  int h = this->h;
  int w = this->w;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      std::cout << this->read[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

short Matrix::get(int i, int j) {
  i = mod(i,h);
  j = mod(j,w);
  return this->read[i][j];
}

void Matrix::set(int i, int j, short v) {
  this->write[mod(i, this->h)][mod(j, this->w)] = v;
}

void Matrix::forEach(std::function<short(int, int, short, int)>f) {
  forEach(0, this->h, f);
}

void Matrix::forEach(int start,
                     int end,
                     std::function<short(int, int, short, int)>f) {
  for (int i = start; i < end; i++) {
    for (int j = 0; j < this->w; j++) {
      this->write[i][j] = f(i, j, this->read[i][j], countAlive(i, j));
    }
  }
}

void Matrix::swap() {
  short **tmp = this->read;

  this->read  = this->write;
  this->write = tmp;
}

int Matrix::countAlive(int x, int y) {
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

short Matrix::mod(int a, int b) {
  return (a % b + b) % b;
}
