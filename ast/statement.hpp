
class expr;
class decl;

class stmt
{
public:
	stmt() { }
	virtual ~stmt() = default;
	
};

class expr_stmt : public stmt
{
public:
	expr * e;

	expr_stmt(expr * e) : e(e) { }
	~expr_stmt() { }
	
};

class decl_stmt : public stmt
{
public:
	decl * d;

	decl_stmt(decl * d) : d(d) { }
	~decl_stmt() { }

};
