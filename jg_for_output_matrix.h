#ifndef JG_FOR_OUTPUT_MATRIX_H_
#define JG_FOR_OUTPUT_MATRIX_H_

#include <iostream>

using namespace std;

class OutputMatrixInitStatement: public Statement
{
	Problem *problem;
public:
	OutputMatrixInitStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->i = 0;
	}
};

class OutputMatrixCondition: public Condition
{
	Problem *problem;
public:
	OutputMatrixCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->i < problem->matrix->rowsCount();
	}
};

class OutputMatrixEndIterationStatement: public Statement
{
	Problem *problem;
public:
	OutputMatrixEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->i++;
	}
};

class OutputMatrixBodyStatement: public Statement
{
	Problem *problem;
public:
	OutputMatrixBodyStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		cout << "x[" << problem->i << "] = " << problem->matrix->get(problem->i, problem->matrix->colsCount() - 1) << endl;
	}
};

#endif /* JG_FOR_OUTPUT_MATRIX_H_ */
