#ifndef JG_FOR_INPUT_MATRIX_FROM_STREAM_H_
#define JG_FOR_INPUT_MATRIX_FROM_STREAM_H_

#include <iostream>

using namespace std;

#include "struct.h"
#include "jg_for_input_row_from_stream.h"

class InputMatrixFromStreamInitStatement: public Statement
{
	Problem *problem;
public:
	InputMatrixFromStreamInitStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->i = 0;
	}
};

class InputMatrixFromStreamCondition: public Condition
{
	Problem *problem;
public:
	InputMatrixFromStreamCondition(Problem *problem)
	{
		this->problem = problem;
	}
	bool check()
	{
		return problem->i < problem->matrix->rowsCount();
	}
};

class InputMatrixFromStreamEndIterationStatement: public Statement
{
	Problem *problem;
public:
	InputMatrixFromStreamEndIterationStatement(Problem *problem)
	{
		this->problem = problem;
	}
	void execute()
	{
		problem->i++;
	}
};

class InputMatrixFromStreamBodyStatement: public Statement
{
	Problem *problem;
	Statement *inputRowFromStreamInitStatement;
	Condition *inputRowFromStreamCondition;
	Statement *inputRowFromStreamEndIterationStatement;
	Statement *inputRowFromStreamBodyStatement;
	For *inputRowFromStream;
public:
	InputMatrixFromStreamBodyStatement(Problem *problem)
	{
		this->problem = problem;
		inputRowFromStreamInitStatement = new InputRowFromStreamInitStatement(problem);
		inputRowFromStreamCondition = new InputRowFromStreamCondition(problem);
		inputRowFromStreamEndIterationStatement = new InputRowFromStreamEndIterationStatement(problem);
		inputRowFromStreamBodyStatement = new InputRowFromStreamBodyStatement(problem);
		inputRowFromStream = new For(inputRowFromStreamInitStatement, inputRowFromStreamCondition, inputRowFromStreamEndIterationStatement, inputRowFromStreamBodyStatement);
	}
	void execute()
	{
		inputRowFromStream->execute();
		cout << endl;
	}
	~InputMatrixFromStreamBodyStatement()
	{
		delete inputRowFromStream;
		delete inputRowFromStreamInitStatement;
		delete inputRowFromStreamCondition;
		delete inputRowFromStreamEndIterationStatement;
		delete inputRowFromStreamBodyStatement;
	}
};

class InputMatrixFromStream: public For
{
	Statement *inputMatrixFromStreamInitStatement;
	Condition *inputMatrixFromStreamCondition;
	Statement *inputMatrixFromStreamEndIterationStatement;
	Statement *inputMatrixFromStreamBodyStatement;
public:
	InputMatrixFromStream(Problem *problem) : For(
		inputMatrixFromStreamInitStatement = new InputMatrixFromStreamInitStatement(problem),
		inputMatrixFromStreamCondition = new InputMatrixFromStreamCondition(problem),
		inputMatrixFromStreamEndIterationStatement = new InputMatrixFromStreamEndIterationStatement(problem),
		inputMatrixFromStreamBodyStatement = new InputMatrixFromStreamBodyStatement(problem)
	) {}
	~InputMatrixFromStream()
	{
		delete inputMatrixFromStreamInitStatement;
		delete inputMatrixFromStreamCondition;
		delete inputMatrixFromStreamEndIterationStatement;
		delete inputMatrixFromStreamBodyStatement;
	}
};

#endif /* JG_FOR_INPUT_MATRIX_FROM_STREAM_H_ */
