#include "struct.h"

If::If(Condition *condition, Statement *statement)
{
	this->condition = condition;
	this->statement = statement;
}

void If::execute()
{
	if(condition->check())
	{
		statement->execute();
	}
}

For::For(Statement *init, Condition *condition, Statement *endIteration, Statement *body)
{
	this->init = init;
	this->condition = condition;
	this->endIteration = endIteration;
	this->body = body;
}

void For::execute()
{
	for(init->execute(); condition->check(); endIteration->execute())
	{
		body->execute();
	}
}
