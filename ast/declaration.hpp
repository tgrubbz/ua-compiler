
#include <vector>

class type;
class expr;

class decl
{
public:
	decl() { }
	virtual ~decl() = default;
	
};

class var_decl : public decl
{
public:
	std::string * name;
	type * t;
	expr * e;

	var_decl(type * t, std::string * name) : t(t), name(name), e(nullptr) { }
	var_decl(type * t, std::string * name, expr * e) : t(t), name(name), e(e) { }
	~var_decl() { }
	
};
