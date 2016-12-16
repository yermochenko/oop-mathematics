#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include "matrix.h"
#include "struct.h"
#include "problem.h"
#include "jg_if_error.h"
#include "jg_for_input_matrix_from_stream.h"
#include "jg_for_output_matrix.h"
#include "jg_for_non_zero.h"
#include "jg_for_one_diagonal_element.h"
#include "jg_if_non_main_element.h"

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
	Condition *errorCondition = new ErrorCondition(&problem);
	Statement *errorStatement = new ErrorStatement();
	If *errorIf = new If(errorCondition, errorStatement);
	NonZeroElementForInitStatement *nonZeroElementForInitStatement = new NonZeroElementForInitStatement(&problem);
	NonZeroElementForCondition *nonZeroElementForCondition = new NonZeroElementForCondition(&problem);
	NonZeroElementForEndIterationStatement *nonZeroElementForEndIterationStatement = new NonZeroElementForEndIterationStatement(&problem);
	NonZeroElementForBodyStatement *nonZeroElementForBodyStatement = new NonZeroElementForBodyStatement(&problem);
	For *nonZeroElementFor = new For(nonZeroElementForInitStatement, nonZeroElementForCondition, nonZeroElementForEndIterationStatement, nonZeroElementForBodyStatement);
	Condition *nonMainElementCondition = new NonMainElementCondition(&problem);
	Statement *nonMainElementStatement = new NonMainElementStatement(&problem);
	If *nonMainElementIf = new If(nonMainElementCondition, nonMainElementStatement);
	Statement *oneDiagonalElementInitStatement = new OneDiagonalElementInitStatement(&problem);
	Condition *oneDiagonalElementCondition = new OneDiagonalElementCondition(&problem);
	Statement *oneDiagonalElementEndIterationStatement = new OneDiagonalElementEndIterationStatement(&problem);
	Statement *oneDiagonalElementBodyStatement = new OneDiagonalElementBodyStatement(&problem);
	For *oneDiagonalElement = new For(oneDiagonalElementInitStatement, oneDiagonalElementCondition, oneDiagonalElementEndIterationStatement, oneDiagonalElementBodyStatement);
 	Statement *outputMatrixInitStatement = new OutputMatrixInitStatement(&problem);
	Condition *outputMatrixCondition = new OutputMatrixCondition(&problem);
	Statement *outputMatrixEndIterationStatement = new OutputMatrixEndIterationStatement(&problem);
	Statement *outputMatrixBodyStatement = new OutputMatrixBodyStatement(&problem);
	For *outputMatrix = new For(outputMatrixInitStatement, outputMatrixCondition, outputMatrixEndIterationStatement, outputMatrixBodyStatement);
	try
	{
		for (problem.i = 0; problem.i < problem.matrix->rowsCount(); problem.i++)
		{
			// проверка на 0
			if (problem.matrix->get(problem.i, problem.i) == 0)
			{
				problem.error = true;
				nonZeroElementFor->execute();
				errorIf->execute();
			}//Конец проверки на 0
			problem.f = problem.matrix->get(problem.i, problem.i);
			oneDiagonalElement->execute();
			for (problem.k = 0; problem.k < problem.matrix->rowsCount(); problem.k++)
			{
				nonMainElementIf->execute();
			}
		}
		outputMatrix->execute();
		cout << endl;
	}
	catch(char *message)
	{
		cout << message << endl;
	}
	delete nonMainElementCondition;
	delete nonMainElementStatement;
	delete nonMainElementIf;
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
	delete nonZeroElementFor;
	delete nonZeroElementForInitStatement;
	delete nonZeroElementForCondition;
	delete nonZeroElementForEndIterationStatement;
	delete nonZeroElementForBodyStatement;
	delete errorIf;
	delete errorStatement;
	delete errorCondition;
	delete problem.matrix;
	return 0;
}
