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

class NonZeroElementFor : public For
{
	NonZeroElementForInitStatement *nonZeroElementForInitStatement;
	NonZeroElementForCondition *nonZeroElementForCondition;
	NonZeroElementForEndIterationStatement *nonZeroElementForEndIterationStatement;
	NonZeroElementForBodyStatement *nonZeroElementForBodyStatement;
public:
	NonZeroElementFor(Problem *problem) : For(
		nonZeroElementForInitStatement = new NonZeroElementForInitStatement(problem),
		nonZeroElementForCondition = new NonZeroElementForCondition(problem),
		nonZeroElementForEndIterationStatement = new NonZeroElementForEndIterationStatement(problem),
		nonZeroElementForBodyStatement = new NonZeroElementForBodyStatement(problem)
	) {}
	~NonZeroElementFor()
	{
		delete nonZeroElementForInitStatement;
		delete nonZeroElementForCondition;
		delete nonZeroElementForEndIterationStatement;
		delete nonZeroElementForBodyStatement;
	}
};

#endif /* JG_FOR_NON_ZERO_H_ */
