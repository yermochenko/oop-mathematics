#ifndef JG_IF_ZERO_H_
#define JG_IF_ZERO_H_

#include "jg_if_error.h"
#include "jg_for_non_zero.h"

class ZeroElementCondition: public Condition
{
	Problem *problem;
public:
	ZeroElementCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->matrix->get(problem->i, problem->i) == 0;
	}
};

class ZeroElementStatement: public Statement
{
	Problem *problem;
	For *nonZeroElementFor;
	If *errorIf;
public:
	ZeroElementStatement(Problem *problem)
	{
		this->problem = problem;
		nonZeroElementFor = new NonZeroElementFor(problem);
		errorIf = new ErrorIf(problem);
	}
	void execute()
	{
		problem->error = true;
		nonZeroElementFor->execute();
		errorIf->execute();
	}
	~ZeroElementStatement()
	{
		delete errorIf;
		delete nonZeroElementFor;
	}
};

class ZeroElementIf : public If
{
	Condition *zeroElementCondition ;
	Statement *zeroElementStatement;
public:
	ZeroElementIf(Problem *problem) : If(
		zeroElementCondition = new ZeroElementCondition(problem),
		zeroElementStatement = new ZeroElementStatement(problem)
	) {}
	~ZeroElementIf()
	{
		delete zeroElementCondition;
		delete zeroElementStatement;
	}
};

#endif /* JG_IF_ZERO_H_ */
