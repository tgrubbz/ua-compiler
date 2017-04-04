
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

public:
	parser()
	{
		lxr = new lexer(& sym_tbl, & kw_tbl);
	}
	~parser() { }
	
	void parse(std::string, output_format);

	/// statement-seq -> statement-seq statement | statement
	std::vector<stmt *> statement_seq();

	/// statement -> declaration-statement | expression-statement
	stmt* statement();

	/// declaration-statement -> declaration
	stmt* declaration_statement();

	/// expression-statement -> expression ';'
	stmt* expression_statement();


	// Declarations

	/// declaration -> variable-declaration
	decl* declaration();

	/// variable-declaration -> 'var' type-specifier identifier '=' expression ';'
	decl* variable_declaration();

	// Types

	/// type-specifier -> simple-type-specifier
	type* type_specifier();

	/// simple-type-specifier -> 'bool' | 'int'
	type* simple_type_specifier();

	// Expressions

	/// expression -> additive-expression
	expr* expression();

	/// additive-expression -> additive-expression '+' multiplicative-expression
	///                      | additive-expression '-' multiplicative-expression
	///                      | multiplicative-expression
	expr* additive_expression();

	/// multiplicative-expression -> multiplicative-expression '+' unary-expression
	///                            | multiplicative-expression '-' unary-expression
	///                            | unary-expression
	expr* multiplicative_expression();

	/// unary-expression -> '-' unary-expression
	///                   | primary-expression
	expr* unary_expression();

	/// primary-expression -> 'true' 
	///                     | 'false'
	///                     | integer-literal
	///                     | id-expression
	///                     | '(' expression ')'
	expr* primary_expression();

	/// id-expression -> identifier
	expr* id_expression();

	/// identifier
	std::string * identifier();
};

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
	// statement_seq();
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
	switch ((*current)->kind)
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
	return new decl_stmt(declaration());
}

stmt*
parser::expression_statement()
{
	return new expr_stmt(expression());
}


// -------------------------------------------------------------------------- //
// Declaration parsing

decl*
parser::declaration()
{
	return variable_declaration();
}

decl*
parser::variable_declaration()
{
	// Creates a variable declaration from the 
	// type, identifier, and expression
	return new var_decl(type_specifier(), identifier() , expression());
}

// -------------------------------------------------------------------------- //
// Type parsing

type*
parser::type_specifier()
{
  return simple_type_specifier();
}


type*
parser::simple_type_specifier()
{
	switch((*current)->kind)
	{
		case token_kind::bool_literal:
			next();
			return & ctx->bool_type;
		case token_kind::int_literal:
			next();
			return & ctx->int_type;
	}
}

// -------------------------------------------------------------------------- //
// Expression parsing

expr*
parser::expression()
{
	return additive_expression();
}

expr*
parser::additive_expression()
{
	expr * e = multiplicative_expression();
	next();

	while(!empty() && (
		(*current)->kind == token_kind::plus || 
		(*current)->kind == token_kind::minus))
	{
		multiplicative_expression();
		e = nullptr;
		next();
	}

	return e;
}


expr*
parser::multiplicative_expression()
{
	expr * e = unary_expression();
	next();
	
	while(!empty() && (
		(*current)->kind == token_kind::asterisk || 
		(*current)->kind == token_kind::percent || 
		(*current)->kind == token_kind::forward_slash))
	{
		unary_expression();
		e = nullptr;
		next();
	}

	return e;
}


expr*
parser::unary_expression()
{
	next();
	if(!empty() && ((*current)->kind == token_kind::minus))
	{
		unary_expression();
		return nullptr;
	}
	else
	{
		return primary_expression();
	}
}

expr*
parser::primary_expression()
{
	expr * e;
	switch((*current)->kind)
	{
		case token_kind::bool_literal:
			return new bool_expr(static_cast<bool_token *>(*current)->val);
		case token_kind::int_literal:		
			return new int_expr(static_cast<int_token *>(*current)->val);
		case token_kind::identifier:
			return id_expression();
		case token_kind::open_parenthesis:
			next();
			e = expression();
			next();
			return e;
		default:
			break;
	}
}

expr*
parser::id_expression()
{
  std::string * s = identifier();
  return nullptr;
}

// -------------------------------------------------------------------------- //
// Identifiers

std::string *
parser::identifier()
{
	next();
	id_token * t = static_cast<id_token *>(*current);			
	return & t->val;
}
