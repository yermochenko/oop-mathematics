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
	If *nonMainElementIf;
public:
	ZeroInColumnForBodyStatement(Problem *problem)
	{
		nonMainElementIf = new NonMainElementIf(problem);
	}
	void execute()
	{
		nonMainElementIf->execute();
	}
	~ZeroInColumnForBodyStatement()
	{
		delete nonMainElementIf;
	}
};

class ZeroInColumn:public For
{
	Statement *zeroInColumnInitStatement;
	Condition *zeroInColumnCondition;
	Statement *zeroInColumnEndIterationStatement;
	Statement *zeroInColumnBodyStatement;
public:
	ZeroInColumn(Problem* problem) : For (
		zeroInColumnInitStatement = new ZeroInColumnForInitStatement(problem),
		zeroInColumnCondition = new ZeroInColumnForCondition(problem),
		zeroInColumnEndIterationStatement = new ZeroInColumnForEndIterationStatement(problem),
		zeroInColumnBodyStatement = new ZeroInColumnForBodyStatement(problem)
	) {}
	~ZeroInColumn()
	{
		delete zeroInColumnInitStatement;
		delete zeroInColumnCondition;
		delete zeroInColumnEndIterationStatement;
		delete zeroInColumnBodyStatement;
	}
};

#endif /* JG_FOR_ZERO_IN_COLUMNS_H_ */
