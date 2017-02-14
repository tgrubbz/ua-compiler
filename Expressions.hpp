
#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <exception>
#include <iostream>
#include "Types.hpp"

// Context class declaration
class context;

// Expressions classes declarations
class bool_expr;
class int_expr;
class and_expr;
class or_expr;
class xor_expr;
class not_expr;
class cond_expr;
class equal_expr;
class not_equal_expr;
class less_than_expr;
class greater_than_expr;
class less_than_eq_expr;
class greater_than_eq_expr;
class add_expr;
class sub_expr;
class multi_expr;
class div_expr;
class rem_expr;
class neg_expr;
class and_then_expr;
class or_else_expr;

// *************************************************************************** //
// Context class
// 
// Summary:
//		- Holds a reference for all possible types in the language.
// 
// *************************************************************************** //
class context
{
public:
	// Default Constructor and Destructor
	context() { }
	~context() { }

	// Type declarations
	// Used for type checking
	bool_type bool_type;
	int_type int_type;
};

// Global context instantiation
context * ctx = new context();

// *************************************************************************** //
// Base class definition for all expressions (Abstract class)
// 
// Summary:
//		- All expressions derive from this class. 
// 		- The visitor pattern is utilized in the evaluation of the expressions.
//		- Accept() (when defined in a base class) allows a visitor with an
//			overloaded function to be used for evaluation.
//		- Check() (when defined in a base class) perfroms a type check on
//			the callee expression's sub expression(s) and returns the
//			type of it's expression or throws an error if the type check
//			could not be satisfied. 
// 
// *************************************************************************** //
class expr
{
public:
	// Default Constructor and Destructor
	expr() { }
	~expr() { }

	// Visitor class declaration
	class visitor;

	// Pure virtual functions
	virtual void accept(visitor &) = 0;
	virtual type * check() = 0;
};

// *************************************************************************** //
// Base expression's visitior class
// 
// Summary:
//		- Defines all of the overloaded visit functions for
//			the visitor pattern.
// 
// *************************************************************************** //
class expr::visitor
{
public:
	// Pure virtual visit functions
	// One for each type of expression
	virtual void visit(bool_expr *) = 0;
	virtual void visit(int_expr *) = 0;
	virtual void visit(and_expr *) = 0;
	virtual void visit(or_expr *) = 0;
	virtual void visit(xor_expr *) = 0;
	virtual void visit(not_expr *) = 0;
	virtual void visit(cond_expr *) = 0;
	virtual void visit(equal_expr *) = 0;
	virtual void visit(not_equal_expr *) = 0;
	virtual void visit(less_than_expr *) = 0;
	virtual void visit(greater_than_expr *) = 0;
	virtual void visit(less_than_eq_expr *) = 0;
	virtual void visit(greater_than_eq_expr *) = 0;
	virtual void visit(add_expr *) = 0;
	virtual void visit(sub_expr *) = 0;
	virtual void visit(multi_expr *) = 0;
	virtual void visit(div_expr *) = 0;
	virtual void visit(rem_expr *) = 0;
	virtual void visit(neg_expr *) = 0;
	virtual void visit(and_then_expr *) = 0;
	virtual void visit(or_else_expr *) = 0;
};

// *************************************************************************** //
// Boolean expression class
// 
// Summary:
//		- Consists of the expressions literal true and literal false.
// 		- This expression is of the bool_type.
// 
// *************************************************************************** //
class bool_expr : public expr
{
public:
	// Literal boolean value
	bool val;

	// Contstructor with initializer list
	bool_expr(bool _val) : val(_val) { }
	~bool_expr() { }

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check() { return & ctx->bool_type; }
};

// *************************************************************************** //
// Integer expression class
// 
// Summary:
//		- Expression that consists of a literal integer. 
// 		- This expression is of the int_type.
// 
// *************************************************************************** //
class int_expr : public expr
{
public:
	// Literal integer value
	int val;

	// Contstructor with initializer list
	int_expr(int _val) : val(_val) { }
	~int_expr() { }

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }	
	type * check() { return & ctx->int_type; }
};

// *************************************************************************** //
// And expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers 
//			(sub expressions) declared as e1 and e1.
//		- e1 and e2 must both be of the bool_type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is true only if the evaluation of
//			both sub expressions are true.
// 
// *************************************************************************** //
class and_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	and_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~and_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->bool_type && e2->check() == & ctx->bool_type)
		{
			// Return the type of this expression
			return & ctx->bool_type;
		}

		throw std::exception("and_expr inner expressions must be of bool_type");
	}
};

