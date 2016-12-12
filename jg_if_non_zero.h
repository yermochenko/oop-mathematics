/*
 * jg_if_non_zero.h
 *
 *  Created on: 12 дек. 2016 г.
 *      Author: User
 */

#ifndef JG_IF_NON_ZERO_H_
#define JG_IF_NON_ZERO_H_

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



#endif /* JG_IF_NON_ZERO_H_ */
