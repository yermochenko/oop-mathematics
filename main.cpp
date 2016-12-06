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
};

class ErrorStatement: public Statement
{
public:
	void execute()
	{
		throw "Нет единственного решения";
	}
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
	try
	{
		double  f;
		for (unsigned int i = 0; i < problem.matrix->rowsCount(); i++)
		{
			// проверка на 0
			if (problem.matrix->get(i, i) == 0)
			{
				problem.error = true;
				for (unsigned int k = i + 1; problem.error && k < problem.matrix->rowsCount(); k++)
				{
					if (problem.matrix->get(k, i) != 0)
					{
						problem.error = false;
						double f1;
						for (unsigned int j = 0; j < problem.matrix->colsCount(); j++)
						{
							f1 = problem.matrix->get(i, j);
							problem.matrix->set(i, j, problem.matrix->get(k, j));
							problem.matrix->set(k, j, f1);
						}
					}
				}
				Condition *errorCondition = new ErrorCondition(&problem);
				Statement *errorStatement = new ErrorStatement();
				If *errorIf = new If(errorCondition, errorStatement);
				errorIf->execute();
				delete errorIf;
				delete errorStatement;
				delete errorCondition;
			}//Конец проверки на 0
			f = problem.matrix->get(i, i);
			for (unsigned int j = 0; j < problem.matrix->colsCount(); j++)
			{
				problem.matrix->set(i, j, problem.matrix->get(i, j) / f);
			}
			for (unsigned int k = 0; k < problem.matrix->rowsCount(); k++)
			{
				if (k != i)
				{
					double g = problem.matrix->get(k, i);
					for (unsigned int j = 0; j < problem.matrix->colsCount(); j++)
					{
						problem.matrix->set(k, j, -g * problem.matrix->get(i, j) + problem.matrix->get(k, j));//делаем нули
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
	delete problem.matrix;
	return 0;
}