// *************************************************************************** //
// Or expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e1.
//		- e1 and e2 must both be of the bool_type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is true if the evaluation of
//			at least one of the sub expressions is true.
// 
// *************************************************************************** //
class or_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	or_expr(expr * e1, expr * e2) : e1(e1), e2(e2)	
	{
		// Type check before construction
		check();
	}

	// Destructor
	~or_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->bool_type && e2->check() == & ctx->bool_type)
		{
			return & ctx->bool_type;
		}

		throw std::exception("or_expr inner expressions must be of bool_type");
	}
};

// *************************************************************************** //
// Xor expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e1.
//		- e1 and e2 must both be of the bool_type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is true only if the evaluation of
//			only one of the sub expressions are true, exclusively.
// 
// *************************************************************************** //
class xor_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	xor_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~xor_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->bool_type && e2->check() == & ctx->bool_type)
		{
			return & ctx->bool_type;
		}

		throw std::exception("xor_expr inner expressions must be of bool_type");
	}
};

// *************************************************************************** //
// Not expression class
// 
// Summary:
//		- Constuction of this class takes one expression pointer 
//			(sub expression) declared as e.
//		- e must be of the bool_type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is the inverse of the
//			sub expression.
// 
// *************************************************************************** //
class not_expr : public expr
{
public:
	// Sub expression pointer
	expr * e;

	// Contstructor with initializer list
	not_expr(expr * e) : e(e) 
	{
		// Type check before construction
		check();
	}

	// Destructor
	~not_expr()
	{
		// Delete sub expression pointer
		delete e;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e->check() == & ctx->bool_type)
		{
			return & ctx->bool_type;
		}

		throw std::exception("not_expr inner expression must be of bool_type");
	}
};

// *************************************************************************** //
// Conditional expression class
// 
// Summary:
//		- Constuction of this class takes three expression pointers 
//			(sub expressions) declared as e1, e2, and e3.
//		- e1 must be of the bool_type.
//		- e2 and e3 must be of the same type.
// 		- This expression is of the same type as e2 and e3.
//		- The evaluation of this expression depends on the boolean value
//			of e1. If e1 evaluates to true then the value of this expression
//			is equal to the evaluation of e2, else it is the evaluation of e3.
// 
// *************************************************************************** //
class cond_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;
	expr * e3;

	// Contstructor with initializer list
	cond_expr(expr * e1, expr * e2, expr * e3) : e1(e1), e2(e2), e3(e3)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~cond_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
		delete e3;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }	
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() != & ctx->bool_type)
		{
			throw std::exception("cond_expr first expression must be of bool_type");
		}

		// Hold onto the type of e2
		// If it matches the type of e3 then return it
		type * r = e2->check();
		if(r != e3->check())
		{
			throw std::exception("cond_expr second expression and third expression must be of identical type");			
		}

		return r;
	}	
};

// *************************************************************************** //
// Is equal to expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the same type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is true if the evaluation
//			of the two sub expression is equivalent.
// 
// *************************************************************************** //
class equal_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	equal_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~equal_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }	
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == e2->check())
		{
			return & ctx->bool_type;
		}

		throw std::exception("equal_expr inner expressions must be of identical type");
	}
};

// *************************************************************************** //
// Is not equal to expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the same type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is true if the evaluation
//			of the two sub expression is not equivalent.
// 
// *************************************************************************** //
class not_equal_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	not_equal_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~not_equal_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == e2->check())
		{
			return & ctx->bool_type;
		}

		throw std::exception("not_equal_expr inner expressions must be of identical type");
	}
};

// *************************************************************************** //
// Less than expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the int_type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is true if the evaluation
//			of e1 is less than the evaluation of e2.
// 
// *************************************************************************** //
class less_than_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	less_than_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~less_than_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->int_type && e2->check() == & ctx->int_type)
		{
			return & ctx->bool_type;
		}

		throw std::exception("less_than_expr inner expressions must be of int_type");
	}
};

// *************************************************************************** //
// Greater than expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the int_type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is true if the evaluation
//			of e1 is greater than the evaluation of e2.
// 
// *************************************************************************** //
// 
// *************************************************************************** //
class greater_than_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	greater_than_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~greater_than_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->int_type && e2->check() == & ctx->int_type)
		{
			return & ctx->bool_type;
		}

		throw std::exception("greater_than_expr inner expressions must be of int_type");
	}
};

