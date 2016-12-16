#ifndef STRUCT_H_
#define STRUCT_H_

class Condition
{
public:
	virtual bool check() = 0;
	virtual ~Condition() {}
};

class Statement
{
public:
	virtual void execute() = 0;
	virtual ~Statement() {}
};

class If: public Statement {
	Condition *condition;
	Statement *statement;
public:
	If(Condition *condition, Statement *statement);
	void execute();
};

class For: public Statement {
	Statement *init;
	Condition *condition;
	Statement *endIteration;
	Statement *body;
public:
	For(Statement *init, Condition *condition, Statement *endIteration, Statement *body);
	void execute();
};

#endif /* STRUCT_H_ */
