#include <iostream>
#include <functional>
#include <cmath>
#include "Matrix.hpp"
#include "Patterns.cpp"

Matrix::Matrix(long h, long w, bool random) {
	this->h = h;
	this->w = w;
	cell_t **rowsR = new cell_t *[h+2];
	this->read = rowsR + 1;
	cell_t **rowsW = new cell_t *[h+2];
	this->write = rowsW + 1;
	this->read[0] = new cell_t[w*h];
	this->write[0] = new cell_t[w*h];

	for (long i = 1; i < h; i++) {
		this->read[i]  = this->read[i-1] + w;
		this->write[i] = this->write[i-1] + w;

		#pragma ivdep
		for (long j = 0; j < w; j++) {
			this->read[i][j] = 0;
			this->write[i][j] = 0;
		}
	}

	if (random) randomizeRows(0, h);

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
		write[i][0]   = lifeLogic(read[i][0],   countAlive(i, 0));
		#pragma ivdep
		for (long j = 1, _w = w - 1; j < _w; j++) {
			write[i][j] = lifeLogic(read[i][j], dumbCountAlive(i, j));
		}
		write[i][w-1] = lifeLogic(read[i][w-1], countAlive(i, w-1));
	}
}

void Matrix::randomizeRows(long start, long end, drand48_data *state) {
	drand48_data state_;
	long int random;
	if (state == nullptr) {
		srand48_r(start ^ time(NULL) ^ end, &state_);
		state = &state_;
	}
	
	for (long i = start; i < end; i++) {
		for (long j = 0; j < w; j++) {
			lrand48_r(state, &random);
			this->read[i][j] = random % 2;
		}
	}
}

void Matrix::swap() {
	cell_t **tmp = read;
	read = write;
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

void Matrix::drawConfigurations(long conf) {
	if (conf & GLIDER)
		for (long p = 0; p < h-5; p += 30) draw(GLIDER, p, p);
	if ((conf & BOTTLE) && h > 140)
		for (long p = 40; p < w-40; p += 60) draw(BOTTLE, 100, p);
	if ((conf & SCHICKENGINE) && w > 40)
		for (long p = 10; p < h-20; p += 30) draw(SCHICKENGINE, p, w-30);
	if ((conf & HAMMERHEAD) && h > 40)
		for (long p = 10; p < w-30; p += 50) draw(HAMMERHEAD, h-25, p);
	if ((conf & GOSPERSGUN) && w > 40)
		for (long p = 0; p < h-11; p += 50) draw(GOSPERSGUN, p, 40);
	swap();
}

template <long W>
void Matrix::drawMatrix(cell_t model[][W], long H, long x, long y) {
	for (long i = 0; i < H; i++)
		for (long j = 0; j < W; j++)
			set(x + i, y + j, model[i][j]);
}