
#include <unordered_map>
#include <string>

class decl;

class symbol_table : public std::unordered_map<std::string, decl *>
{
public:
	symbol_table() { }
	~symbol_table() { }
	
};
