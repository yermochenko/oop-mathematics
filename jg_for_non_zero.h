#ifndef JG_FOR_NON_ZERO_H_
#define JG_FOR_NON_ZERO_H_

#include <iostream>

using namespace std;

#include "jg_if_non_zero.h"

class NonZeroElementForInitStatement: public Statement
{
	Problem *problem;
public:
	NonZeroElementForInitStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->k = problem->i + 1;
	}
};

class NonZeroElementForCondition: public Condition
{
	Problem *problem;
public:
	NonZeroElementForCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->error && problem->k < problem->matrix->rowsCount();
	}
};

class NonZeroElementForEndIterationStatement: public Statement
{
	Problem *problem;
public:
	NonZeroElementForEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->k++;
	}
};

class NonZeroElementForBodyStatement: public Statement
{
	If *nonZeroElementIf;
public:
	NonZeroElementForBodyStatement(Problem *problem)
	{
		nonZeroElementIf = new NonZeroElementIf(problem);
	}
	void execute()
	{
		nonZeroElementIf->execute();
	}
	~NonZeroElementForBodyStatement()
	{
		delete nonZeroElementIf;
	}
};

#endif /* JG_FOR_NON_ZERO_H_ */
