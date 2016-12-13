#ifndef JG_FOR_INPUT_ROW_FROM_STREAM_H_
#define JG_FOR_INPUT_ROW_FROM_STREAM_H_

#include <iostream>

using namespace std;

class InputRowFromStreamInitStatement: public Statement
{
	Problem *problem;
public:
	InputRowFromStreamInitStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->j = 0;
	}
};

class InputRowFromStreamCondition: public Condition
{
	Problem *problem;
public:
	InputRowFromStreamCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->j < problem->matrix->colsCount();
	}
};

class InputRowFromStreamEndIterationStatement: public Statement
{
	Problem *problem;
public:
	InputRowFromStreamEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->j++;
	}
};

class InputRowFromStreamBodyStatement: public Statement
{
	Problem *problem;
public:
	InputRowFromStreamBodyStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		double e;
		problem->fs->operator>>(e);
		problem->matrix->set(problem->i, problem->j, e);
		cout << e << "\t";
	}
};

#endif /* JG_FOR_INPUT_ROW_FROM_STREAM_H_ */