// *************************************************************************** //
// Is less than or equal to expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the int_type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is true if the evaluation
//			of e1 is less than or equal to the evaluation of e2.
// 
// *************************************************************************** //
class less_than_eq_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	less_than_eq_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~less_than_eq_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->int_type && e2->check() == & ctx->int_type)
		{
			return & ctx->bool_type;
		}

		throw std::exception("less_than_eq_expr inner expressions must be of int_type");
	}
};

// *************************************************************************** //
// Greater than or equal to expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the int_type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is true if the evaluation
//			of e1 is greater than or equal to the evaluation of e2.
// 
// *************************************************************************** //
class greater_than_eq_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	greater_than_eq_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~greater_than_eq_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->int_type && e2->check() == & ctx->int_type)
		{
			return & ctx->bool_type;
		}

		throw std::exception("greater_than_eq_expr inner expressions must be of int_type");
	}
};

// *************************************************************************** //
// Add expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the int_type.
// 		- This expression is of the int_type.
//		- The evaluation of this expression is equal to the sum of the 
//			evaluation of e1 and the evaluation of e2.
// 
// *************************************************************************** //
class add_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	add_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~add_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->int_type && e2->check() == & ctx->int_type)
		{
			return & ctx->int_type;
		}

		throw std::exception("add_expr inner expressions must be of int_type");
	}
};

// *************************************************************************** //
// Subtraction expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the int_type.
// 		- This expression is of the int_type.
//		- The evaluation of this expression is equal to the mathematical 
//			difference (the evaluation of e1 - the evaluation of e2).
// 
// *************************************************************************** //
class sub_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	sub_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~sub_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->int_type && e2->check() == & ctx->int_type)
		{
			return & ctx->int_type;
		}

		throw std::exception("sub_expr inner expressions must be of int_type");
	}
};

// *************************************************************************** //
// Multiplication expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the int_type.
// 		- This expression is of the int_type.
//		- The evaluation of this expression is equal to the mathematical 
//			product of the evaluation of e1 and the evaluation of e2.
// 
// *************************************************************************** //
class multi_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	multi_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~multi_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->int_type && e2->check() == & ctx->int_type)
		{
			return & ctx->int_type;
		}

		throw std::exception("multi_expr inner expressions must be of int_type");
	}
};

// *************************************************************************** //
// Division expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the int_type.
// 		- This expression is of the int_type.
//		- The evaluation of this expression is equal to the mathematical 
//			division (the evaluation of e1 divided by evaluation of e2).
// 
// *************************************************************************** //
class div_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	div_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~div_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->int_type && e2->check() == & ctx->int_type)
		{
			return & ctx->int_type;
		}

		throw std::exception("div_expr inner expressions must be of int_type");
	}
};

// *************************************************************************** //
// Remainder expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the int_type.
// 		- This expression is of the int_type.
//		- The evaluation of this expression is equal to the mathematical 
//			modulus of the evaluation of e1 and the evaluation of e2.
// 
// *************************************************************************** //
class rem_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	rem_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}

	// Destructor
	~rem_expr()
	{
		// Delete sub expression pointers
		delete e1;
		delete e2;
	}
	
	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->int_type && e2->check() == & ctx->int_type)
		{
			return & ctx->int_type;
		}

		throw std::exception("rem_expr inner expressions must be of int_type");
	}
};

// *************************************************************************** //
// Negation expression class
// 
// Summary:
//		- Constuction of this class takes one expression pointer
//			(sub expression) declared as e.
//		- e must be of the int_type.
// 		- This expression is of the int_type.
//		- The evaluation of this expression is equal to the mathematical 
//			inverse of the sub expression e.
// 
// *************************************************************************** //
class neg_expr : public expr
{
public:
	// Sub expression pointer
	expr * e;

	// Contstructor with initializer list
	neg_expr(expr * e) : e(e)
	{
		// Type check before construction
		check();
	}
	
	// Destructor
	~neg_expr()
	{
		// Delete sub expression pointer
		delete e;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }	
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e->check() == & ctx->int_type)
		{
			return & ctx->int_type;
		}

		throw std::exception("neg_expr inner expression must be of int_type");
	}
};

