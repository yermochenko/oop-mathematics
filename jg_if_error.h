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

class ErrorIf : public If
{
	Condition *errorCondition;
	Statement *errorStatement;
public:
	ErrorIf(Problem *problem) : If(
		errorCondition = new ErrorCondition(problem),
		errorStatement = new ErrorStatement()
	) {}
	~ErrorIf()
	{
		delete errorStatement;
		delete errorCondition;
	}
};

#endif /* JG_IF_ERROR_H_ */
