#ifndef JG_IF_NON_MAIN_ELEMENT_H_
#define JG_IF_NON_MAIN_ELEMENT_H_

#include "jg_for_computation.h"

class NonMainElementCondition: public Condition
{
	Problem* problem;
public:
	NonMainElementCondition(Problem* problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->k != problem->i;
	}
};

class NonMainElementStatement: public Statement
{
	Problem* problem;
	For *computationFor;
public:
	NonMainElementStatement(Problem* problem)
	{
		this->problem = problem;
		computationFor = new ComputationFor(problem);
	}
	void execute()
	{
		problem->f = problem->matrix->get(problem->k, problem->i);
		computationFor->execute();
	}
	~NonMainElementStatement()
	{
		delete computationFor;
	}
};

class NonMainElementIf: public If {
	Condition *nonMainElementCondition;
	Statement *nonMainElementStatement;
public:
	NonMainElementIf(Problem *problem) : If(
		nonMainElementCondition = new NonMainElementCondition(problem),
		nonMainElementStatement = new NonMainElementStatement(problem)
	) {}
	~NonMainElementIf()
	{
		delete nonMainElementCondition;
		delete nonMainElementStatement;
	}
};

#endif /* JG_IF_NON_MAIN_ELEMENT_H_ */
