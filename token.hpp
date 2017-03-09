
#ifndef TOKEN_HPP
#define TOKEN_HPP

# include <ostream>
# include <bitset>

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

	// literals
	bool_literal,
	int_literal,
	binary_literal,
	hex_literal
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

	// literals
	"BOOL_LITERAL",
	"INT_LITERAL",
	"BINARY_LITERAL",
	"HEX_LITERAL"
};

class op_token;
class bool_token;
class int_token;
class binary_token;
class hex_token;
int default_output_number_base = 10;

class token
{
public:
	token_kind kind;

	token() { }
	~token() { }

	virtual void print(int) = 0;
	
};

class op_token : public token
{
public:
	op_token(token_kind tk)
	{
		kind = tk;
	}
	~op_token() { }

	void print(int output_number_base = default_output_number_base)
	{
		std::cout << token_kind_strs[kind] << std::endl;;
	}
	
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

	void print(int output_number_base = default_output_number_base)
	{
		std::cout << token_kind_strs[kind] << " : " << (val ? "TRUE" : "FALSE") << std::endl;;
	}
	
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

	void print(int output_number_base = default_output_number_base)
	{
		char buffer [33];
		std::cout << token_kind_strs[kind] << " : " << itoa(val, buffer, output_number_base) << std::endl;
	}
	
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

	void print(int output_number_base = default_output_number_base)
	{
		char buffer [33];
		std::cout << token_kind_strs[kind] << " : " << itoa(val, buffer, output_number_base) << std::endl;
	}
	
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

	void print(int output_number_base = default_output_number_base)
	{
		char buffer [33];
		std::cout << token_kind_strs[kind] << " : " << itoa(val, buffer, output_number_base) << std::endl;	
	}
	
};

#endif
