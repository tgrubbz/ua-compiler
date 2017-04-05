
# include "lexer.hpp"
# include "print.hpp"
# include "ast/token.hpp"
#include "ast/statement.hpp"
#include "ast/declaration.hpp"

# include <string>
# include <vector>

class parser
{
private:
	std::vector<token *> tokens;
	symbol_table sym_tbl;
	keyword_table kw_tbl;
	lexer * lxr;

	token ** current;
	token ** last;

	bool empty() { return current > last; }
	token * now() { return * current; }
	void next() { ++current; }
	void back() { --current; }

	token * peek();
	token_kind lookahead();
	token * match_if(token_kind);
	token * match(token_kind);
	token * consume();

	// Recursive Parsing
	
	std::vector<stmt *> statement_seq();

	// Statements
	stmt * statement();
	stmt * declaration_statement();
	stmt * expression_statement();

	// Declarations
	decl * declaration();
	decl * variable_declaration();

	// Types
	type* type_specifier();
	type* simple_type_specifier();

	// Expressions
	expr * expression();
	expr * conditional_expression();
	expr * logical_or_expression();
	expr * logical_and_expression();
	expr * equality_expression();
	expr * ordering_expression();
	expr * additive_expression();
	expr * multiplicative_expression();
	expr * unary_expression();
	expr * primary_expression();
	expr * id_expression();

	std::string * identifier();

public:
	parser()
	{
		lxr = new lexer(& sym_tbl, & kw_tbl);
	}
	~parser() { }
	
	void parse(std::string, output_format);
};

token*
parser::peek()
{
	if(!empty())
	{
		return *current;
	}

	return nullptr;
}

token_kind
parser::lookahead()
{
	if(token * t = peek())
	{
		return t->kind;
	}
	else
	{
		return token_kind::eof;
	}
}

token*
parser::match_if(token_kind k)
{
	if(lookahead() == k)
	{
		return consume();
	}

	return nullptr;
}

token*
parser::match(token_kind k)
{
	if(lookahead() == k)
	{
		return consume();
	}

	return nullptr;
}

token * parser::consume()
{
	token * t = *current;
	next();
	return t;
}

void parser::parse(std::string s, output_format format)
{
	// Lex the tokens from the string input
	tokens = lxr->lex(s);

	// Set the current token ptr and the last token ptr
	current = &tokens.front();
	last = &tokens.back();

	// Loop through the lexed tokens
	// while(!empty())
	// {
	// 	print(*current, format);
	// 	next();
	// }

	// std::cout << std::endl;
	for(stmt * s : statement_seq())
	{
		std::cout << s->evaluate() << std::endl;
	}
}

// decl*
// parser::program()
// {
//   std::vector<stmt*> ss = statement_seq();
//   return sema.on_program(ss);
// }

// -------------------------------------------------------------------------- //
// Statement parsing

std::vector<stmt *>
parser::statement_seq()
{
	std::cout << "statement_seq" << std::endl;
	std::vector<stmt*> statements;
	while (!empty())
	{
		statements.push_back(statement());
	}
	return statements;
}

stmt *
parser::statement()
{
	std::cout << "statement" << std::endl;
	switch (lookahead())
	{
		case token_kind::variable_literal:
			return declaration_statement();
		default:
			return expression_statement();
	}
}

stmt*
parser::declaration_statement()
{
	std::cout << "declaration_statement" << std::endl;
	return new decl_stmt(declaration());
}

stmt*
parser::expression_statement()
{
	std::cout << "expression_statement" << std::endl;
	stmt * s = new expr_stmt(expression());
	match(token_kind::semicolon);
	return s;
}


// -------------------------------------------------------------------------- //
// Declaration parsing

decl*
parser::declaration()
{
	std::cout << "declaration" << std::endl;
	switch(lookahead())
	{
		case token_kind::variable_literal:
			return variable_declaration();
	}

	return nullptr;
}

decl*
parser::variable_declaration()
{
	std::cout << "variable_declaration" << std::endl;

	type * t = type_specifier();
	std::string * n = identifier();
	var_decl * v = new var_decl(t, n);
	match(token_kind::equals);
	v->e = expression();
	match(token_kind::semicolon);

	return v;
}

// -------------------------------------------------------------------------- //
// Type parsing

type*
parser::type_specifier()
{
	std::cout << "type_specifier" << std::endl;
	return simple_type_specifier();
}


type*
parser::simple_type_specifier()
{
	std::cout << "simple_type_specifier" << std::endl;
	switch(lookahead())
	{
		case token_kind::bool_literal:
			consume();
			return & ctx->bool_type;
		case token_kind::int_literal:
			consume();
			return & ctx->int_type;
	}
}

// -------------------------------------------------------------------------- //
// Expression parsing

expr*
parser::expression()
{
	std::cout << "expression" << std::endl;
	return conditional_expression();
}

