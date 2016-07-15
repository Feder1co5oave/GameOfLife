#include <iostream>
#include <cmath>
#include "MatrixG.hpp"

MatrixG::MatrixG(long h, long w, bool random) : Matrix(h, w, false) {
	this->screen = cv::Mat::zeros(h, w, CV_8UC3);
	cv::imshow("Game of Life", this->screen);
	cv::moveWindow("Game of Life", 0, 20);
	cv::waitKey(1);
	if (random) randomizeRows(0, h);
}

void MatrixG::print() const {
	cv::imshow("Game of Life", this->screen);
	cv::waitKey(1);
}

void MatrixG::set(long i, long j, cell_t v){
	Matrix::set(i,j,v);
	unsigned char c = (~v) + 1;
	this->screen.at<cv::Vec3b>(cv::Point(j, i)) = cv::Vec3b(c, c, c);
}

void MatrixG::updateRows(long start, long end) {
	for (long i = start; i < end; i++) {
		set(i, 0, lifeLogic(read[i][0], countAlive(i, 0)));
		for (long j = 1, _w = w - 1; j < _w; j++) {
			set(i, j, lifeLogic(read[i][j], dumbCountAlive(i, j)));
		}
		set(i, w-1, lifeLogic(read[i][w-1], countAlive(i, w-1)));
	}
}

void MatrixG::randomizeRows(long start, long end, drand48_data *state) {
	unsigned char c;
	Matrix::randomizeRows(start, end, state);
	for (long i = start; i < end; i++) {
		for (long j = 0; j < w; j++) {
			c = (~read[i][j]) + 1;
			screen.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(c, c, c);
		}
	}
}
