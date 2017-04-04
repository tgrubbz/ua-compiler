
#ifndef PRINT_HPP
#define PRINT_HPP

# include "ast/token.hpp"

static char buffer [33];

enum output_format
{
	decimal,
	binary,
	hexadecimal
};

static int getNumberBase(output_format format)
{
	switch(format)
	{
		case decimal:
			return 10;
		case binary:
			return 2;
		case hexadecimal:
			return 16;
	}
}

void print(token * t, output_format format)
{
	class vis : public token::visitor
	{
	public:
		output_format format;

		vis(output_format format) : format(format) { }

		void visit(op_token * tok) 
		{
			std::cout << token_kind_strs[tok->kind] << std::endl;
		}
		void visit(bool_token * tok) 
		{
			std::cout << token_kind_strs[tok->kind] << " : " << (tok->val ? "TRUE" : "FALSE") << std::endl;
		}
		void visit(int_token * tok) 
		{
			std::cout << token_kind_strs[tok->kind] << " : " << itoa(tok->val, buffer, getNumberBase(format)) << std::endl;
		}
		void visit(binary_token * tok) 
		{
			std::cout << token_kind_strs[tok->kind] << " : " << itoa(tok->val, buffer, getNumberBase(format)) << std::endl;
		}
		void visit(hex_token * tok) 
		{
			std::cout << token_kind_strs[tok->kind] << " : " << itoa(tok->val, buffer, getNumberBase(format)) << std::endl;
		}
		void visit(comment_token * tok) 
		{
			std::cout << token_kind_strs[tok->kind] << " : " << tok->val << std::endl;
		}
		void visit(id_token * tok) 
		{
			std::cout << token_kind_strs[tok->kind] << " : " << tok->val << std::endl;
		}
		void visit(var_token * tok) 
		{
			std::cout << token_kind_strs[tok->kind] << " : var" << std::endl;
		}
	};

	vis v(format);
	t->accept(v);	
}

#endif
