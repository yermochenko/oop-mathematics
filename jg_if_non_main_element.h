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
	Statement *computationForInitStatement;
	Condition *computationForCondition;
	Statement *computationForEndIterationStatement;
	Statement *computationForBodyStatement;
	For *computationFor;
public:
	NonMainElementStatement(Problem* problem)
	{
		this->problem = problem;
		computationForInitStatement = new ComputationForInitStatement(problem);
		computationForCondition = new ComputationForCondition(problem);
		computationForEndIterationStatement = new ComputationForEndIterationStatement(problem);
		computationForBodyStatement = new ComputationForBodyStatement(problem);
		computationFor = new For(computationForInitStatement, computationForCondition, computationForEndIterationStatement, computationForBodyStatement);
	}
	void execute()
	{
		problem->f = problem->matrix->get(problem->k, problem->i);
		computationFor->execute();
	}
	~NonMainElementStatement()
	{
		delete computationFor;
		delete computationForInitStatement;
		delete computationForCondition;
		delete computationForEndIterationStatement;
		delete computationForBodyStatement;
	}
};

#endif /* JG_IF_NON_MAIN_ELEMENT_H_ */
