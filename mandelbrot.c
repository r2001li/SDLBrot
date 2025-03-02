#include "mandelbrot.h"

#define MAX_ITER 1000

int iterate(double x0, double y0) {
	double x = 0.0;
	double y = 0.0;
	int iteration = 0;

	while (x * x + y * y <= 4 && iteration < MAX_ITER) {
		double xtmp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtmp;
		iteration++;
	}

	return iteration;
}
