
# include <iostream>
# include <string>
# include <vector>

# include "ast/expression.hpp"
# include "lexer.hpp"
# include "print.hpp"
# include "parser.hpp"
# include "com/context.h"

// Global context instantiation
context * ctx = new context();

// void test_expr()
// {
// 	bool_expr * t = new bool_expr(true);
// 	bool_expr * f = new bool_expr(false);

// 	int_expr * x = new int_expr(2);
// 	int_expr * y = new int_expr(3);	

// 	try
// 	{
// 		std::cout << "bool_expr eval() = " << eval(new bool_expr(true)) << std::endl;
// 		std::cout << "int_expr eval() = " << eval(new int_expr(1)) << std::endl;
// 		std::cout << "and_expr eval() = " << eval(new and_expr(t, f)) << std::endl;
// 		std::cout << "or_expr eval() = " << eval(new or_expr(t, f)) << std::endl;
// 		std::cout << "xor_expr eval() = " << eval(new xor_expr(t, f)) << std::endl;
// 		std::cout << "not_expr eval() = " << eval(new not_expr(t)) << std::endl;
// 		std::cout << "cond_expr eval() = " << eval(new cond_expr(t, x, y)) << std::endl;
// 		std::cout << "equal_expr eval() = " << eval(new equal_expr(x, y)) << std::endl;
// 		std::cout << "not_equal_expr eval() = " << eval(new not_equal_expr(x, y)) << std::endl;
// 		std::cout << "less_than_expr eval() = " << eval(new less_than_expr(x, y)) << std::endl;
// 		std::cout << "greater_than_expr eval() = " << eval(new greater_than_expr(x, y)) << std::endl;
// 		std::cout << "less_than_eq_expr eval() = " << eval(new less_than_eq_expr(x, y)) << std::endl;
// 		std::cout << "greater_than_eq_expr eval() = " << eval(new greater_than_eq_expr(x, y)) << std::endl;
// 		std::cout << "add_expr eval() = " << eval(new add_expr(x, y)) << std::endl;
// 		std::cout << "sub_expr eval() = " << eval(new sub_expr(x, y)) << std::endl;
// 		std::cout << "multi_expr eval() = " << eval(new multi_expr(x, y)) << std::endl;
// 		std::cout << "div_expr eval() = " << eval(new div_expr(x, y)) << std::endl;
// 		std::cout << "rem_expr eval() = " << eval(new rem_expr(x, y)) << std::endl;
// 		std::cout << "neg_expr eval() = " << eval(new neg_expr(x)) << std::endl;
// 		std::cout << "and_then_expr eval() = " << eval(new and_then_expr(t, f)) << std::endl;
// 		std::cout << "or_else_expr eval() = " << eval(new or_else_expr(x, y)) << std::endl;

// 		std::cout << std::endl << "Incoming intentional exception..." << std::endl;
// 		eval(new and_expr(x, y));
// 	}
// 	catch(std::exception & e)
// 	{
// 		std::cout << e.what() << std::endl;
// 	}	
// }

output_format getOutputFormat(int argc, char * argv[])
{	
	if(argc > 1)
	{
		if(std::string(argv[argc - 1]) == "-b")
		{
			return output_format::binary;
		}
		else if(std::string(argv[argc - 1]) == "-h")
		{
			return output_format::hexadecimal;
		}
	}

	return output_format::decimal;
}

// void test_lexer(int argc, char * argv[])
// {
// 	output_format format = getOutputFormat(argc, argv);

// 	lexer lx;
// 	std::string str;

// 	while(getline(std::cin, str))
// 	{
// 		std::vector<token *> tokens = lx.lex(str);
// 		for(int i = 0; i < tokens.size(); ++i)
// 		{
// 			print(tokens.at(i), format);
// 		}
// 		std::cout << std::endl;
// 	}	
// }

void test_parser(int argc, char * argv[])
{
	output_format format = getOutputFormat(argc, argv);

	parser prsr;
	std::string str;

	while(getline(std::cin, str))
	{
		prsr.parse(str, format);
	}
}

int main(int argc, char * argv[])
{
	test_parser(argc, argv);
	return 0;
}