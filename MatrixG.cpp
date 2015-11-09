#include <iostream>
#include <functional>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "MatrixG.hpp"

MatrixG::MatrixG(int h, int w) : Matrix(h, w) {
  this->screen = cv::Mat::zeros(h, w, CV_8UC3);
  cv::imshow("test", this->screen);
  cv::moveWindow("test", 0, 20);
  cv::waitKey(1);
}

void MatrixG::print() const{
  // int h = this->h;
  // int w = this->w;
  //
  // for (int i = 0; i < h; i++) {
  //   for (int j = 0; j < w; j++) {
  //     if (this->read[i][j] == 1) {
  //       this->screen.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(255, 255, 255);
  //     } else {
  //       this->screen.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(0, 0, 0);
  //     }
  //   }
  // }

  cv::imshow("test", this->screen);
  cv::waitKey(1);
}

void MatrixG::set(int i, int j, short v){
  Matrix::set(i,j,v);
  if (v==1){
    this->screen.at<cv::Vec3b>(cv::Point(j, i)) = cv::Vec3b(255, 255, 255);
  }
  if (v==0){
    this->screen.at<cv::Vec3b>(cv::Point(j, i)) = cv::Vec3b(0,0,0);
  }
}
