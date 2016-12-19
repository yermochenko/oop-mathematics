#ifndef JG_IF_NON_ZERO_H_
#define JG_IF_NON_ZERO_H_

#include "jg_for_exchange_rows.h"

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
	For *exchangeRowsElementFor;
public:
	NonZeroElementStatement(Problem *problem)
	{
		this->problem = problem;
		exchangeRowsElementFor = new ExchangeRowsElementFor(problem);
	}
	void execute()
	{
		problem->error = false;
		exchangeRowsElementFor->execute();
	}
	~NonZeroElementStatement()
	{
		delete exchangeRowsElementFor;
	}
};

class NonZeroElementIf : public If
{
	Condition *nonZeroElementCondition;
	Statement *nonZeroElementStatement;
public:
	NonZeroElementIf(Problem *problem) : If(
		nonZeroElementCondition = new NonZeroElementCondition(problem),
		nonZeroElementStatement = new NonZeroElementStatement(problem)
	) {}
	~NonZeroElementIf()
	{
		delete nonZeroElementStatement;
		delete nonZeroElementCondition;
	}
};

#endif /* JG_IF_NON_ZERO_H_ */
