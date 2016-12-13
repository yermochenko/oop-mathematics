/*
 * jg_if_non_zero.h
 *
 *  Created on: 12 дек. 2016 г.
 *      Author: User
 */

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
	Statement *exchangeRowsElementInitStatement;
	Condition *exchangeRowsElementCondition;
	Statement *exchangeRowsElementEndIterationStatement;
	Statement *exchangeRowsElementBodyStatement;
	For *exchangeRowsElementFor;
public:
	NonZeroElementStatement(Problem *problem)
	{
		this->problem = problem;
		exchangeRowsElementInitStatement = new ExchangeRowsElementInitStatement(problem);
		exchangeRowsElementCondition = new ExchangeRowsElementCondition(problem);
		exchangeRowsElementEndIterationStatement = new ExchangeRowsElementEndIterationStatement(problem);
		exchangeRowsElementBodyStatement = new ExchangeRowsElementBodyStatement(problem);
		exchangeRowsElementFor = new For(exchangeRowsElementInitStatement, exchangeRowsElementCondition, exchangeRowsElementEndIterationStatement, exchangeRowsElementBodyStatement);
	}
	void execute()
	{
		problem->error = false;
		exchangeRowsElementFor->execute();
	}
	~NonZeroElementStatement()
	{
		delete exchangeRowsElementFor;
		delete exchangeRowsElementInitStatement;
		delete exchangeRowsElementCondition;
		delete exchangeRowsElementEndIterationStatement;
		delete exchangeRowsElementBodyStatement;
	}
};

#endif /* JG_IF_NON_ZERO_H_ */
