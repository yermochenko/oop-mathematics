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