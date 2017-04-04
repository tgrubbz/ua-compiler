
#ifndef TOKEN_HPP
#define TOKEN_HPP

enum token_kind
{
	eof,

	// operators and punctuators
	plus,
	minus,
	asterisk,
	forward_slash,
	percent,
	ampersand,
	ampersand_ampersand,
	bar,
	bar_bar,
	exclamation,
	equal_equal,
	exclamation_equal,
	less_than,
	greater_than,
	less_than_equal,
	greater_than_equal,
	question_mark,
	colon,
	open_parenthesis,
	close_parenthesis,
	tilde,
	carat,
	pound,
	semicolon,

	// literals
	bool_literal,
	int_literal,
	binary_literal,
	hex_literal,
	comment_literal,
	variable_literal,

	identifier
};

const char * token_kind_strs[] 
{
	"EOF",

	// operators and punctuators
	"PLUS",
	"MINUS",
	"ASTERISK",
	"FORWARD_SLASH",
	"PERCENT",
	"AMPERSAND",
	"AMPERSAND_AMPERSAND",
	"BAR",
	"BAR_BAR",
	"EXCLAMATION",
	"EQUAL_EQUAL",
	"EXCLAMATION_EQUAL",
	"LESS_THAN",
	"GREATER_THAN",
	"LESS_THAN_EQUAL",
	"GREATER_THAN_EQUAL",
	"QUESTION_MARK",
	"COLON",
	"OPEN_PARENTHESIS",
	"CLOSE_PARENTHESIS",
	"TILDE",
	"CARAT",
	"POUND",
	"SEMICOLON",

	// literals
	"BOOL_LITERAL",
	"INT_LITERAL",
	"BINARY_LITERAL",
	"HEX_LITERAL",
	"COMMENT_LITERAL",
	"VARIABLE_LITERAL",
	"IDENTIFIER"
};

class op_token;
class bool_token;
class int_token;
class binary_token;
class hex_token;
class comment_token;
class id_token;
class var_token;

class token
{
public:
	token_kind kind;

	token() { }
	virtual ~token() = default;

	// Visitor class declaration
	class visitor;

	// Pure virtual functions
	virtual void accept(visitor &) = 0;
	
};

class token::visitor
{
public:
	virtual void visit(op_token *) = 0;
	virtual void visit(bool_token *) = 0;
	virtual void visit(int_token *) = 0;
	virtual void visit(binary_token *) = 0;
	virtual void visit(hex_token *) = 0;
	virtual void visit(comment_token *) = 0;
	virtual void visit(id_token *) = 0;
	virtual void visit(var_token *) = 0;
};

class op_token : public token
{
public:
	op_token(token_kind tk)
	{
		kind = tk;
	}
	~op_token() { }

	void accept(visitor & v) { return v.visit(this); }
	
};

class bool_token : public token
{
public:
	bool val;

	bool_token(bool b) : val(b)
	{
		kind = bool_literal;
	}
	~bool_token() { }

	void accept(visitor & v) { return v.visit(this); }
	
};

class int_token : public token
{
public:
	const int val;

	int_token(int i) : val(i)
	{
		kind = int_literal;
	}
	~int_token() { }

	void accept(visitor & v) { return v.visit(this); }
	
};

class binary_token : public token
{
public:
	const int val;

	binary_token(int i) : val(i)
	{
		kind = binary_literal;
	}
	~binary_token() { }

	void accept(visitor & v) { return v.visit(this); }
	
};

class hex_token : public token
{
public:
	const int val;

	hex_token(int i) : val(i)
	{
		kind = hex_literal;
	}
	~hex_token() { }

	void accept(visitor & v) { return v.visit(this); }
	
};

class comment_token : public token
{
public:
	std::string val;

	comment_token(std::string s) : val(s) 
	{
		kind = comment_literal;
	}
	~comment_token() { }

	void accept(visitor & v) { return v.visit(this); }
	
};

class id_token : public token
{
public:
	std::string val;

	id_token(std::string s) : val(s)
	{
		kind = identifier;
	}
	~id_token() { }

	void accept(visitor & v) { return v.visit(this); }
	
};

class var_token : public token
{
public:
	var_token()
	{
		kind = variable_literal;
	}
	~var_token() { }

	void accept(visitor & v) { return v.visit(this); }
	
};

#endif
