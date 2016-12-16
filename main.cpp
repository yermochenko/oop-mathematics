#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include "matrix.h"
#include "struct.h"
#include "problem.h"
#include "jg_for_input_matrix_from_stream.h"
#include "jg_for_output_matrix.h"
#include "jg_for_making_e_matrix.h"

int main()
{
	setlocale(LC_ALL, "rus");
	fstream fs("text.txt");//читаем из файла
	Problem problem;
	problem.fs = &fs;
	unsigned int n;
	problem.fs->operator>>(n);
	problem.matrix = new Matrix(n, n + 1);

	Statement *inputMatrixFromStreamInitStatement = new InputMatrixFromStreamInitStatement(&problem);
	Condition *inputMatrixFromStreamCondition = new InputMatrixFromStreamCondition(&problem);
	Statement *inputMatrixFromStreamEndIterationStatement = new InputMatrixFromStreamEndIterationStatement(&problem);
	Statement *inputMatrixFromStreamBodyStatement = new InputMatrixFromStreamBodyStatement(&problem);
	For *inputMatrixFromStream = new For(inputMatrixFromStreamInitStatement, inputMatrixFromStreamCondition, inputMatrixFromStreamEndIterationStatement, inputMatrixFromStreamBodyStatement);

	inputMatrixFromStream->execute();

	delete inputMatrixFromStream;
	delete inputMatrixFromStreamInitStatement;
	delete inputMatrixFromStreamCondition;
	delete inputMatrixFromStreamEndIterationStatement;
	delete inputMatrixFromStreamBodyStatement;

	problem.fs->close();

	//Метод Жордана-Гаусса
	//Прямой ход, приведение к верхнетреугольному виду



 	Statement *outputMatrixInitStatement = new OutputMatrixInitStatement(&problem);
	Condition *outputMatrixCondition = new OutputMatrixCondition(&problem);
	Statement *outputMatrixEndIterationStatement = new OutputMatrixEndIterationStatement(&problem);
	Statement *outputMatrixBodyStatement = new OutputMatrixBodyStatement(&problem);
	For *outputMatrix = new For(outputMatrixInitStatement, outputMatrixCondition, outputMatrixEndIterationStatement, outputMatrixBodyStatement);

	Statement *makingEMatrixInitStatement = new MakingEMatrixInitStatement(&problem);
	Condition *makingEMatrixCondition = new MakingEMatrixCondition(&problem);
	Statement *makingEMatrixEndIterationStatement = new MakingEMatrixEndIterationStatement(&problem);
	Statement *makingEMatrixBodyStatement = new MakingEMatrixBodyStatement(&problem);
	For *makingEMatrix = new For(makingEMatrixInitStatement, makingEMatrixCondition, makingEMatrixEndIterationStatement, makingEMatrixBodyStatement);
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

	delete makingEMatrixInitStatement;
	delete makingEMatrixCondition;
	delete makingEMatrixEndIterationStatement;
	delete makingEMatrixBodyStatement;
	delete makingEMatrix;
	delete outputMatrixInitStatement;
	delete outputMatrixCondition;
	delete outputMatrixEndIterationStatement;
	delete outputMatrixBodyStatement;
	delete outputMatrix;

	delete problem.matrix;
	return 0;
}
