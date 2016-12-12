#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include "matrix.h"
#include "struct.h"
#include "problem.h"
#include "jg_if_error.h"
#include "jg_for_exchange_rows.h"
#include "jg_if_non_zero.h"


class ExchangeRowsElementCondition: public Condition
{
	Problem *problem;
public:
	ExchangeRowsElementCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->j < problem->matrix->colsCount();
	}
};

class ExchangeRowsElementEndIterationStatement: public Statement
{
	Problem *problem;
public:
	ExchangeRowsElementEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->j++;
	}
};

class ExchangeRowsElementBodyStatement: public Statement
{
	Problem *problem;
public:
	ExchangeRowsElementBodyStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		double f1 = problem->matrix->get(problem->i, problem->j);
		problem->matrix->set(problem->i, problem->j, problem->matrix->get(problem->k, problem->j));
		problem->matrix->set(problem->k, problem->j, f1);
	}
};

// jg_if_non_zero.h

class NonZeroElementStatement: public Statement
{
	Problem *problem;
	Statement *exchangeRowsElementInitStatement;
	Condition *exchangeRowsElementCondition;
	Statement *exchangeRowsElementEndIterationStatement;
	Statement *exchangeRowsElementBodyStatement;
	For *exchangeRowsElementFor;
public:
	NonZeroElementStatement(Problem *problem)
	{
		this->problem = problem;
		exchangeRowsElementInitStatement = new ExchangeRowsElementInitStatement(problem);
		exchangeRowsElementCondition = new ExchangeRowsElementCondition(problem);
		exchangeRowsElementEndIterationStatement = new ExchangeRowsElementEndIterationStatement(problem);
		exchangeRowsElementBodyStatement = new ExchangeRowsElementBodyStatement(problem);
		exchangeRowsElementFor = new For(exchangeRowsElementInitStatement, exchangeRowsElementCondition, exchangeRowsElementEndIterationStatement, exchangeRowsElementBodyStatement);
	}
	void execute()
	{
		problem->error = false;
		exchangeRowsElementFor->execute();
	}
	~NonZeroElementStatement()
	{
		delete exchangeRowsElementFor;
		delete exchangeRowsElementInitStatement;
		delete exchangeRowsElementCondition;
		delete exchangeRowsElementEndIterationStatement;
		delete exchangeRowsElementBodyStatement;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	fstream fs("text.txt");//читаем из файла
	unsigned int n;
	fs >> n;
	double e;
	Problem problem;
	problem.matrix = new Matrix(n, n + 1);
	for (unsigned int i = 0; i < problem.matrix->rowsCount(); i++)
	{
		for (unsigned int j = 0; j < problem.matrix->colsCount(); j++)
		{
			fs >> e;
			problem.matrix->set(i, j, e);
			cout << e << "\t";
		}
		cout << endl;
	}
	fs.close();

	//Метод Жердана-Гаусса
	//Прямой ход, приведение к верхнетреугольному виду
	Condition *errorCondition = new ErrorCondition(&problem);
	Statement *errorStatement = new ErrorStatement();
	If *errorIf = new If(errorCondition, errorStatement);
	Condition *nonZeroElementCondition = new NonZeroElementCondition(&problem);
	Statement *nonZeroElementStatement = new NonZeroElementStatement(&problem);
	If *nonZeroElementIf = new If(nonZeroElementCondition, nonZeroElementStatement);
	try
	{
		double  f;
		for (problem.i = 0; problem.i < problem.matrix->rowsCount(); problem.i++)
		{
			// проверка на 0
			if (problem.matrix->get(problem.i, problem.i) == 0)
			{
				problem.error = true;
				for (problem.k = problem.i + 1; problem.error && problem.k < problem.matrix->rowsCount(); problem.k++)
				{
					nonZeroElementIf->execute();
				}
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
					double g = problem.matrix->get(k, problem.i);
					for (unsigned int j = 0; j < problem.matrix->colsCount(); j++)
					{
						problem.matrix->set(k, j, -g * problem.matrix->get(problem.i, j) + problem.matrix->get(k, j));//делаем нули
					}
				}
			}
		}

		//Выводим решение
		for (unsigned int i = 0; i < problem.matrix->rowsCount(); i++)
		{
			cout << "x[" << i << "] = " << problem.matrix->get(i, problem.matrix->colsCount() - 1) << " " << endl;
		}
		cout << endl;
	}
	catch(char *message)
	{
		cout << message << endl;
	}
	delete errorIf;
	delete errorStatement;
	delete errorCondition;
	delete nonZeroElementIf;
	delete nonZeroElementStatement;
	delete nonZeroElementCondition;
	delete problem.matrix;
	return 0;
}