// *************************************************************************** //
// And then expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of the bool_type.
// 		- This expression is of the bool_type.
//		- The evaluation of this expression is equal to e2 if e1 evaluates
//			to true, else the evaluation of this expression is false.
// 
// *************************************************************************** //
class and_then_expr : public expr
{
public:
	// Sub expression pointers
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	and_then_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}
	
	// Destructor
	~and_then_expr()
	{
		// Delete sub expression pointer
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }	
	type * check()
	{
		// Verify appropriate sub expression typing
		if(e1->check() == & ctx->bool_type && e2->check() == & ctx->bool_type)
		{
			return & ctx->bool_type;
		}

		throw std::exception("and_then_expr inner expressions must be of bool_type");
	}
};

// *************************************************************************** //
// Or else expression class
// 
// Summary:
//		- Constuction of this class takes two expression pointers
//			(sub expressions) declared as e1 and e2.
//		- e1 and e2 must be of identical type.
// 		- This expression is of the same type as e1 and e2.
//		- The evaluation of this expression is equal to e1 by 
//			default or else e2.
// 
// *************************************************************************** //
class or_else_expr : public expr
{
public:
	// Sub expression pointer
	expr * e1;
	expr * e2;

	// Contstructor with initializer list
	or_else_expr(expr * e1, expr * e2) : e1(e1), e2(e2)
	{
		// Type check before construction
		check();
	}
	
	// Destructor
	~or_else_expr()
	{
		// Delete sub expression pointer
		delete e1;
		delete e2;
	}

	// Inherited virtual function definitions
	void accept(visitor & v) { return v.visit(this); }	
	type * check()
	{
		// Verify appropriate sub expression typing
		type * r = e1->check();
		if(r == e2->check())
		{
			return r;
		}

		throw std::exception("or_else_expr inner expression must be of identical type");
	}
};

// *************************************************************************** //
// Helper Functions
// *************************************************************************** //

// Convert helper function 
// Converts the boolean literal argument into an integer literal
int convert(bool val) { return val ? 1 : 0; }

// Evaluation helper function
// Evaluates the expression argument
int eval(expr * e)
{
	// Derived expression visitor class
	// Overloaded visit function for each of the expression types
	// Part of the visitor pattern 
	class v : public expr::visitor
	{
	public:
		int val;
		void visit(bool_expr * e) { val = convert(e->val); }
		void visit(int_expr * e) { val = e->val; }
		void visit(and_expr * e) { val = convert(eval(e->e1) & eval(e->e2)); }
		void visit(or_expr * e) { val = convert(eval(e->e1) | eval(e->e2)); }
		void visit(xor_expr * e) { val = convert(eval(e->e1) ^ eval(e->e2)); }
		void visit(not_expr * e) { val = convert(!eval(e->e)); }
		void visit(cond_expr * e) { val = (eval(e->e1) ? eval(e->e2) : eval(e->e3)); }
		void visit(equal_expr * e) { val = convert(eval(e->e1) == eval(e->e2)); }
		void visit(not_equal_expr * e) { val = convert(eval(e->e1) != eval(e->e2)); }
		void visit(less_than_expr * e) { val = convert(eval(e->e1) < eval(e->e2)); }
		void visit(greater_than_expr * e) { val = convert(eval(e->e1) > eval(e->e2)); }
		void visit(less_than_eq_expr * e) { val = convert(eval(e->e1) <= eval(e->e2));}
		void visit(greater_than_eq_expr * e) { val = convert(eval(e->e1) >= eval(e->e2)); }
		void visit(add_expr * e) { val = eval(e->e1) + eval(e->e2); }
		void visit(sub_expr * e) { val = eval(e->e1) - eval(e->e2); }
		void visit(multi_expr * e) { val = eval(e->e1) * eval(e->e2); }
		void visit(div_expr * e) { val = eval(e->e1) / eval(e->e2); }
		void visit(rem_expr * e) { val = eval(e->e1) % eval(e->e2); }
		void visit(neg_expr * e) { val = -eval(e->e); }
		void visit(and_then_expr * e) { val = eval(e->e1) == 1 ? eval(e->e2) : 0; }
		void visit(or_else_expr * e) { val = 1 == 1 ? eval(e->e1) : eval(e->e2); }
	};

	// Create v (derived from visitor)
	v vis;

	// Call the expression argument's accept function with the (v) argument
	e->accept(vis);

	// Return the value of v
	// This is set in the corrsponding overloaded visit function defined in class v
	return vis.val;
}

#endif
