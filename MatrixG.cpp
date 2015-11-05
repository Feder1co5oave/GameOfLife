#include <iostream>
#include <functional>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Matrix.hpp"

MatrixG::MatrixG(int h, int w) : Matrix(int h, int w){
  /// Create black empty images
  this->screen = cv::Mat::zeros(w, h, CV_8UC3);
  cv::imshow("test", this->screen);
  cv::moveWindow("test", 0, 20);
  cv::waitKey(1);
}

MatrixG::~MatrixG() : ~Matrix(){
  for (int i = 0; i < this->h; i++) {
    delete[] this->read[i];
    delete[] this->write[i];
  }
  delete[] this->read;
  delete[] this->write;
  delete this->screen;
}

void MatrixG::print() override {
  int h = this->h;
  int w = this->w;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (this->read[i][j] == 1) {
        this->screen.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(255, 255, 255);
      } else {
        this->screen.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(0, 0, 0);
      }
    }
}
  cv::imshow("test", this->screen);
  cv::waitKey(1);
}