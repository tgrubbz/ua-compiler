
#ifndef CONTEXT_HPP
#define CONTEXT_HPP

// *************************************************************************** //
// Context class
// 
// Summary:
//		- Holds a reference for all possible types in the language.
// 
// *************************************************************************** //
class context
{
public:
	// Default Constructor and Destructor
	context() { }
	~context() { }

	// Type declarations
	bool_type bool_type;
	int_type int_type;
};

#endif