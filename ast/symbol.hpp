
#include <unordered_map>
#include <string>

class symbol_table : public std::unordered_map<std::string, void *>
{
public:
	symbol_table() { }
	~symbol_table() { }

	void ins(std::string);
	bool exists(std::string);
	
};
