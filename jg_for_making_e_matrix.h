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
	If *zeroElementIf;
	For *oneDiagonalElement;
	For *zeroInColumn;
public:
	MakingEMatrixBodyStatement(Problem *problem)
	{
		this->problem = problem;
		zeroElementIf = new ZeroElementIf(problem);
		oneDiagonalElement = new OneDiagonalElement(problem);
		zeroInColumn = new ZeroInColumn(problem);
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
		delete oneDiagonalElement;
		delete zeroInColumn;
	}
};

class MakingEMatrix: public For
{
	Statement *makingEMatrixInitStatement;
	Condition *makingEMatrixCondition;
	Statement *makingEMatrixEndIterationStatement;
	Statement *makingEMatrixBodyStatement;
public:
	MakingEMatrix(Problem *problem) : For(
		makingEMatrixInitStatement = new MakingEMatrixInitStatement(problem),
		makingEMatrixCondition = new MakingEMatrixCondition(problem),
		makingEMatrixEndIterationStatement = new MakingEMatrixEndIterationStatement(problem),
		makingEMatrixBodyStatement = new MakingEMatrixBodyStatement(problem)
	) {}
	~MakingEMatrix()
	{
		delete makingEMatrixInitStatement;
		delete makingEMatrixCondition;
		delete makingEMatrixEndIterationStatement;
		delete makingEMatrixBodyStatement;
	}
};

#endif /* JG_FOR_MAKING_E_MATRIX_H_ */
