#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {
	double **values;
	unsigned int n;
	unsigned int m;
public:
	Matrix(unsigned int n, unsigned int m);
	virtual ~Matrix();
	double get(unsigned int i, unsigned int j);
	void set(unsigned int i, unsigned int j, double value);
	unsigned int rowsCount();
	unsigned int colsCount();
};

#endif /* MATRIX_H_ */
