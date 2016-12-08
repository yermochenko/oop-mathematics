#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include "matrix.h"
#include "struct.h"

class Problem
{
public:
	Matrix* matrix;
	bool error;
	int i, k;
};

class ErrorCondition: public Condition
{
	Problem* problem;
public:
	ErrorCondition(Problem* problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->error;
	}
};

class ErrorStatement: public Statement
{
public:
	void execute()
	{
		throw "Нет единственного решения";
	}
};

class NonZeroElementCondition: public Condition
{
	Problem *problem;
public:
	NonZeroElementCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->matrix->get(problem->k, problem->i) != 0;
	}
};

class NonZeroElementStatement: public Statement
{
	Problem *problem;
public:
	NonZeroElementStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->error = false;
		double f1;
		for (unsigned int j = 0; j < problem->matrix->colsCount(); j++)
		{
			f1 = problem->matrix->get(problem->i, j);
			problem->matrix->set(problem->i, j, problem->matrix->get(problem->k, j));
			problem->matrix->set(problem->k, j, f1);
		}
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
