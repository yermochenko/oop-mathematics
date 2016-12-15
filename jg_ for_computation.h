#ifndef JG_FOR_COMPUTATION_H_
#define JG_FOR_COMPUTATION_H_

class ComputationForInitStatement: public Statement
{
	Problem *problem;
public:
	ComputationForInitStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->j = 0;
	}
};

class ComputationForCondition: public Condition
{
	Problem *problem;
public:
	ComputationForCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->j < problem->matrix->colsCount();
	}
};

class ComputationForEndIterationStatement: public Statement
{
	Problem *problem;
public:
	ComputationForEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->j++;
	}
};

class ComputationForBodyStatement: public Statement
{
	Problem *problem;
public:
	ComputationForBodyStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->matrix->set(problem->k, problem->j, -problem->f * problem->matrix->get(problem->i, problem->j) + problem->matrix->get(problem->k, problem->j));
	}
};

#endif /* JG_FOR_COMPUTATION_H_ */