expr * parser::conditional_expression()
{
	std::cout << "conditional_expression" << std::endl;
	expr * e1 = logical_or_expression();

	while(true)
	{
		if(match_if(token_kind::question_mark))
		{
			expr * e2 = logical_or_expression();
			match(token_kind::colon);
			expr * e3 = logical_or_expression();
			e1 = new cond_expr(e1, e2, e3);
		}
		else
		{
			break;
		}
	}

	return e1;	
}

expr * parser::logical_or_expression()
{
	std::cout << "logical_or_expression" << std::endl;
	expr * e1 = logical_and_expression();

	while(true)
	{
		if(match_if(token_kind::bar))
		{
			expr * e2 = logical_and_expression();
			e1 = new or_expr(e1, e2);
		}
		else if(match_if(token_kind::bar_bar))
		{
			expr * e2 = logical_and_expression();
			e1 = new or_else_expr(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;

}

expr * parser::logical_and_expression()
{
	std::cout << "logical_and_expression" << std::endl;
	expr * e1 = equality_expression();

	while(true)
	{
		if(match_if(token_kind::ampersand))
		{
			expr * e2 = equality_expression();
			e1 = new and_expr(e1, e2);
		}
		else if (match_if(token_kind::ampersand_ampersand))
		{
			expr * e2 = equality_expression();
			e1 = new and_then_expr(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;

}

expr * parser::equality_expression()
{
	std::cout << "equality_expression" << std::endl;
	expr * e1 = ordering_expression();

	while(true)
	{
		if(match_if(token_kind::equal_equal))
		{
			expr * e2 = ordering_expression();
			e1 = new equal_expr(e1, e2);
		}
		else if (match_if(token_kind::exclamation_equal))
		{
			expr * e2 = ordering_expression();
			e1 = new not_equal_expr(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;

}

expr * parser::ordering_expression()
{
	std::cout << "ordering_expression" << std::endl;
	expr * e1 = additive_expression();

	while(true)
	{
		if(match_if(token_kind::less_than))
		{
			expr * e2 = additive_expression();
			e1 = new less_than_expr(e1, e2);
		}
		else if(match_if(token_kind::less_than_equal))
		{
			expr * e2 = additive_expression();
			e1 = new less_than_eq_expr(e1, e2);
		}
		else if(match_if(token_kind::greater_than))
		{
			expr * e2 = additive_expression();
			e1 = new greater_than_expr(e1, e2);
		}
		else if(match_if(token_kind::greater_than_equal))
		{
			expr * e2 = additive_expression();
			e1 = new greater_than_eq_expr(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;

}


expr*
parser::additive_expression()
{
	std::cout << "additive_expression" << std::endl;
	expr * e1 = multiplicative_expression();

	while(true)
	{
		if(match_if(token_kind::plus))
		{
			expr * e2 = multiplicative_expression();
			e1 = new add_expr(e1, e2);
		}
		else if (match_if(token_kind::minus))
		{
			expr * e2 = multiplicative_expression();
			e1 = new sub_expr(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}


expr*
parser::multiplicative_expression()
{
	std::cout << "multiplicative_expression" << std::endl;
	expr * e1 = unary_expression();
	
	while(true)
	{
		if(match_if(token_kind::asterisk))
		{
			expr * e2 = unary_expression();
			e1 = new multi_expr(e1, e2);
		}
		else if (match_if(token_kind::forward_slash))
		{
			expr * e2 = unary_expression();
			e1 = new div_expr(e1, e2);
		}
		else if (match_if(token_kind::percent))
		{
			expr * e2 = unary_expression();
			e1 = new rem_expr(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}


expr*
parser::unary_expression()
{
	std::cout << "unary_expression" << std::endl;
	if(match_if(token_kind::minus))
	{		
		return new neg_expr(unary_expression());
	}
	else
	{
		return primary_expression();
	}
}

expr*
parser::primary_expression()
{
	std::cout << "primary_expression, kind: " << token_kind_strs[(*current)->kind] << std::endl;
	expr * e;
	switch(lookahead())
	{
		case token_kind::bool_literal:
			return new bool_expr(static_cast<bool_token *>(consume())->val);
		case token_kind::int_literal:
			return new int_expr(static_cast<int_token *>(consume())->val);
		case token_kind::identifier:
			return id_expression();
		case token_kind::open_parenthesis:
			consume();
			e = expression();
			match(token_kind::close_parenthesis);
			return e;
		default:
			break;
	}
}

expr*
parser::id_expression()
{
	std::cout << "id_expression" << std::endl;
	std::string * s = identifier();
	decl * d = sym_tbl->find(*s);
	var_decl * v = 
	return nullptr;
}

// -------------------------------------------------------------------------- //
// Identifiers

std::string *
parser::identifier()
{
	std::cout << "identitfier" << std::endl;
	token * temp = match(token_kind::identifier);
	id_token * t = static_cast<id_token *>(temp);
	return & t->val;
}
