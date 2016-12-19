#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include "matrix.h"
#include "struct.h"
#include "problem.h"
#include "jg_for_input_matrix_from_stream.h"
#include "jg_for_making_e_matrix.h"
#include "jg_for_output_matrix.h"

int main()
{
	setlocale(LC_ALL, "rus");
	fstream fs("text.txt");//читаем из файла
	Problem problem;
	problem.fs = &fs;
	unsigned int n;
	problem.fs->operator>>(n);
	problem.matrix = new Matrix(n, n + 1);

	InputMatrixFromStream *inputMatrixFromStream = new InputMatrixFromStream(&problem);
	inputMatrixFromStream->execute();
	delete inputMatrixFromStream;

	problem.fs->close();

	MakingEMatrix *makingEMatrix = new MakingEMatrix(&problem);
	OutputMatrix *outputMatrix = new OutputMatrix(&problem);

	//Метод Жордана-Гаусса
	//Прямой ход, приведение к верхнетреугольному виду
	try
	{
		makingEMatrix->execute();
		outputMatrix->execute();
		cout << endl;
	}
	catch(char *message)
	{
		cout << message << endl;
	}

	delete makingEMatrix;
	delete outputMatrix;

	delete problem.matrix;
	return 0;
}
