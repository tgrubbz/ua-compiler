
#include <unordered_map>
#include <string>

class keyword_table : public std::unordered_map<std::string, token_kind>
{
public:
	keyword_table()
	{
		// Register keywords here
		// insert({ "bool", bool_literal });
		insert({ "false", bool_literal });
		// insert({ "int", int_literal });
		insert({ "true", bool_literal });
		insert({ "var", variable_literal });
	}

	~keyword_table() { }
	
};
