#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include "matrix.h"
#include "struct.h"
#include "problem.h"
#include "jg_for_input_matrix_from_stream.h"
#include "jg_for_output_matrix.h"
#include "jg_for_one_diagonal_element.h"
#include "jg_if_zero.h"
#include "jg_for_zeroes_in_column.h"

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
	Condition *zeroElementCondition = new ZeroElementCondition(&problem);
	Statement *zeroElementStatement = new ZeroElementStatement(&problem);
	If *zeroElementIf = new If(zeroElementCondition, zeroElementStatement);
	Statement *oneDiagonalElementInitStatement = new OneDiagonalElementInitStatement(&problem);
	Condition *oneDiagonalElementCondition = new OneDiagonalElementCondition(&problem);
	Statement *oneDiagonalElementEndIterationStatement = new OneDiagonalElementEndIterationStatement(&problem);
	Statement *oneDiagonalElementBodyStatement = new OneDiagonalElementBodyStatement(&problem);
	For *oneDiagonalElement = new For(oneDiagonalElementInitStatement, oneDiagonalElementCondition, oneDiagonalElementEndIterationStatement, oneDiagonalElementBodyStatement);
	Statement *zeroInColumnForInitStatement = new ZeroInColumnForInitStatement(&problem);
	Condition *zeroInColumnForCondition = new ZeroInColumnForCondition(&problem);
	Statement *zeroInColumnForEndIterationStatement = new ZeroInColumnForEndIterationStatement(&problem);
	Statement *zeroInColumnForBodyStatement = new ZeroInColumnForBodyStatement(&problem);
	For *zeroInColumn = new For(zeroInColumnForInitStatement, zeroInColumnForCondition, zeroInColumnForEndIterationStatement, zeroInColumnForBodyStatement);
 	Statement *outputMatrixInitStatement = new OutputMatrixInitStatement(&problem);
	Condition *outputMatrixCondition = new OutputMatrixCondition(&problem);
	Statement *outputMatrixEndIterationStatement = new OutputMatrixEndIterationStatement(&problem);
	Statement *outputMatrixBodyStatement = new OutputMatrixBodyStatement(&problem);
	For *outputMatrix = new For(outputMatrixInitStatement, outputMatrixCondition, outputMatrixEndIterationStatement, outputMatrixBodyStatement);
	try
	{
		for (problem.i = 0; problem.i < problem.matrix->rowsCount(); problem.i++)
		{
			zeroElementIf->execute();
			problem.f = problem.matrix->get(problem.i, problem.i);
			oneDiagonalElement->execute();
			zeroInColumn->execute();
		}
		outputMatrix->execute();
		cout << endl;
	}
	catch(char *message)
	{
		cout << message << endl;
	}
	delete zeroElementIf;
	delete zeroElementCondition;
	delete zeroElementStatement;
	delete zeroInColumn;
	delete zeroInColumnForInitStatement;
	delete zeroInColumnForCondition;
	delete zeroInColumnForEndIterationStatement;
	delete zeroInColumnForBodyStatement;
	delete outputMatrixInitStatement;
	delete outputMatrixCondition;
	delete outputMatrixEndIterationStatement;
	delete outputMatrixBodyStatement;
	delete outputMatrix;
	delete oneDiagonalElement;
	delete oneDiagonalElementInitStatement;
	delete oneDiagonalElementCondition;
	delete oneDiagonalElementEndIterationStatement;
	delete oneDiagonalElementBodyStatement;
	delete problem.matrix;
	return 0;
}
