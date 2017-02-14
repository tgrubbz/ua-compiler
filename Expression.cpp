
#include <iostream>
#include <string>

#include "Expressions.hpp"

using namespace std;

int main()
{
	bool_expr * t = new bool_expr(true);
	bool_expr * f = new bool_expr(false);

	int_expr * x = new int_expr(2);
	int_expr * y = new int_expr(3);	

	try
	{
		cout << "bool_expr eval() = " << eval(new bool_expr(true)) << endl;
		cout << "int_expr eval() = " << eval(new int_expr(1)) << endl;
		cout << "and_expr eval() = " << eval(new and_expr(t, f)) << endl;
		cout << "or_expr eval() = " << eval(new or_expr(t, f)) << endl;
		cout << "xor_expr eval() = " << eval(new xor_expr(t, f)) << endl;
		cout << "not_expr eval() = " << eval(new not_expr(t)) << endl;
		cout << "cond_expr eval() = " << eval(new cond_expr(t, x, y)) << endl;
		cout << "equal_expr eval() = " << eval(new equal_expr(x, y)) << endl;
		cout << "not_equal_expr eval() = " << eval(new not_equal_expr(x, y)) << endl;
		cout << "less_than_expr eval() = " << eval(new less_than_expr(x, y)) << endl;
		cout << "greater_than_expr eval() = " << eval(new greater_than_expr(x, y)) << endl;
		cout << "less_than_eq_expr eval() = " << eval(new less_than_eq_expr(x, y)) << endl;
		cout << "greater_than_eq_expr eval() = " << eval(new greater_than_eq_expr(x, y)) << endl;
		cout << "add_expr eval() = " << eval(new add_expr(x, y)) << endl;
		cout << "sub_expr eval() = " << eval(new sub_expr(x, y)) << endl;
		cout << "multi_expr eval() = " << eval(new multi_expr(x, y)) << endl;
		cout << "div_expr eval() = " << eval(new div_expr(x, y)) << endl;
		cout << "rem_expr eval() = " << eval(new rem_expr(x, y)) << endl;
		cout << "neg_expr eval() = " << eval(new neg_expr(x)) << endl;
		cout << "and_then_expr eval() = " << eval(new and_then_expr(t, f)) << endl;
		cout << "or_else_expr eval() = " << eval(new or_else_expr(x, y)) << endl;

		cout << endl << "Incoming intentional exception..." << endl;
		eval(new and_expr(x, y));
	}
	catch(exception & e)
	{
		cout << e.what() << endl;
	}

	return 0;
}