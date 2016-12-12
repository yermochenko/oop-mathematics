/*
 * jg_for_exchange_rows.h
 *
 *  Created on: 12 дек. 2016 г.
 *      Author: User
 */

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


#endif /* JG_FOR_EXCHANGE_ROWS_H_ */
