
// # include "expression.hpp"
// # include "declaration.hpp"

class expr;
class decl;

class stmt
{
public:
	stmt() { }
	virtual ~stmt() = default;
	virtual int evaluate() = 0;
	
};

class expr_stmt : public stmt
{
public:
	expr * e;

	expr_stmt(expr * e) : e(e) { }
	~expr_stmt() { }

	int evaluate()
	{
		std::cout << "evaluate expr stmt" << std::endl;
		return eval(e);
	}
	
};

class decl_stmt : public stmt
{
public:
	decl * d;

	decl_stmt(decl * d) : d(d) { }
	~decl_stmt() { }

	int evaluate()
	{
		std::cout << "evaluate decl stmt" << std::endl;
		return 0;
	}	

};
