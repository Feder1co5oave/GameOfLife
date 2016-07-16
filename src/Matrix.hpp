#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <ios>
#include <iomanip>

typedef unsigned char cell_t;

extern cell_t _lifeLogic[][9];

struct digest128 {
	uint64_t upper, lower;
	digest128(uint64_t up, uint64_t low): upper(up), lower(low) {}
	friend std::ostream& operator<<(std::ostream& os, digest128 const& d) {
		os << std::setfill('0') << std::setw(16) << std::hex << std::right << d.upper;
		os << std::setfill('0') << std::setw(16) << std::hex << std::right << d.lower;
		return os;
	}
};

class Matrix {

	Matrix(Matrix const&)            = delete;
	Matrix& operator=(Matrix const&) = delete;

protected:
	cell_t **read, **write;
	long w, h;

public:
	Matrix(long h, long w, bool random = false);
	virtual ~Matrix();
	void print(std::ostream& os = std::cout) const;
	virtual void set(long i, long j, cell_t v) { write[i][j] = v; }
	cell_t get(long i, long j) { return read[i][j]; }
	void swap();	
	void updateRows(long start, long end);
	virtual void randomizeRows(long start, long end);

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
		return
			(~(liveNeighbors >> 2))
			&
			(liveNeighbors >> 1)
			&
			(liveNeighbors | cell)
			& 1;
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
	digest128 hashcode() const;

protected:
	template <long W> void drawMatrix(cell_t model[][W], long H, long x, long Y);

	inline long dumbCountAlive(long x, long y) const {
		return read[x-1][y-1] + read[x-1][ y ] + read[x-1][y+1] +
		       read[ x ][y-1]                  + read[ x ][y+1] +
		       read[x+1][y-1] + read[x+1][ y ] + read[x+1][y+1];
	}
};

#endif // ifndef MATRIX_H
