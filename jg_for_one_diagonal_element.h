#ifndef JG_FOR_DIAGONAL_ELEMENT_H_
#define JG_FOR_DIAGONAL_ELEMENT_H_

class OneDiagonalElementInitStatement: public Statement
{
	Problem *problem;
public:
	OneDiagonalElementInitStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->j = 0;
	}
};

class OneDiagonalElementCondition: public Condition
{
	Problem *problem;
public:
	OneDiagonalElementCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->j < problem->matrix->colsCount();
	}
};

class OneDiagonalElementEndIterationStatement: public Statement
{
	Problem *problem;
public:
	OneDiagonalElementEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->j++;
	}
};

class OneDiagonalElementBodyStatement: public Statement
{
	Problem *problem;
public:
	OneDiagonalElementBodyStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->matrix->set(problem->i, problem->j, problem->matrix->get(problem->i, problem->j) / problem->f);
	}

};

class OneDiagonalElement : public For
{
	Statement *oneDiagonalElementInitStatement;
	Condition *oneDiagonalElementCondition;
	Statement *oneDiagonalElementEndIterationStatement;
	Statement *oneDiagonalElementBodyStatement;
public:
	OneDiagonalElement(Problem* problem) : For(
		oneDiagonalElementInitStatement = new OneDiagonalElementInitStatement(problem),
		oneDiagonalElementCondition = new OneDiagonalElementCondition(problem),
		oneDiagonalElementEndIterationStatement = new OneDiagonalElementEndIterationStatement(problem),
		oneDiagonalElementBodyStatement = new OneDiagonalElementBodyStatement(problem)
	) {}
	~OneDiagonalElement()
	{
		delete oneDiagonalElementInitStatement;
		delete oneDiagonalElementCondition;
		delete oneDiagonalElementEndIterationStatement;
		delete oneDiagonalElementBodyStatement;
	}
};

#endif  /*JG_FOR_DIAGONAL_ELEMENT_H_*/
