#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>

typedef unsigned char cell_t;

extern cell_t _lifeLogic[][9];


class Matrix {

	Matrix(Matrix const&)            = delete;
	Matrix& operator=(Matrix const&) = delete;

protected:
	cell_t **read, **write;
	long w, h;

public:
	Matrix(long h, long w, bool random = false);
	virtual ~Matrix();
	void print() const;
	virtual void set(long i, long j, cell_t v) { write[i][j] = v; }
	cell_t get(long i, long j) { return read[i][j]; }
	void swap();	
	void updateRows(long start, long end);
	virtual void randomizeRows(long start, long end, drand48_data *state = nullptr);

	inline long countAlive(long x, long y) const {
		if (y == 0)
			return read[x-1][w-1] + read[x-1][ 0 ] + read[x-1][ 1 ]
			     + read[ x ][w-1]                  + read[ x ][ 1 ]
			     + read[x+1][w-1] + read[x+1][ 0 ] + read[x+1][ 1 ];
		else if (y == w-1)
			return read[x-1][w-2] + read[x-1][w-1] + read[x-1][ 0 ]
			     + read[ x ][w-2]                  + read[ x ][ 0 ]
			     + read[x+1][w-2] + read[x+1][w-1] + read[x+1][ 0 ];
		else return dumbCountAlive(x, y);
	}
	
	inline static cell_t lifeLogic(cell_t cell, long liveNeighbors) {
		return _lifeLogic[cell][liveNeighbors];
	}

	enum configuration {
		GLIDER = 1,
		BOTTLE = 2,
		SCHICKENGINE = 4,
		HAMMERHEAD = 8,
		GOSPERSGUN = 16
	};
	
	void draw(enum configuration conf, long x, long y);
	void drawConfigurations(long conf);

protected:
	template <long W> void drawMatrix(cell_t model[][W], long H, long x, long Y);

	inline long dumbCountAlive(long x, long y) const {
		return read[x-1][y-1] + read[x-1][ y ] + read[x-1][y+1] +
		       read[ x ][y-1]                  + read[ x ][y+1] +
		       read[x+1][y-1] + read[x+1][ y ] + read[x+1][y+1];
	}
};

#endif // ifndef MATRIX_H
