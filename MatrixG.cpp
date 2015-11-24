#include <iostream>
#include <cmath>
#include "MatrixG.hpp"

MatrixG::MatrixG(long h, long w, bool random) : Matrix(h, w, random) {
  this->screen = cv::Mat::zeros(h, w, CV_8UC3);
  cv::imshow("test", this->screen);
  cv::moveWindow("test", 0, 20);
  cv::waitKey(1);
  if (random) {
    for (long i = 0; i < h; i++)
      for (long j = 0; j < w; j++)
        screen.at<cv::Vec3b>(cv::Point(i, j)) = (read[i][j] ?
          cv::Vec3b(255, 255, 255) :
          cv::Vec3b(0, 0, 0));
  }
}

void MatrixG::print() const{
  cv::imshow("test", this->screen);
  cv::waitKey(1);
}

void MatrixG::set(long i, long j, cell_t v){
  Matrix::set(i,j,v);
  if (v==1){
    this->screen.at<cv::Vec3b>(cv::Point(j, i)) = cv::Vec3b(255, 255, 255);
  }
  if (v==0){
    this->screen.at<cv::Vec3b>(cv::Point(j, i)) = cv::Vec3b(0,0,0);
  }
}
