/*
 * jg_for_exchange_rows.h
 *
 *  Created on: 12 ���. 2016 �.
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
