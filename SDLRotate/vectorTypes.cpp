#include "vectorTypes.h"


double maxX2(std::vector<double> xes) {
	double max = 0;
	for (double x : xes) {
		if (max < x) {
			max = x;
		}
	}
	return max;
}

double maxY2(std::vector<double> yes) {
	double max = 0;
	for (double y : yes) {
		if (max < y) {
			max = y;
		}
	}
	return max;
}

double minX2(std::vector<double> xes) {
	double min = 0;
	for (double x : xes) {
		if (min > x) {
			min = x;
		}
	}
	return min;
}

double minY2(std::vector<double> yes) {
	double min = 0;
	for (double y : yes) {
		if (min > y) {
			min = y;
		}
	}
	return min;
}