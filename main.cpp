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

int main()
{
	setlocale(LC_ALL, "rus");
	fstream fs("text.txt");//читаем из файла
	Problem problem;
	problem.fs = &fs;
	unsigned int n;
	//fs >> n;
	problem.fs->operator>>(n);
	double e;
	problem.matrix = new Matrix(n, n + 1);

	Statement *inputMatrixFromStreamInitStatement = new InputMatrixFromStreamInitStatement(&problem);
	Condition *inputMatrixFromStreamCondition = new InputMatrixFromStreamCondition(&problem);
	Statement *inputMatrixFromStreamEndIterationStatement = new InputMatrixFromStreamEndIterationStatement(&problem);
	Statement *inputMatrixFromStreamBodyStatement = new InputMatrixFromStreamBodyStatement(&problem);
	For *inputMatrixFromStream = new For(inputMatrixFromStreamInitStatement, inputMatrixFromStreamCondition, inputMatrixFromStreamEndIterationStatement, inputMatrixFromStreamBodyStatement);

	/*Statement *inputRowFromStreamInitStatement = new InputRowFromStreamInitStatement(&problem);
	Condition *inputRowFromStreamCondition = new InputRowFromStreamCondition(&problem);
	Statement *inputRowFromStreamEndIterationStatement = new InputRowFromStreamEndIterationStatement(&problem);
	Statement *inputRowFromStreamBodyStatement = new InputRowFromStreamBodyStatement(&problem);
	For *inputRowFromStream = new For(inputRowFromStreamInitStatement, inputRowFromStreamCondition, inputRowFromStreamEndIterationStatement, inputRowFromStreamBodyStatement);
	for (problem.i = 0; problem.i < problem.matrix->rowsCount(); problem.i++)
	{
		for (unsigned int j = 0; j < problem.matrix->colsCount(); j++)
		{
			fs >> e;
			problem.matrix->set(i, j, e);
			cout << e << "\t";
		}
		inputRowFromStream->execute();
		cout << endl;
	}
	delete inputRowFromStream;
	delete inputRowFromStreamInitStatement;
	delete inputRowFromStreamCondition;
	delete inputRowFromStreamEndIterationStatement;
	delete inputRowFromStreamBodyStatement;*/
	inputMatrixFromStream->execute();

	delete inputMatrixFromStream;
	delete inputMatrixFromStreamInitStatement;
	delete inputMatrixFromStreamCondition;
	delete inputMatrixFromStreamEndIterationStatement;
	delete inputMatrixFromStreamBodyStatement;

	fs.close();

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
	try
	{
		double  f;
		for (problem.i = 0; problem.i < problem.matrix->rowsCount(); problem.i++)
		{
			// проверка на 0
			if (problem.matrix->get(problem.i, problem.i) == 0)
			{
				problem.error = true;
				nonZeroElementFor->execute();
				errorIf->execute();
			}//Конец проверки на 0
			f = problem.matrix->get(problem.i, problem.i);
			for (unsigned int j = 0; j < problem.matrix->colsCount(); j++)
			{
				problem.matrix->set(problem.i, j, problem.matrix->get(problem.i, j) / f);
			}
			for (unsigned int k = 0; k < problem.matrix->rowsCount(); k++)
			{
				if (k != problem.i)
				{
					f = problem.matrix->get(k, problem.i);
					for (unsigned int j = 0; j < problem.matrix->colsCount(); j++)
					{
						problem.matrix->set(k, j, -f * problem.matrix->get(problem.i, j) + problem.matrix->get(k, j));//делаем нули
					}
				}
			}
		}

     	Statement *outputMatrixInitStatement = new OutputMatrixInitStatement(&problem);
		Condition *outputMatrixCondition = new OutputMatrixCondition(&problem);
		Statement *outputMatrixEndIterationStatement = new OutputMatrixEndIterationStatement(&problem);
		Statement *outputMatrixBodyStatement = new OutputMatrixBodyStatement(&problem);
		For *outputMatrix = new For(outputMatrixInitStatement, outputMatrixCondition, outputMatrixEndIterationStatement, outputMatrixBodyStatement);
		outputMatrix->execute();
		cout << endl;
		delete outputMatrixInitStatement;
		delete outputMatrixCondition;
		delete outputMatrixEndIterationStatement;
		delete outputMatrixBodyStatement;
		delete outputMatrix;
	}
	catch(char *message)
	{
		cout << message << endl;
	}
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
