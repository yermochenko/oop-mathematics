#ifndef JG_FOR_MAKING_E_MATRIX_H_
#define JG_FOR_MAKING_E_MATRIX_H_

#include <iostream>

using namespace std;
#include "jg_if_zero.h"
#include "jg_for_one_diagonal_element.h"
#include "jg_for_zeroes_in_column.h"

class MakingEMatrixInitStatement: public Statement
{
	Problem *problem;
public:
	MakingEMatrixInitStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->i = 0;
	}
};

class MakingEMatrixCondition: public Condition
{
	Problem *problem;
public:
	MakingEMatrixCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->i < problem->matrix->rowsCount();	}
};

class MakingEMatrixEndIterationStatement: public Statement
{
	Problem *problem;
public:
	MakingEMatrixEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		 problem->i++;
	}
};

class MakingEMatrixBodyStatement: public Statement
{
	Problem *problem;
	Condition *zeroElementCondition ;
	Statement *zeroElementStatement;
	If *zeroElementIf;

	Statement *oneDiagonalElementInitStatement;
	Condition *oneDiagonalElementCondition;
	Statement *oneDiagonalElementEndIterationStatement;
	Statement *oneDiagonalElementBodyStatement;
	For *oneDiagonalElement;

	Statement *zeroInColumnForInitStatement;
	Condition *zeroInColumnForCondition ;
	Statement *zeroInColumnForEndIterationStatement;
	Statement *zeroInColumnForBodyStatement;
	For *zeroInColumn;
public:
	MakingEMatrixBodyStatement(Problem *problem)
	{
		this->problem = problem;
		zeroElementCondition = new ZeroElementCondition(problem);
		zeroElementStatement = new ZeroElementStatement(problem);
		zeroElementIf = new If(zeroElementCondition, zeroElementStatement);

		oneDiagonalElementInitStatement = new OneDiagonalElementInitStatement(problem);
		oneDiagonalElementCondition = new OneDiagonalElementCondition(problem);
		oneDiagonalElementEndIterationStatement = new OneDiagonalElementEndIterationStatement(problem);
		oneDiagonalElementBodyStatement = new OneDiagonalElementBodyStatement(problem);
		oneDiagonalElement = new For(oneDiagonalElementInitStatement, oneDiagonalElementCondition, oneDiagonalElementEndIterationStatement, oneDiagonalElementBodyStatement);

		zeroInColumnForInitStatement = new ZeroInColumnForInitStatement(problem);
		zeroInColumnForCondition = new ZeroInColumnForCondition(problem);
		zeroInColumnForEndIterationStatement = new ZeroInColumnForEndIterationStatement(problem);
		zeroInColumnForBodyStatement = new ZeroInColumnForBodyStatement(problem);
		zeroInColumn = new For(zeroInColumnForInitStatement, zeroInColumnForCondition, zeroInColumnForEndIterationStatement, zeroInColumnForBodyStatement);
	}
	void execute()
	{
		zeroElementIf->execute();
	    problem->f = problem->matrix->get(problem->i, problem->i);
	    oneDiagonalElement->execute();
	    zeroInColumn->execute();

	}
	~MakingEMatrixBodyStatement()
	{
		delete zeroElementIf;
		delete zeroElementCondition;
		delete zeroElementStatement;
		delete oneDiagonalElement;
		delete oneDiagonalElementInitStatement;
		delete oneDiagonalElementCondition;
		delete oneDiagonalElementEndIterationStatement;
		delete oneDiagonalElementBodyStatement;
		delete zeroInColumn;
		delete zeroInColumnForInitStatement;
		delete zeroInColumnForCondition;
		delete zeroInColumnForEndIterationStatement;
		delete zeroInColumnForBodyStatement;
	}
};

#endif /* JG_FOR_MAKING_E_MATRIX_H_ */
