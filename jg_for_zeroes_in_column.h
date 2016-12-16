#ifndef JG_FOR_ZERO_IN_COLUMNS_H_
#define JG_FOR_ZERO_IN_COLUMNS_H_

#include <iostream>

using namespace std;

#include "jg_if_non_main_element.h"

class ZeroInColumnForInitStatement: public Statement
{
	Problem *problem;
public:
	ZeroInColumnForInitStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->k = 0;
	}
};

class ZeroInColumnForCondition: public Condition
{
	Problem *problem;
public:
	ZeroInColumnForCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->k < problem->matrix->rowsCount();
	}
};

class ZeroInColumnForEndIterationStatement: public Statement
{
	Problem *problem;
public:
	ZeroInColumnForEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->k++;
	}
};

class ZeroInColumnForBodyStatement: public Statement
{
	Problem *problem;
	Condition *nonMainElementCondition;
	Statement *nonMainElementStatement;
	If *nonMainElementIf;
public:
	ZeroInColumnForBodyStatement(Problem *problem)
	{
		this->problem = problem;
		nonMainElementCondition = new NonMainElementCondition(problem);
		nonMainElementStatement = new NonMainElementStatement(problem);
		nonMainElementIf = new If(nonMainElementCondition, nonMainElementStatement);
	}
	void execute()
	{
		nonMainElementIf->execute();
	}
	~ZeroInColumnForBodyStatement()
	{
		delete nonMainElementCondition;
		delete nonMainElementStatement;
		delete nonMainElementIf;
	}
};

#endif /* JG_FOR_ZERO_IN_COLUMNS_H_ */
