#include "matrix.h"

Matrix::Matrix(unsigned int n, unsigned int m) {
	this->n = n;
	this->m = m;
	values = new double*[n];
	for(unsigned int i = 0; i < n; i++) {
		values[i] = new double[m];
	}
}

Matrix::~Matrix() {
	for(unsigned int i = 0; i < n; i++) {
		delete [] values[i];
	}
	delete [] values;
}

double Matrix::get(unsigned int i, unsigned int j) {
	return values[i][j];
}

void Matrix::set(unsigned int i, unsigned int j, double value) {
	values[i][j] = value;
}

unsigned int Matrix::rowsCount() {
	return n;
}

unsigned int Matrix::colsCount() {
	return m;
}
