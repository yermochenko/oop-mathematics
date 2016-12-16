#ifndef JG_IF_ERROR_H_
#define JG_IF_ERROR_H_

class ErrorCondition: public Condition
{
	Problem* problem;
public:
	ErrorCondition(Problem* problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->error;
	}
};

class ErrorStatement: public Statement
{
public:
	void execute()
	{
		throw "Нет единственного решения";
	}
};

#endif /* JG_IF_ERROR_H_ */
