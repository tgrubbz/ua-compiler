
#ifndef LEXER_HPP
#define LEXER_HPP

# include <string>
# include <vector>
# include "token.hpp"

class lexer
{
private:
	char * current;
	char * last;
	std::vector<token *> tokens;

	bool empty() { return current > last; }
	char now() { return * current; }
	void next() { ++current; }
	void back() { --current; }
	bool is_digit(char);
	token * parse_two(char, token_kind, token_kind);
	token * parse_amp(char);
	token * parse_int(char);
	token * parse_bool(bool);
	token * parse_binary();
	token * parse_hex();
	token * parse_comment();

public:
	lexer() { }
	~lexer() { }

	std::vector<token *> lex(std::string);
	
};

std::vector<token *> lexer::lex(std::string str)
{
	tokens.clear();
	if(str.size() == 0)
	{
		return tokens;
	}

	current = & str.front();
	last = & str.back();

	while(!empty())
	{
		char c = now();
		// std::cout << c << std::endl;
		switch(c)
		{
			case '+':
				tokens.push_back(new op_token(plus));
				break;
			case '-':
				tokens.push_back(new op_token(minus));
				break;
			case '*':
				tokens.push_back(new op_token(asterisk));
				break;
			case '/':
				tokens.push_back(new op_token(forward_slash));
				break;
			case '%':
				tokens.push_back(new op_token(percent));
				break;
			case '&':
				tokens.push_back(parse_two('&', ampersand_ampersand, ampersand));
				break;
			case '|':
				tokens.push_back(parse_two('|', bar_bar, bar));
				break;
			case '!':
				tokens.push_back(parse_two('=', exclamation_equal, exclamation));
				break;
			case '=':
				next();
				tokens.push_back(new op_token((now() == '=' ? equal_equal : throw std::exception("Invlaid Token - Attempted '=='"))));
				break;
			case '<':
				tokens.push_back(parse_two('=', less_than_equal, less_than));
				break;
			case '>':
				tokens.push_back(parse_two('=', greater_than_equal, greater_than));
				break;
			case '?':
				tokens.push_back(new op_token(question_mark));
				break;
			case ':':
				tokens.push_back(new op_token(colon));
				break;
			case '(':
				tokens.push_back(new op_token(open_parenthesis));
				break;
			case ')':
				tokens.push_back(new op_token(close_parenthesis));
				break;
			case '~':
				tokens.push_back(new op_token(tilde));
				break;
			case '^':
				tokens.push_back(new op_token(carat));
				break;
			case '#':
				tokens.push_back(parse_comment());
				break;
			case '0':
				next();
				if((c = now()) == 'b')
				{
					tokens.push_back(parse_binary());
					break;				
				}
				else if(c == 'h')
				{
					tokens.push_back(parse_hex());
					break;
				}
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': // integer
				tokens.push_back(parse_int(c));
				break;
			case 't':
				tokens.push_back(parse_bool(true));
				break;
			case 'f':
				tokens.push_back(parse_bool(false));
				break;
			default:
				break;
		}

		next();
	}

	return tokens;	
};

token * lexer::parse_int(char c)
{
	std::string s;

	while(is_digit((c = now())))
	{
		s += c;
		next();
	}
	back();

	try
	{
		return new int_token(std::stoi(s));
	}
	catch(std::exception e)
	{
		std::cout << e.what() << std::endl;
		throw e;
	}
}

bool lexer::is_digit(char c)
{	
	return 
		c == '0' || 
		c == '1' || 
		c == '2' || 
		c == '3' || 
		c == '4' || 
		c == '5' || 
		c == '6' || 
		c == '7' || 
		c == '8' || 
		c == '9';
}

token * lexer::parse_bool(bool b)
{
	next();
	if(b)
	{
		if(now() == 'r')
		{
			next();
			if(now() == 'u')
			{
				next();
				if(now() == 'e')
				{
					return new bool_token(true);
				}
			}
		}
	}
	else
	{
		if(now() == 'a')
		{
			next();
			if(now() == 'l')
			{
				next();
				if(now() == 's')
				{
					next();
					if(now() == 'e')
					{
						return new bool_token(false);						
					}
				}
			}
		}		
	}

	throw std::exception("Invalid Boolean Format");
}

token * lexer::parse_two(char secondary, token_kind double_kind, token_kind single_kind)
{
	next();
	if(now() == secondary)
	{
		return new op_token(double_kind);
	}
	else
	{
		back();
		return new op_token(single_kind);
	}
}

token * lexer::parse_binary()
{
	std::string s;

	next();
	char c = now();

	while(c == '1' || c == '0')
	{
		s += c;
		next();
		c = now();
	}
	back();

	try
	{
		return new binary_token(std::stoi(s, nullptr, 2));
	}
	catch(std::exception e)
	{
		std::cout << e.what() << std::endl;
		throw e;
	}
}

token * lexer::parse_hex()
{
	std::string s;

	next();
	char c = now();

	while(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7'
		 || c == '8' || c == '9' || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F')
	{
		s += c;
		next();
		c = now();
	}
	back();

	try
	{
		return new hex_token(std::stoi(s, nullptr, 16));
	}
	catch(std::exception e)
	{
		std::cout << e.what() << std::endl;
		throw e;
	}
}

token * lexer::parse_comment()
{
	std::string s;	
	char c = now();

	// skip any initial whitespace
	do
	{
		next();
	}
	while((c = now()) == ' ');


	while(!empty())
	{
		s += now();
		next();
	}

	return new comment_token(s);
}

#endif
