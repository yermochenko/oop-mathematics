#ifndef JG_FOR_EXCHANGE_ROWS_H_
#define JG_FOR_EXCHANGE_ROWS_H_

class ExchangeRowsElementInitStatement: public Statement
{
	Problem *problem;
public:
	ExchangeRowsElementInitStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->j = 0;
	}
};

class ExchangeRowsElementCondition: public Condition
{
	Problem *problem;
public:
	ExchangeRowsElementCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->j < problem->matrix->colsCount();
	}
};

class ExchangeRowsElementEndIterationStatement: public Statement
{
	Problem *problem;
public:
	ExchangeRowsElementEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->j++;
	}
};

class ExchangeRowsElementBodyStatement: public Statement
{
	Problem *problem;
public:
	ExchangeRowsElementBodyStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		double f1 = problem->matrix->get(problem->i, problem->j);
		problem->matrix->set(problem->i, problem->j, problem->matrix->get(problem->k, problem->j));
		problem->matrix->set(problem->k, problem->j, f1);
	}
};

class ExchangeRowsElementFor : public For
{
	Statement *exchangeRowsElementInitStatement;
	Condition *exchangeRowsElementCondition;
	Statement *exchangeRowsElementEndIterationStatement;
	Statement *exchangeRowsElementBodyStatement;
public:
	ExchangeRowsElementFor(Problem *problem) : For(
		exchangeRowsElementInitStatement = new ExchangeRowsElementInitStatement(problem),
		exchangeRowsElementCondition = new ExchangeRowsElementCondition(problem),
		exchangeRowsElementEndIterationStatement = new ExchangeRowsElementEndIterationStatement(problem),
		exchangeRowsElementBodyStatement = new ExchangeRowsElementBodyStatement(problem)
	) {}
	~ExchangeRowsElementFor()
	{
		delete exchangeRowsElementInitStatement;
		delete exchangeRowsElementCondition;
		delete exchangeRowsElementEndIterationStatement;
		delete exchangeRowsElementBodyStatement;
	}
};

#endif /* JG_FOR_EXCHANGE_ROWS_H_ */
